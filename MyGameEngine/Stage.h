#pragma once
#include "Engine/GameObject.h"

class Player;
class Shadow;


//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[7];
    bool isOpenWall_;
    int shadowCount_;

    Player* pPlayer_;
    Shadow* pShadow[5];

public:

    int map_[20][10];
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
};

