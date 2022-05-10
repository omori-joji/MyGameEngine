#pragma once
#include<string>
#include<vector>

#include "VFX.h"

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	float uvLeft, uvTop, uvWidth, uvHeight;
};

namespace VisualEffect
{
	extern ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	extern ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	extern ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ


	extern ID3D11VertexShader* pVertexShader;	//頂点シェーダー
	extern ID3D11PixelShader* pPixelShader;		//ピクセルシェーダー
	extern ID3D11InputLayout* pVertexLayout;	//頂点インプットレイアウト
	extern ID3D11RasterizerState* pRasterizerState;	//ラスタライザー



	void Initialize();

	int Load(std::string fileName, DWORD width, DWORD height);

	void Add(int hVfx, Transform transform, float speed, bool isLoop);

	void Update();
	void Draw();
	void Release();
};

