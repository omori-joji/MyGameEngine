#pragma once
#include "Transform.h"
#include "Texture.h"

//エフェクトに使う画像のデータ
struct VFXTextureData
{
	std::string fileName;	//ファイル名
	Texture* pTexture;		//テクスチャ
	DWORD width, height;	//画像の中に何個並んでるか
};


//頂点情報
struct VERTEX
{
	XMVECTOR position;	//位置
	XMVECTOR uv;		//UV座標
};


//表示中の１個のエフェクトを管理するクラス
class VFX
{
	VFXTextureData* pTexData_;	//テクスチャデータ
	Transform transform_;		//表示する位置等
	float frame_;				//今何コマ目を表示してるか
	float speed_;				//再生速度
	bool isLoop_;				//ループするかどうか


public:
	//コンストラクタ
	VFX();

	//エフェクトを１個作成
	//引数：data		使用する画像のデータ
	//引数：transform	位置やサイズ
	//引数：speed		アニメーション速度（大きい方が早い）
	//引数：isLoop		true→ループ再生　／　false→最後までアニメーションしたら自動で消える
	void Create(VFXTextureData* data, Transform transform, float speed, bool isLoop);

	//アニメーションを進める
	//戻値：ループなしのエフェクトで最後までアニメーションしたらtrue
	bool Update();

	//描画
	void Draw();
};

