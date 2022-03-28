#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Stage.h"


//Playerを管理するクラス
class Player : public GameObject
{
    //constは定数宣言で使う
    const float SPEED;//Playerの移動速度
    const float WIDTH;//Playerの幅
    const float HEIGHT;//Playerの高さ
    const float MARGIN;//当たり判定の遊び
    const float BLOCK_SIZE;//ブロックのサイズ
    const float MAX_JUMP;//ジャンプの上限
    bool isJump;
    float move_; //重力
    float gravity_;

    //Fbx* pFbx;
    int hModel_;
    Stage* pStage_;
    XMFLOAT3 prevPos_; //1フレーム前の位置

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /*bool isCrash(int x, int y);*/
};
