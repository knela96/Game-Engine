#ifndef IMPORTER_H
#define IMPORTER_H
#include "Application.h"
#include "Module.h"
#include "Shader.h"

#include <vector>

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64



enum aiTextureType;

class GameObject;
struct Texture;
class aiMesh;
class aiScene;
class aiMaterial;

class ModuleImporter : public Module
{
public:
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();
	
	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	update_status Update(float dt);
	bool Draw();

	bool CleanUp();

	bool Load(const char * path);

	GameObject* ProcessMesh(aiMesh * new_mesh,const aiScene * scene = NULL);

	void PushObj(aiMesh* mesh);

	uint LoadTexture(const char * path, uint & texture);

	vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type);

public:
	std::vector<GameObject*> gameObjects;
	std::vector<Texture> stored_textures;
	
private:
	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	bool enabled;
	uint Texture_id = 0;
public: 
	Shader* shader;

};
#endif IMPORTER_H
