#ifndef MODULEGUI_H
#define MODULEGUI_H
#include "Module.h"
#include "Application.h"


#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>

class ModuleGUI : public Module {

public:


	ModuleGUI(Application* app, bool start_enabled = true);
	~ModuleGUI();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void CreateMenuBar();

	void ShowConsole();

	void ShowWindowSettings();

	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);
	ImGuiIO* test_io = nullptr;
	ImGuiIO* io = nullptr;
	bool show_demo_window = false;
	bool show_another_window = false;
private:
	bool openConsole = false;
	bool openWindowSettings = false;
	bool fullscreen = false;
	bool borderless = false;
	bool resizable = false;
	bool fulldesktop = false;

	int screen_width = SCREEN_WIDTH;
	int screen_height = SCREEN_WIDTH;
	bool p_open = true;
};

#endif
