#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Shadow.h"

class Shadow;

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
    bool isJump; //ジャンプしているか
    bool isDirection;
    float move_; //Y軸の移動
    float gravity_; //重力
   



    int hModel_Left[2];
    int hModel_Right[2];
    int plyerRightMoveCount;
    int plyerLeftMoveCount;

    Stage* pStage_;


public:




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

};
