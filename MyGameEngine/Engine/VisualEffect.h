#pragma once
#include<string>
#include<vector>

#include "VFX.h"

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	float uvLeft, uvTop, uvWidth, uvHeight;
};

namespace VisualEffect
{
	extern ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	extern ID3D11Buffer* pIndexBuffer_;    //�C���f�b�N�X�o�b�t�@
	extern ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@


	extern ID3D11VertexShader* pVertexShader;	//���_�V�F�[�_�[
	extern ID3D11PixelShader* pPixelShader;		//�s�N�Z���V�F�[�_�[
	extern ID3D11InputLayout* pVertexLayout;	//���_�C���v�b�g���C�A�E�g
	extern ID3D11RasterizerState* pRasterizerState;	//���X�^���C�U�[



	void Initialize();

	int Load(std::string fileName, DWORD width, DWORD height);

	void Add(int hVfx, Transform transform, float speed, bool isLoop);

	void Update();
	void Draw();
	void Release();
};

