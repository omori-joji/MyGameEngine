#pragma once
#include "Texture.h"
#include "Transform.h"
//#include "FbxParts.h"
#include "Fbx.h"
#include<string>

//�N���X�̑O���錾
class Transform;

//���O���
namespace Model
{
	//ModelData�^�̍\����
	struct ModelData
	{
		Fbx* pFbx;				//FBX�N���X
		Transform transform;	//Transform�N���X
		std::string fileName;	//���[�h����t�@�C����
	};

	int Load(std::string fileName);						//fbx�t�@�C�������[�h����֐��B�߂�l�̓��f���ԍ��B�����̓��[�h�������t�@�C����
	void SetTransform(int hModel, Transform transform);	//�ʒu�A��]�A�g�k�����߂�֐��B������(���f���ԍ��A�ʒu��]�g�k�̒l)
	void Draw(int hModel);								//�`��B����
	void AllRelease();									//�������
};

