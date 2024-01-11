/*****************************************************************//**
 * \file   map2.h
 * \brief  this component is responsible for handling map
 *
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/asset.h>

#include <SDL_stdinc.h>

#include <components/animator.h>
#include <components/sprite.h>

#include <render/subtexture.h>
#include <render/device.h>
#include <render/buffer.h>

#include <lib/imgui/imgui.h>

#include <LDtkLoader/Project.hpp>
#include <LDtkLoader/World.hpp>
#include <LDtkLoader/Level.hpp>

struct Tile {
	Vec2 Position;
	Subtexture* SubTex;
	Vec2 Rect;
};

struct Vertex { float position[2]; float texcoord[2]; } ;

class Player;
/// <summary>
/// class responsible for generating map
/// </summary>
class Map2 : public Component
{
public:
	Map2() = default;
	Map2(int test)
	{

	}
	
	GLuint map_vbo;
	GLuint map_vao;

	bool naive;

	int tile_limit = 1;

	Texture* tileset;

	Vector<Tile> tiles;
	
	Vertex* vertices;
	gpu::Buffer* map_buffer;
	int vertex_capacity = 1000;
	int vertex_count = 0;

	void load_layer(const ldtk::Level& lvl, String layer_name)
	{
		const auto& layer = lvl.getLayer(layer_name);

		log_info("[MAP] Loading layer: %s", layer.getName().c_str());


		for (auto tile : layer.allTiles())
		{
			Tile t;
			t.Position = Vec2(tile.getWorldPosition().x, tile.getWorldPosition().y);
			t.Rect = Vec2(tile.getTextureRect().x, tile.getTextureRect().y);
			t.SubTex = new Subtexture(tileset, Vec2(tile.getTextureRect().x, tile.getTextureRect().y), Vec2(tile.getTextureRect().width, tile.getTextureRect().height));
			tiles.push_back(t);
		}

	}

	void load_colliders(const ldtk::Level& lvl, String collider_layer_name)
	{
		const auto& layer = lvl.getLayer(collider_layer_name);

		log_info("[MAP] Loading collisions: %s", layer.getName().c_str());
		
		auto g_size = layer.getGridSize();

		for (int x = 0; x < g_size.x; x++)
		{
			for (int y = 0; y < g_size.y; y++)
			{
				if (layer.getIntGridVal(x, y).value == 1)
				{
					std::ostringstream str;
					str << "Collider: " << x << "x" << y;

					auto ent = this->entity->world->create(str.str(), this->entity);
					ent->position = Vec2(x * 16, y * 16);
					auto col = ent->add(Collider(Vec2(16, 16), Vec2(0,0)));
					col->tag = CollisionTag::Solid;
				}
			}

		}
	}

	void init() override
	{
		ldtk::Project ldtk_project;
		// parse map and create entites and stuff
		ldtk_project.loadFromFile(Asset::get_asset_path("map/world/world.ldtk"));
		const auto& w = ldtk_project.getWorld();
		const auto& lvl = w.getLevel("Level_0");
		const auto& layer = lvl.getLayer("Tiles");

		log_info("[MAP] Starting to load map: %s", w.getName().c_str());
		log_info("[MAP] Loading level: %s", lvl.name.c_str());

		log_info("[MAP] Loading layer: %s", layer.getName().c_str());
		log_info("[MAP] Loading tileset: %s for layer: %s", layer.getTileset().name.c_str(), layer.getName().c_str());
		tileset = Asset::load_texture("map/world/" + layer.getTileset().path);

		load_layer(lvl, "IntGrid");
		load_colliders(lvl, "Colliders");

		for (auto tile : layer.allTiles())
		{
			Tile t;
			t.Position = Vec2(tile.getWorldPosition().x, tile.getWorldPosition().y);
			t.Rect = Vec2(tile.getTextureRect().x, tile.getTextureRect().y);
			t.SubTex = new Subtexture(tileset, Vec2(tile.getTextureRect().x, tile.getTextureRect().y), Vec2(tile.getTextureRect().width, tile.getTextureRect().height));
			tiles.push_back(t);
		}


		map_buffer = gpu::device->create_buffer({
			{{2, GL_FLOAT}, {2, GL_FLOAT}},
			gpu::BindFlags::BIND_VERTEX_BUFFER,
			gpu::UsageFlags::DYNAMIC_DRAW,
			vertex_capacity * sizeof(Vertex),
			NULL
		});

		vertices = (Vertex*)malloc(sizeof(Vertex) * vertex_capacity);
	}


	void update() override
	{
		// handle map transitions
	};

	void push_vertex(Renderer* ren, float x, float y, float u, float v)
	{
		// push vertex to buffer
		if (vertex_count % 6 == 0 && vertex_count + 6 > vertex_capacity) {
			// draw
			gpu::device->update_buffer(map_buffer, vertices, vertex_count * sizeof(Vertex));
			ren->draw_buffer(map_buffer, vertex_count, glm::mat4(1.0f), tileset);
			vertex_count = 0;
		}

		vertices[vertex_count++] = {
			.position = {x, y},
			.texcoord = {u, v}
		};
	}

	void render(Renderer* ren) override
	{
		int counter = 0;

		for (auto& tile : tiles)
		{
			if (tile.Position.x - 32 < ren->get_camera()->position.x || tile.Position.x + 32 > ren->get_camera()->position.x + ren->get_target()->target_size.x ||
				tile.Position.y + 32 < ren->get_camera()->position.y || tile.Position.y - 32 > ren->get_camera()->position.y + ren->get_target()->target_size.y)
				continue;


			if (naive)
			{
				ren->draw_subtex(tile.SubTex, tile.Position);
			}
			else 
			{
				float x1 = tile.Position.x;
				float y1 = tile.Position.y;
				float x2 = tile.Position.x + 16;
				float y2 = tile.Position.y + 16;
		
				float u1 = tile.Rect.x / tileset->size.x;
				float v1 = tile.Rect.y / tileset->size.y;
				float u2 = (tile.Rect.x + 16) / tileset->size.x;
				float v2 = (tile.Rect.y + 16) / tileset->size.y;

				push_vertex(ren, x1, y1, u1, v1);
				push_vertex(ren, x2, y2, u2, v2);
				push_vertex(ren, x2, y1, u2, v1);

				push_vertex(ren, x1, y1, u1, v1);
				push_vertex(ren, x1, y2, u1, v2);
				push_vertex(ren, x2, y2, u2, v2);

			}

			counter++;

	/*		if (counter == tile_limit)
				break;*/

		}

		// draw
		gpu::device->update_buffer(map_buffer, vertices, vertex_count * sizeof(Vertex));
		ren->draw_buffer(map_buffer, vertex_count, glm::mat4(1.0f), tileset);
		vertex_count = 0;

		if (ImGui::Begin("Map"))
		{
			ImGui::InputInt("How many tiles to render", &tile_limit);
			ImGui::End();
		}
	}

	void destroy() override
	{
		free(vertices);
		gpu::device->destroy_buffer(map_buffer);
		//gpu::device->destroy_texture(tileset);
	}
};

