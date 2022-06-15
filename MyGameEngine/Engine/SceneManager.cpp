#include "../Game/Stage.h"
#include "../Game/Result.h"
#include "../Game/Title.h"
#include "sceneManager.h"
#include "Model.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"),
	nextSceneID_(),
	currentSceneID_()
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<Title>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Model::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		   case SCENE_ID_STAGE1: Instantiate<Stage>(this); break;	//STAGE1
		   case SCENE_ID_STAGE2: Instantiate<Stage>(this); break;	//STAGE2
		   case SCENE_ID_STAGE3: Instantiate<Stage>(this); break;	//STAGE3
		   case SCENE_ID_STAGE4: Instantiate<Stage>(this); break;	//STAGE4
		   case SCENE_ID_TITLE: Instantiate<Title>(this); break;	//タイトル画面
		   case SCENE_ID_CLEAR: Instantiate<Result>(this); break;	//クリア画面
		   case SCENE_ID_DEBUG: Instantiate<Stage>(this); break;	//デバッグ用
		}
		//次のシーンを現在のシーンに入れ替える
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}

//次のシーンを登録する関数
SCENE_ID SceneManager::SetnextSceneID(SCENE_ID x)
{
	x = nextSceneID_;
	return x;
}
