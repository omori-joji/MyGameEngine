#include "Direct3D.h"
#include <DirectXMath.h>

//名前空間
using namespace DirectX;

namespace Camera
{
	void Initialize();								//初期化（プロジェクション行列作成）
	void Update();									//更新（ビュー行列作成）
	void SetPosition(DirectX::XMVECTOR position);	//視点（カメラの位置）を設定
	void SetPosition(XMFLOAT3 position);			//SetPositionにアドレスを渡すセッター
	void SetTarget(XMVECTOR target);				//焦点（見る位置）を設定
	void SetTarget(XMFLOAT3 target);				//SetTargetにアドレスを渡すセッター
	XMFLOAT3 GetPosition();							//位置と焦点の値を渡すゲッター
	XMMATRIX GetViewMatrix();						//ビュー行列を取得
	XMMATRIX GetProjectionMatrix();					//プロジェクション行列を取得
};

