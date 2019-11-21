#ifndef IMPORTER_H
#define IMPORTER_H
#include "Application.h"
#include "Module.h"
#include "Shader.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "Globals.h"
#include <vector>

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

enum aiTextureType;

class MeshObject;
class aiNode;
class aiScene;
struct Texture;
class aiMesh;
class aiScene;
class aiMaterial;

enum FileFormats {
	NONE = -1,
	FBX,
	PNG,
	DDS
};

class ModuleImporter : public Module
{
public:
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();
	
	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	update_status Update(float dt);

	const string getFileExt(const string & s);

	string getRootPath(const string & s);

	const string getFileName(const string & s);

	bool CleanUp();

	bool LoadFile(const char * path);

	bool Load(const char * path);

	void ImportMesh(aiNode * node, aiScene *scene, string *FileName, string *str);

	GameObject * LoadHierarchy(aiNode * node, aiScene * scene, string * FileName, string * str, GameObject * parent);

	GameObject * ProcessMesh(aiMesh * mesh, string * path = nullptr, const char* fileName = nullptr, const aiScene * scene = NULL);

public:
	std::vector<Texture*> stored_textures;
	
private:

	bool enabled;
	uint Texture_id = 0;
public: 
	Shader* shader;
	uint checkImage_id;


public: //OUR OWN FILE FORMAT HERE

	struct weOBJ {
		std::string    name;
		float4x4       transform = float4x4::identity;
		uint           parent = 0;
		RID            mesh = 0;
		RID            material = 0;
	};


	

};
#endif IMPORTER_H
