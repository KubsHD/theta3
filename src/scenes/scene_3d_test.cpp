#include "scene_3d_test.h"

#include <glm/glm.hpp>

#include <core/input.h>
#include <core/asset.h>

#include <system/render_system.h>

#include <render/device.h>
#include <render/Shader.h>
#include <core/game.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vfs.h>
#include <utils/profiler.h>


float cube_vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};


struct SceneData {
	glm::mat4 mvp;
	glm::mat4 model;
};

struct Material {
	Texture* diff = nullptr;
	Texture* spec = nullptr;
	Texture* norm = nullptr;
};

struct Camera3D {
	glm::vec3 pos;
	
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	glm::vec3 worldUp;

	float yaw;
	float pitch;
};

struct Vertex {
	float x;
	float y;
	float z;

	float nx;
	float ny;
	float nz;

	float u;
	float v;
};

struct Mesh {
	gpu::Buffer* vb;
	gpu::Buffer* ib;
	int indices;
	Material mat;
};

static gpu::Buffer* vb;
static gpu::Buffer* ib;
static SceneData sd;
static Shader* shd;

static RenderSystem rs;
static ConstantBufferHandle* cbh;
static Camera3D cam;

static Vector<Mesh> meshes;

static float rotation;

static Vector<String> debug_msgs;

void Test3DScene::init()
{
	cam.pos = glm::vec3(0.0f, 0.0f, -3.0f);
	cam.worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cam.yaw = -90.0f;
	cam.pitch = 0.0f;
	cam.up = glm::vec3(0, 1, 0);
	cam.front = glm::vec3(0, 0, 1);

	cbh = new ConstantBufferHandle();
	cbh->name = "SceneData";

	target = gpu::device->create_target({
		.w = 1280,
		.h = 720
	});

	vb = gpu::device->create_buffer({
		.layout = { {3 , GL_FLOAT}, {3, GL_FLOAT }, {2, GL_FLOAT} },
		.bindFlags = gpu::BindFlags::BIND_VERTEX_BUFFER,
		.usageFlags = gpu::UsageFlags::STATIC_DRAW,
		.size = sizeof(cube_vertices),
		.data = cube_vertices,
	});
	
	cbh->buf = gpu::device->create_buffer({
		.bindFlags = gpu::BindFlags::BIND_CONSTANT_BUFFER,
		.usageFlags = gpu::UsageFlags::STATIC_DRAW,
		.size = sizeof(sd),
		.data = &sd,
	});

	shd = Asset::load_shader("3d");

	// creating model

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(Asset::get_asset_path("model/test.fbx"), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		Mesh m;

		aiMesh* mesh = scene->mMeshes[i];

		Vector<Vertex> vertices;
		Vector<unsigned int> indices;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex v;
			v.x = mesh->mVertices[i].x;
			v.y = mesh->mVertices[i].y;
			v.z = mesh->mVertices[i].z;

			v.nx = mesh->mNormals[i].x;
			v.ny = mesh->mNormals[i].y;
			v.nz = mesh->mNormals[i].z;
			
			if (mesh->mTextureCoords[0])
			{
				v.u = mesh->mTextureCoords[0][i].x;
				v.v = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				v.u = 0;
				v.v = 0;
			}

			vertices.push_back(v);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);

			
		}

		// iterate over materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			
			aiString path;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &path);


			const aiTexture* tex = scene->GetEmbeddedTexture(path.C_Str());
			
			//load texture with stb
			if (tex)
			{
				stbi_set_flip_vertically_on_load(false);
				int w, h, n;
				stbi_uc* data = stbi_load_from_memory((stbi_uc*)tex->pcData, tex->mWidth, &w, &h, &n, 4);
				m.mat.diff = gpu::device->create_texture({
					.data = data,
					.width = w,
					.height = h,
					});
				stbi_image_free(data);
			}
			
		}

		m.vb = gpu::device->create_buffer({
			.layout = { {3 , GL_FLOAT}, {3, GL_FLOAT }, {2, GL_FLOAT} },
			.bindFlags = gpu::BindFlags::BIND_VERTEX_BUFFER,
			.usageFlags = gpu::UsageFlags::STATIC_DRAW,
			.size = sizeof(Vertex) * vertices.size(),
			.data = vertices.data(),
			});
		
		m.ib = gpu::device->create_buffer({
			.layout = { {3 , GL_UNSIGNED_INT} },
			.bindFlags = gpu::BindFlags::BIND_INDEX_BUFFER,
			.usageFlags = gpu::UsageFlags::STATIC_DRAW,
			.size = sizeof(unsigned int) * indices.size(),
			.data = indices.data(),
			});
		
		m.indices = indices.size();

		meshes.push_back(m);
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

}

void Test3DScene::destroy()
{

}

void Test3DScene::update()
{
	Scene::update();



	float speed = 0.1f;

	if (Input::key_held(SDL_SCANCODE_W))
		cam.pos += cam.front * speed;
	if (Input::key_held(SDL_SCANCODE_S))
		cam.pos -= cam.front * speed;
	if (Input::key_held(SDL_SCANCODE_A))
		cam.pos -= cam.right * speed;
	if (Input::key_held(SDL_SCANCODE_D))
		cam.pos += cam.right * speed;

	
	if (Input::key_held(SDL_SCANCODE_LCTRL))
		cam.pos.y -= speed;
	if (Input::key_held(SDL_SCANCODE_LSHIFT))
		cam.pos.y += speed;

	cam.yaw += Input::get_mouse_pos_rel().x * -speed;
	cam.pitch += Input::get_mouse_pos_rel().y * -speed;
	
	if (cam.pitch> 89.0f)
		cam.pitch = 89.0f;
	if (cam.pitch < -89.0f)
		cam.pitch = -89.0f;


	cam.front.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
	cam.front.y = sin(glm::radians(cam.pitch));
	cam.front.z = sin(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
	cam.front = glm::normalize(cam.front);

	cam.right = glm::normalize(glm::cross(cam.worldUp, cam.front));
	cam.up = glm::normalize(glm::cross(cam.front, cam.right));


	rotation = -90;

	sd.mvp = glm::perspectiveLH<float>(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 10000.0f);
	sd.mvp *= glm::lookAtLH<float>(cam.pos, cam.pos + cam.front, cam.up);

	glm::mat4 model = glm::mat4(1.0f);

	//model = glm::rotate(model, rotation, glm::vec3(1, 0, 0));
	//model = glm::rotate(model, glm::radians(190.0f), glm::vec3(0, 0, 1));

	sd.mvp *= model;
	sd.model = model;


	gpu::device->update_buffer(cbh->buf, &sd, sizeof(sd));

	for (auto m : meshes)
	{
		DrawCall dc1;
		
		dc1.buffer = m.vb;
		dc1.index_buffer = m.ib;
		dc1.indices_count = m.indices;
		dc1.shader = shd;
		dc1.uniform = cbh;
		m.mat.diff ? dc1.textures = { m.mat.diff } : dc1.textures = {};

		rs.submit_drawcall(dc1);
	}

	debug_msgs.push_back("fps: " + std::to_string(1000 / Game::Instance->get_delta()));
}

void Test3DScene::render()
{
	THETA_PROFILE;

	ren->set_target(target);
	ren->clear(Vec4(0.0f, 0.0f, 0.0f, 0.0f));

	int y = 0;
	for (auto s : debug_msgs)
	{
		ren->draw_text(s, Renderer::DefaultFont, Vec2(10, 10 + y));
		y += 20;
	}

	debug_msgs.clear();

	Scene::render();

	rs.work();

	ren->set_target(Renderer::Viewport);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));
	ren->draw_target(target);
}

