#include "sceneManager.h"
#include "../TestScene.h"
#include "../PlayScene.h"
#include "Model.h"
#include "../Stage.h"
#include "../Clear.h"
#include "../Title.h"
#include "../Setumei.h"


//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
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
		//Audio::AllRelease();
		Model::AllRelease();
		//Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		   case SCENE_ID_STAGE1: Instantiate<Stage>(this); break;
		   case SCENE_ID_STAGE2: Instantiate<Stage>(this); break;;
		   case SCENE_ID_STAGE3: Instantiate<Stage>(this); break;
		   case SCENE_ID_STAGE4: Instantiate<Stage>(this); break;
		   case SCENE_ID_CLEAR: Instantiate<Clear>(this); break;
		   case SCENE_ID_CLEDIT: Instantiate<Clear>(this); break;
		   case SCENE_ID_SETUMEI: Instantiate<Setumei>(this); break;
		   case SCENE_ID_TITLE2: Instantiate<Title>(this); break;
		}

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

SCENE_ID SceneManager::SetnextSceneID(SCENE_ID x)
{
	x = nextSceneID_;
	return x;
}
