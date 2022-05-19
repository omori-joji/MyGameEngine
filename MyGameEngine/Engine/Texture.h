#pragma once
#include <d3d11.h>
#include "string"

using namespace std;

class Texture
{
	//テクスチャを描画するときに必要なのでメンバ変数にする
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;

public:
	Texture();
	~Texture();
	HRESULT Load(std::string fileName);
	void Release();

	ID3D11SamplerState* GetSampler() { return pSampler_; }
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }
};
