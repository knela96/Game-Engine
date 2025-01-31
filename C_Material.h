#pragma once
#include "Component.h"

class C_Material : public Component
{
public:
	C_Material(GameObject* gameobject, Component_Type type);
	~C_Material();

	bool Enable();
	void Update();
	bool Disable();
	void Save(const char* gameObject, json &file);
	void Load(const char* gameObject, const json &file);

public:
	bool open_material = true;
};