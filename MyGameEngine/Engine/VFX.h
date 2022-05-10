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
	VFXTextureData* pTexData_;	//�e�N�X�`���f�[�^
	Transform transform_;		//�\������ʒu��
	float frame_;				//�����R�}�ڂ�\�����Ă邩
	float speed_;				//�Đ����x
	bool isLoop_;				//���[�v���邩�ǂ���


public:
	VFX();
	void Create(VFXTextureData* data, Transform transform, float speed, bool isLoop);
	bool Update();
	void Draw();
};

