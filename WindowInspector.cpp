#include "Application.h"
#include "WindowInspector.h"

WindowInspector::WindowInspector(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	enabled = true;
}


WindowInspector::~WindowInspector()
{
}


bool WindowInspector::Start()
{
	return true;
}

update_status WindowInspector::PreUpdate(float dt) {
	return UPDATE_CONTINUE;
}

update_status WindowInspector::PostUpdate(float dt) {
	return UPDATE_CONTINUE;
}

bool WindowInspector::Draw()
{
	ImGui::SetNextWindowSizeConstraints(ImVec2(400, -1), ImVec2(1000, -1));
	ImGui::Begin("Inspector"); 
	ImGui::SetNextTreeNodeOpen(open_transform);
	if (ImGui::CollapsingHeader("Transform"))
	{
		vec3 pos;
		vec3 rot;
		vec3 scale;
		ImGui::Text("Position:"); 
		ImGui::SameLine(/*ImGui::GetWindowContentRegionWidth() - 240*/); ImGui::PushItemWidth(60); ImGui::DragFloat("X", &pos.x, 0.005f);
		ImGui::SameLine(/*ImGui::GetWindowContentRegionWidth() - 160*/); ImGui::PushItemWidth(60); ImGui::DragFloat("Y", &pos.y, 0.005f);
		ImGui::SameLine(/*ImGui::GetWindowContentRegionWidth() - 80*/); ImGui::PushItemWidth(60); ImGui::DragFloat("Z", &pos.z, 0.005f);

		ImGui::Text("Rotation:");
		ImGui::SameLine(); ImGui::PushItemWidth(60); ImGui::DragFloat("X", &rot.x, 0.005f);
		ImGui::SameLine(); ImGui::PushItemWidth(60); ImGui::DragFloat("Y", &rot.y, 0.005f);
		ImGui::SameLine(); ImGui::PushItemWidth(60); ImGui::DragFloat("Z", &rot.z, 0.005f);

		ImGui::Text("Scale:   ");
		ImGui::SameLine(); ImGui::PushItemWidth(60); ImGui::DragFloat("X", &scale.x, 0.005f);
		ImGui::SameLine(); ImGui::PushItemWidth(60); ImGui::DragFloat("Y", &scale.y, 0.005f);
		ImGui::SameLine(); ImGui::PushItemWidth(60); ImGui::DragFloat("Z", &scale.z, 0.005f);

		//ImGui::DragFloat3("drag float3", vec4f, 0.01f, 0.0f, 1.0f);

	}
	ImGui::End();
	return false;
}

bool WindowInspector::Cleanup()
{
	return true;
}

bool WindowInspector::isEnabled()
{
	return enabled;
}
