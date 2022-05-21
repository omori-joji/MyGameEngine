#pragma once
#include "Texture.h"
#include "Transform.h"
#include "FbxParts.h"
#include "Fbx.h"
#include<string>

//クラスの前方宣言
class Transform;

//名前空間
namespace Model
{
	//ModelData型の構造体
	struct ModelData
	{
		Fbx* pFbx;				//FBXクラス
		Transform transform;	//Transformクラス
		std::string fileName;	//ロードするファイル名
	};

	int Load(std::string fileName);						//fbxファイルをロードする関数。戻り値はモデル番号。引数はロードしたいファイル名
	void SetTransform(int hModel, Transform transform);	//位置、回転、拡縮を決める関数。引数は(モデル番号、位置回転拡縮の値)
	void Draw(int hModel);								//描画。引数
	void AllRelease();									//解放処理
};

