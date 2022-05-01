#pragma once
#include "GameObject.h"
#include "Common.h"

//ゲームに登場するシーン
enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_STAGE1,
	SCENE_ID_STAGE2,
	SCENE_ID_STAGE3,
	SCENE_ID_STAGE4,
	SCENE_ID_CLEAR,
	SCENE_ID_CLEDIT,
	SCENE_ID_TITLE,
	SCENE_ID_TITLE2,
	SCENE_ID_SETUMEI,
};

//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//コンストラクタ
	//引数：parent	親オブジェクト（基本的にゲームマネージャー）
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);

	SCENE_ID SetnextSceneID(SCENE_ID x);
	SCENE_ID nextSceneID_;		//次のシーン

private:

	SCENE_ID currentSceneID_;	//現在のシーン
	
};