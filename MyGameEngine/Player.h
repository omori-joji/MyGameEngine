#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Shadow.h"


class Shadow;

//Playerを管理するクラス
class Player : public GameObject
{

    const float SPEED_;                     //Playerの移動速度
    const float WIDTH_;                     //Playerの幅
    const float HEIGHT_;                    //Playerの高さ
    const float MARGIN_;                    //当たり判定の遊び
    const float BLOCK_SIZE_;                //ブロックのサイズ
    const float MAX_JUMP_;                  //ジャンプの上限
    const float BACK_POSITION_LEFT_;        //触れていたら位置を戻す値
    const float BACK_POSITION_RIGHT_;       //触れていたら位置を戻す値
    const float BACK_POSITION_UP_;          //触れていたら位置を戻す値
    const float BACK_POSITION_DOWN_;        //触れていたら位置を戻す値
    const float GRAVITY_;                   //重力の値
    const float DROP_DOWN_;                 //Playerの下に何もなければ下に落ちるための定数
    const int RESET_VALU_;                  //初期化用の定数
    const int PLAYER_FOOT_;                 //Playerの足元を見るためにY軸を-1する定数
    const int RUN_MODEL_;                   //走っているモデルの番号
    const int STANDING_MODEL_;              //立っているモデルの番号

    int hModel_[2][2];                      //Playerのモデル番号を格納する多次元配列
    int direction_;                         //プレイヤーの向きの番号
    int modelNumber_;                       //走っているモデルの番号
    float move_;                            //Y軸の移動

    bool isJump_;                           //ジャンプしているか
    bool isPastButton;                      //さっき踏んでいるか

    Stage* pStage_;                         //ステージの情報を入れるポインタ

    //Playerの向き
    enum Direction
    {
        DIR_RIGHT,                          //右
        DIR_LEFT,                           //左
    };

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

    //Find処理をすべてまとめる関数
    void AllFind();

    //Playerの操作をまとめる関数
    void PlayerMove();

    //Playyerの当たり判定をまとめる関数
    void PlayerCollision();

    //Playerがボタンを踏んでいるか、ボタンから離れたかを判断する関数
    void FootButtonCheck();

    //Playerの走っているモデル番号を返す関数
    int GetModelNumber();

    //Player向きのモデル番号を返す関数
    int GetDirection();
};
