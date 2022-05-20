#pragma once
#include <DirectXMath.h>

//名前空間
using namespace DirectX;

//位置、向き、拡大率などを管理するクラス
class Transform
{
	XMMATRIX matTranslate_;		//移動行列
	XMMATRIX matRotate_;		//回転行列	
	XMMATRIX matScale_;			//拡大行列

public:
	Transform();				//コンストラクタ
	~Transform();				//デストラクタ
	void Calclation();			//各行列の計算

	//これの値を変えて各行列をかけるのでpublicにしておく
	XMFLOAT3  position_;		//位置
	XMFLOAT3  rotate_;			//向き
	XMFLOAT3  scale_;			//拡大率

	//ゲッター
	XMMATRIX GetWorldMatrix();	//ワールド行列を渡すゲッター
	XMMATRIX GetNormalmatrix();	//正規行列を渡すゲッター
};