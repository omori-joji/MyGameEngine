#pragma once
#include "GameObject.h"
#include "Common.h"

//ゲームに登場するシーン
enum SCENE_ID
{
	SCENE_ID_STAGE1,//STAGE1
	SCENE_ID_STAGE2,//STAGE2
	SCENE_ID_STAGE3,//STAGE3
	SCENE_ID_STAGE4,//STAGE4
	SCENE_ID_CLEAR,//クリア画面
	SCENE_ID_TITLE,//一番最初のタイトル
	SCENE_ID_DEBUG,
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
	void Initialize() override;				//初期化
	void Update() override;					//更新
	void Draw() override;					//描画
	void Release() override;				//解放

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	//いろんなとこで使うのでpublicにしておく
	void ChangeScene(SCENE_ID next);
	SCENE_ID SetnextSceneID(SCENE_ID x);	//次のシーンを登録する関数
	SCENE_ID nextSceneID_;					//次のシーン
private:
	SCENE_ID currentSceneID_;				//現在のシーン
};