#pragma once
#include "Engine/GameObject.h"

class Player;
class Shadow;


//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[99];
    int shadowCount_;
    bool isOpenWall_;
    

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

    //ぶつかるかどうか
    bool isCrash(int x , int y);

    void DownButton(int x, int y);

    void OpenWall();

    void CheckBrock(int find);
};

