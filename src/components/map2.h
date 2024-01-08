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

#include <lib/imgui/imgui.h>

#include <LDtkLoader/Project.hpp>
#include <LDtkLoader/World.hpp>
#include <LDtkLoader/Level.hpp>

struct Tile {
	Vec2 Position;
	Subtexture* SubTex;
};

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
	
	Texture* tileset;

	Vector<Tile> tiles;

	void load_layer(const ldtk::Level& lvl, String layer_name)
	{
		const auto& layer = lvl.getLayer(layer_name);

		log_info("[MAP] Loading layer: %s", layer.getName().c_str());


		for (auto tile : layer.allTiles())
		{
			Tile t;
			t.Position = Vec2(tile.getWorldPosition().x, tile.getWorldPosition().y);
			t.SubTex = new Subtexture(tileset, Vec2(tile.getTextureRect().x, tile.getTextureRect().y), Vec2(tile.getTextureRect().width, tile.getTextureRect().height));
			tiles.push_back(t);
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

		//log_info("[MAP] Creating tiles: %s", tileset.name.c_str());
		
		for (auto tile : layer.allTiles())
		{
			Tile t;
			t.Position = Vec2(tile.getWorldPosition().x, tile.getWorldPosition().y);
			t.SubTex = new Subtexture(tileset, Vec2(tile.getTextureRect().x, tile.getTextureRect().y), Vec2(tile.getTextureRect().width, tile.getTextureRect().height));
			tiles.push_back(t);
		}

		load_layer(lvl, "IntGrid");
	}


	void update() override
	{
		// handle map transitions
	};

	void render(Renderer* ren) override
	{
		for (auto& tile : tiles)
		{
			ren->draw_subtex(tile.SubTex, tile.Position);
		}
	}
};

