#pragma once
#include "Transform.h"
#include "Texture.h"

struct VFXTextureData
{
	std::string fileName;
	Texture* pTexture;
	DWORD width, height;
};

struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class VFX
{
	VFXTextureData* pTexData_;	//テクスチャデータ
	Transform transform_;		//表示する位置等
	float frame_;				//今何コマ目を表示してるか
	float speed_;				//再生速度
	bool isLoop_;				//ループするかどうか


public:
	VFX();
	void Create(VFXTextureData* data, Transform transform, float speed, bool isLoop);
	bool Update();
	void Draw();
};

