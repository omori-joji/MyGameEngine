#pragma once
#include <d3d11.h>
#include "string"
using namespace std;

class Texture
{
	//テクスチャを描画するときに必要なのでメンバ変数にする
	ID3D11SamplerState* pSampler_;			//サンプラー
	ID3D11ShaderResourceView* pSRV_;		//リソースビュー

public:
	Texture();								//コンストラクタ
	~Texture();								//デストラクタ
	void Release();							//解放処理
	HRESULT Load(std::string fileName);		//ファイルをロードする関数
	ID3D11SamplerState* GetSampler() { return pSampler_; }	//サンプラーを渡すゲッター
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }	//リソースビューわ渡すゲッター
};
