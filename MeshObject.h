#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec4 Colors;
	vec2 TexCoords;
};

class aiMesh;

class MeshObject : public GameObject
{
public:
	MeshObject(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture*> textures, string name);
	~MeshObject();

	bool SetupBuffers();

	void Draw();

	const vec3 getNormal(vec3 p1, vec3 p2, vec3 p3) const;

	void CleanUp();

	void DebugNormals() const;

	void DrawBox() const;
public:
	vector<Vertex> vertices;
	vector<uint> indices;
	uint VAO;

private:
	uint VBO, EBO;
};

