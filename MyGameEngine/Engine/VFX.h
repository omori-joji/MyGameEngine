#pragma once
#include "Transform.h"
#include "Texture.h"

//�G�t�F�N�g�Ɏg���摜�̃f�[�^
struct VFXTextureData
{
	std::string fileName;	//�t�@�C����
	Texture* pTexture;		//�e�N�X�`��
	DWORD width, height;	//�摜�̒��ɉ�����ł邩
};


//���_���
struct VERTEX
{
	XMVECTOR position;	//�ʒu
	XMVECTOR uv;		//UV���W
};


//�\�����̂P�̃G�t�F�N�g���Ǘ�����N���X
class VFX
{
	VFXTextureData* pTexData_;	//�e�N�X�`���f�[�^
	Transform transform_;		//�\������ʒu��
	float frame_;				//�����R�}�ڂ�\�����Ă邩
	float speed_;				//�Đ����x
	bool isLoop_;				//���[�v���邩�ǂ���


public:
	//�R���X�g���N�^
	VFX();

	//�G�t�F�N�g���P�쐬
	//�����Fdata		�g�p����摜�̃f�[�^
	//�����Ftransform	�ʒu��T�C�Y
	//�����Fspeed		�A�j���[�V�������x�i�傫�����������j
	//�����FisLoop		true�����[�v�Đ��@�^�@false���Ō�܂ŃA�j���[�V���������玩���ŏ�����
	void Create(VFXTextureData* data, Transform transform, float speed, bool isLoop);

	//�A�j���[�V������i�߂�
	//�ߒl�F���[�v�Ȃ��̃G�t�F�N�g�ōŌ�܂ŃA�j���[�V����������true
	bool Update();

	//�`��
	void Draw();
};

