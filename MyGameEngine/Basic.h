#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Engine/Fbx.h"
#include "Basic.h"
#include <string>
class Basic : public GameObject
{
public:
	Basic(GameObject* parent, const std::string& name);
	void CommonButtonDown();
};

