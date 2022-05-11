#pragma once

#include<string>
#include<vector>
#include "VFX.h"

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	float		uvLeft, uvTop, uvWidth, uvHeight;	//�A�j���[�V�����̂��߂�UV���W�����炷���߂̏��
};


namespace VisualEffect
{
	extern ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	extern ID3D11Buffer* pIndexBuffer_;		//�C���f�b�N�X�o�b�t�@
	extern ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@


	extern ID3D11VertexShader*		pVertexShader;		//���_�V�F�[�_�[
	extern ID3D11PixelShader*		pPixelShader;		//�s�N�Z���V�F�[�_�[
	extern ID3D11InputLayout*		pVertexLayout;		//���_�C���v�b�g���C�A�E�g
	extern ID3D11RasterizerState*	pRasterizerState;	//���X�^���C�U�[


	//������(CreatePolygon��ShaderSetup���Ăԁj
	void Initialize();

	//�|���S�����\������f�[�^�̏���
	void CreatePolygon();

	//�V�F�[�_�[�̃R���p�C����
	void ShaderSetup();

	//�g�p����摜�̃��[�h
	//�����FfileName	�t�@�C����
	//�����Fwidth		���̉摜�̒��ŁA���ɉ��R�}����ł邩
	//�����Fheight		���̉摜�̒��ŁA�c�ɉ��R�}����ł邩
	//�ߒl�F���̉摜�Ɋ��蓖�Ă���ԍ�
	int Load(std::string fileName, DWORD width, DWORD height);

	//�G�t�F�N�g��ǉ�
	//�����FhVfx		�g�p����摜�ԍ�
	//�����Ftransform	�ʒu��T�C�Y
	//�����Fspeed		�A�j���[�V�������x�i�傫�����������j
	//�����FisLoop		true�����[�v�Đ��@�^�@false���Ō�܂ŃA�j���[�V���������玩���ŏ�����
	void Add(int hVfx, Transform transform, float speed, bool isLoop);

	//�\�����̃G�t�F�N�g�̃A�j���[�V������i�߂�
	void Update();

	//�S�G�t�F�N�g�̕`��
	void Draw();

	//�������
	void Release();
};

