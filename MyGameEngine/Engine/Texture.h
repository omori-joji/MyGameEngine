#pragma once
#include <d3d11.h>
#include "string"
using namespace std;

class Texture
{
	//�e�N�X�`����`�悷��Ƃ��ɕK�v�Ȃ̂Ń����o�ϐ��ɂ���
	ID3D11SamplerState* pSampler_;			//�T���v���[
	ID3D11ShaderResourceView* pSRV_;		//���\�[�X�r���[

public:
	Texture();								//�R���X�g���N�^
	~Texture();								//�f�X�g���N�^
	void Release();							//�������
	HRESULT Load(std::string fileName);		//�t�@�C�������[�h����֐�
	ID3D11SamplerState* GetSampler() { return pSampler_; }	//�T���v���[��n���Q�b�^�[
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }	//���\�[�X�r���[��n���Q�b�^�[
};
