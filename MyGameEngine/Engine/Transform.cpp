#include "Transform.h"

//コンストラクタ
Transform::Transform():
	matTranslate_(XMMatrixIdentity()),
	matRotate_(XMMatrixIdentity()),
	matScale_(XMMatrixIdentity()),

	position_(XMFLOAT3(0,0,0)),
    rotate_(XMFLOAT3(0, 0, 0)),
	scale_(XMFLOAT3(1, 1, 1))
{
}

//デストラクタ
Transform::~Transform()
{
}

//移動、回転、拡大行列(ワールド行列)をかける関数
void Transform::Calclation()
{
	//移動行列
	matTranslate_ = XMMatrixTranslation(position_.x,position_.y,position_.z);

	//回転
	XMMATRIX mX, mY, mZ;
	mX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));   
	mY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));   
	mZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = mX * mY * mZ;

	//拡大縮小
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

//ワールド行列を渡すゲッター
//戻り値は行列の結果を返すのでXMMATRIXにする
XMMATRIX Transform::GetWorldMatrix()
{
	//ワールド行列を返す
	return  matScale_ * matRotate_ * matTranslate_;
}

//正規行列を渡すゲッター
//戻り値は行列の結果を返すのでXMMATRIXにする
XMMATRIX Transform::GetNormalmatrix()
{
	XMVECTOR det;
	return matRotate_ * XMMatrixInverse(&det, matScale_);
}
