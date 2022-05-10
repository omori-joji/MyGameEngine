#pragma once
#include "Transform.h"
#include "Fbx.h"
#include "FbxParts.h"
#include "Texture.h"
#include<string>

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx;
		Transform transform;
		std::string fileName;
	};



	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void AllRelease();
};

