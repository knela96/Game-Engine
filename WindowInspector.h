#ifndef INSPECTOR_H
#define INSPECTOR_H
#include "Module.h"
#include "Application.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>

class GameObject;

class WindowInspector : public Module
{
public:
	WindowInspector(Application* app, bool start_enabled = true);
	~WindowInspector();

	bool Start();
	bool Draw();
	update_status Update(float dt);
	bool Cleanup();
	bool isEnabled();

private:
	bool enabled = false;
	bool unFold = false;
	bool open_transform = true;
	bool open_normals = true;
	bool open_mesh_info = true;
	bool open_material = true;
	bool s = false;
public:
	bool to_static = false;
	GameObject* active_gameObject = nullptr;
};
#endif
