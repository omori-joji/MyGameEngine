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
    const float SPEED;      //Playerの移動速度
    const float WIDTH;      //Playerの幅
    const float HEIGHT;     //Playerの高さ
    const float MARGIN;     //当たり判定の遊び
    const float BLOCK_SIZE; //ブロックのサイズ
    const float MAX_JUMP;   //ジャンプの上限
    const float BACK_POSITION_LEFT_;
    const float BACK_POSITION_RIGHT_;
    const float BACK_POSITION_UP_;
    const float BACK_POSITION_DOWN_;
    const float GRAVITY_;
    const float DROP_DOWN_;
    const int RESET_VALU_;
    const int PLAYER_FOOT_;


    bool isJump_;            //ジャンプしているか
    float move_;            //Y軸の移動
   



    int hModel_Left[2];
    int hModel_Right[2];

    Stage* pStage_;


public:
    int plyerRightMoveCount;
    int plyerLeftMoveCount;
    bool isDirection;


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

    //Find処理をすべてまとめる関数
    void AllFind();

    //Playerの操作をまとめる関数
    void PlayerMove();

    //Playyerの当たり判定をまとめる関数
    void PlayerCollision();
};
