#pragma once
#include "Engine/GameObject.h"

//クラスの前方宣言
class Player;
class Shadow;


//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[500];
    int shadowCount_;
    int timeCount_;

    bool isOpenWall_;
    bool isBlinking_;
    

    Player* pPlayer_;
    Shadow* pShadow[6];




public:


    int map_[20][12];
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

    void OpenWall();

    void CheckBlock(int find , bool which);

    void Blinking(int blockNum, int time);

    void WarpBlock(int x, int y);
};

