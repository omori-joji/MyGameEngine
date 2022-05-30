#pragma once
#include "Engine/GameObject.h"
#include "Actor.h"

//クラスの前方宣言
class Stage;

//Player処理を行うクラス
class Player :  public Actor
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
    const char RESET_VALU_;                 //初期化用の定数
    const char PLAYER_FOOT_;                //Playerの足元を見るためにY軸を-1する定数
    const string MODEL_FILE_PAS_;           //モデルが保存されているファイルパス
    const string SE_FILE_PAS_;              //モデルが保存されているファイルパス
    char modelNumber_;                      //走っているモデルの番号
    float yMove_;                           //Y軸の移動
    bool isJump_;                           //ジャンプしているか
    Stage* pStage_;                         //ステージの情報を入れるポインタ

    //Playerのモデル番号
    enum Direction
    {
        STANDING_MODEL,                     //立っているモデル番号
        RUN_MODEL,                          //走っているモデル番号

        DIR_RIGHT = 0,                      //右向きのモデル番号
        DIR_LEFT,                           //左向きのモデル番号
        DIR_MAX                             //hModel_の要素数
    }direction_;                            //プレイヤーの向きの番号
    int hModel_[DIR_MAX][DIR_MAX];          //Playerのモデル番号を格納する多次元配列

    //サウンドファイル番号
    enum Se
    {
        JUMP,                               //ジャンプのSE
        RESET,                              //リセットのSE
        MAX_SE,                             //配列の要素数
    }se_;
    int hSe_[MAX_SE];                       //サウンドファイルを格納する配列

public:    
    Player(GameObject* parent);             //コンストラクタ
    ~Player();                              //デストラクタ    
    void Initialize() override;             //初期化
    void Update() override;                 //更新
    void Draw() override;                   //描画  
    void Release() override;                //開放

    //Playerの走っているモデル番号を返す関数
    //引数：なし
    //戻り値：modelNumber_
    int GetModelNumber();

    //Player向きのモデル番号を返す関数
    //引数：なし
    //戻り値：direction_
    int GetDirection();
private:
    //Find処理をすべてまとめる関数
    //引数：なし
    //戻り値：なし
    void AllFind();

    //Playerの右操作をまとめる関数
    //引数：なし
    //戻り値：なし
    void PlayerRightMove();

    //Playerの左操作をまとめる関数
    //引数：なし
    //戻り値：なし
    void PlayerLeftMove();

    //Playyerの当たり判定をまとめる関数
    //引数：なし
    //戻り値：なし
    void Collision();

    //初期位置に戻る処理をまとめた関数
    //引数：なし
    //戻り値：なし
    void Reset();

    //ジャンプの処理をまとめた関数
    //引数：なし
    //戻り値：なし
    void Jump();
};
