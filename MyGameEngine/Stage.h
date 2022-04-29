#pragma once
#include "Engine/GameObject.h"

//クラスの前方宣言
class Player;
class Shadow;
class SceneManager;


//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[500];
    int shadowCount_;
    int timeCount_;
    int hSound_;
    int verticalValu;
    int besideValu;

    bool isOpenWall_;
    bool isBlinking_;
    bool isWarp_;
    bool isdoubleButton1_;
    bool isdoubleButton2_;

    Player* pPlayer_;
    SceneManager* pSceneManager_;
    Shadow* pShadow[6];




public:

    int memoryBlock_;

    int map_[28][23];
    XMFLOAT3 stertPos;



public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void ModelLoad();

    //ぶつかるかどうか
    bool isCrash(int x , int y);

    void DownButton(int x, int y);

    void CheckBlock(int find , bool which);

    void Blinking(int blockNum, int time);

    bool WarpBlockEnter(int x, int y);

    void GoalCol(int x, int y);

    void WarpBlockExit(int getX, int getY);
};

