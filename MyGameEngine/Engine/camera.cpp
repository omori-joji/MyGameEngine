#include "Camera.h"

namespace Camera
{
	XMVECTOR position_;		//カメラの位置（視点）
	XMVECTOR target_;		//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列
}

//初期化
void Camera::Initialize()
{
	//カメラをステージの中央に出す処理
	//横
	//縦
	int x = 28;
	int y = 23;

	//初期値を設定
	//カメラの位置
	position_ = XMVectorSet((x / 2), (y / 2), -25, 0);

	//カメラの焦点
	target_ = XMVectorSet((x/2), (y / 2), 0, 0);

	//プロジェクション行列の処理を実行する関数
	//引数は(画角, アスペクト比, この値より近いものは映らない, この値より遠いものは映らない)
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);

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