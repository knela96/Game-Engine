#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "FrameBuffer.h"

#define MAX_LIGHTS 8



class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void checkRenderFilters();

	static void SetSDLIcon(SDL_Window * window);



public:
	FrameBuffer* fbo;
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool depth_active = true;
	bool cullface_active = true;
	bool lighting_active = true;
	bool color_active = true;
	bool texture_active = true;
	bool wireframe_active = false;



};