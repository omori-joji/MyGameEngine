#include "Camera.h"

//名前空間
namespace Camera
{
	XMVECTOR position_;		//カメラの位置（視点）
	XMVECTOR target_;		//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列

	auto yscale = 0.9f;
	auto viewWidht = 10.0f;
	auto viewHeght = viewWidht * yscale;
	auto nearZ = 1.0f / (1000.0f - 0.3f);
	auto farZ = 1000.0f;

	//カメラをステージの中央に出す処理
	//Stageの大きさ
	const int VERTICAL_ = 23;
	const int BESIDE_ = 28;

	//カメラのZ軸の位置
	const int CAMERA_POSITION_ = -25;	//奥行
}

//初期化
void Camera::Initialize()
{
	//初期値を設定
	//カメラの位置
	position_ = XMVectorSet((BESIDE_ / 2), (VERTICAL_ / 2), CAMERA_POSITION_, 0);

	//カメラの焦点
	target_ = XMVectorSet((BESIDE_ / 2), (VERTICAL_ / 2), 0, 0);

	//プロジェクション行列の処理を実行する関数
	//引数は(画角, アスペクト比, この値より近いものは映らない, この値より遠いものは映らない)
	projMatrix_ = XMMatrixOrthographicLH(viewWidht, viewHeght, nearZ, farZ);//2D投影
	//projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);//3D投影

	//ビュー行列の作成
	//引数は(カメラの位置, 焦点, 上方向のベクトル)
	//カメラの位置は変わることがないのでInitializeで処理しておく
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//更新
void Camera::Update()
{
}

//位置を設定
void Camera::SetPosition(XMVECTOR position)
{
	//引数に渡されたpositionに位置を変更する
	position_ = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	//位置を渡す
	SetPosition(XMLoadFloat3(&position));
}

//位置と焦点の値を引数に渡す関数
XMFLOAT3 Camera::GetPosition()
{
	XMFLOAT3 f;
	XMVECTOR v = XMLoadFloat3(&f);
	return f;
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

//焦点のアドレスをSetTargetの引数に渡す
void Camera::SetTarget(XMFLOAT3 target)
{
	SetTarget(XMLoadFloat3(&target));
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}


