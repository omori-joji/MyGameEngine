#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Stage.h"




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

    int direction_;                         //プレイヤーの向きの番号
    int modelNumber_;                       //走っているモデルの番号
    float move_;                            //Y軸の移動

    bool isJump_;                           //ジャンプしているか
    bool isPastButton;                      //さっき踏んでいるか

    Stage* pStage_;                         //ステージの情報を入れるポインタ

    enum Direction                         //Playerの向き
    {
        DIR_RIGHT,                          //右向き
        DIR_LEFT,                           //左向き
        DIR_MAX,                            //配列の最大要素数
    };
    int hModel_[DIR_MAX][DIR_MAX];          //Playerのモデル番号を格納する多次元配列

public:    
    Player(GameObject* parent);             //コンストラクタ
    ~Player();                              //デストラクタ    
    void Initialize() override;             //初期化
    void Update() override;                 //更新
    void Draw() override;                   //描画  
    void Release() override;                //開放
    void FootButtonCheck();                 //Playerがボタンを踏んでいるか、ボタンから離れたかを判断する関数
    int GetModelNumber();                   //Playerの走っているモデル番号を返す関数
    int GetDirection();                     //Player向きのモデル番号を返す関数

private:    
    void AllFind();                         //Find処理をすべてまとめる関数
    void PlayerRightMove();                 //Playerの操作をまとめる関数
    void PlayerLeftMove();
    void PlayerCollision();                 //Playyerの当たり判定をまとめる関数
};
