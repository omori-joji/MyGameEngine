#pragma once

#include<string>
#include<vector>
#include "VFX.h"

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	float		uvLeft, uvTop, uvWidth, uvHeight;	//アニメーションのためにUV座標をずらすための情報
};


namespace VisualEffect
{
	extern ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	extern ID3D11Buffer* pIndexBuffer_;		//インデックスバッファ
	extern ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ


	extern ID3D11VertexShader*		pVertexShader;		//頂点シェーダー
	extern ID3D11PixelShader*		pPixelShader;		//ピクセルシェーダー
	extern ID3D11InputLayout*		pVertexLayout;		//頂点インプットレイアウト
	extern ID3D11RasterizerState*	pRasterizerState;	//ラスタライザー


	//初期化(CreatePolygonとShaderSetupを呼ぶ）
	void Initialize();

	//ポリゴンを構成するデータの準備
	void CreatePolygon();

	//シェーダーのコンパイル等
	void ShaderSetup();

	//使用する画像のロード
	//引数：fileName	ファイル名
	//引数：width		その画像の中で、横に何コマ並んでるか
	//引数：height		その画像の中で、縦に何コマ並んでるか
	//戻値：その画像に割り当てられる番号
	int Load(std::string fileName, DWORD width, DWORD height);

	//エフェクトを追加
	//引数：hVfx		使用する画像番号
	//引数：transform	位置やサイズ
	//引数：speed		アニメーション速度（大きい方が早い）
	//引数：isLoop		true→ループ再生　／　false→最後までアニメーションしたら自動で消える
	void Add(int hVfx, Transform transform, float speed, bool isLoop);

	//表示中のエフェクトのアニメーションを進める
	void Update();

	//全エフェクトの描画
	void Draw();

	//解放処理
	void Release();
};

