#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	
	uint s_vertices;
	uint s_normals;

	float num_vertices;
	uint iboId = 0;
	uint vboId = 0;


public:
};
