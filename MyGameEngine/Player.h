#pragma once
#include "Engine/GameObject.h"
#include "Actor.h"

//クラスの前方宣言
class Stage;

//Player処理を行うクラス
class Player :  public Actor
{
    //定数宣言
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
    const string MODEL_FILE_PAS_;                 //モデルが保存されているファイルパス
    const string SE_FILE_PAS_;                 //モデルが保存されているファイルパス

    //変数宣言
    char modelNumber_;                      //走っているモデルの番号
    float yMove_;                           //Y軸の移動
    bool isJump_;                           //ジャンプしているか
    Stage* pStage_;                         //ステージの情報を入れるポインタ
    //列挙体
    enum
    {
        STANDING_MODEL = 0,                 //立っているモデル番号
        RUN_MODEL,                          //走っているモデル番号

        ON_DOUBLE_BUTTON = 0,               //片方の同時押しボタンのフラグ番号
        OR_DOUBLE_BUTTON,                   //もう片方の同時押しボタンのフラグ番号
        MAX_DOUBLE_BUTTON,                  //isPastDoubleButton_の最大要素数
    };
    enum Direction
    {
        DIR_RIGHT,
        DIR_LEFT,
        DIR_MAX
    }direction_;                            //プレイヤーの向きの番号
    int hModel_[DIR_MAX][DIR_MAX];          //Playerのモデル番号を格納する多次元配列
    enum Se
    {
        JUMP,                               //ジャンプのSE
        RESET,                              //リセットのSE
        MAX_SE,                             //配列の要素数
    }se_;
    int hSe_[MAX_SE];
public:    
    Player(GameObject* parent);             //コンストラクタ
    ~Player();                              //デストラクタ    
    void Initialize() override;             //初期化
    void Update() override;                 //更新
    void Draw() override;                   //描画  
    void Release() override;                //開放
    int GetModelNumber();                   //Playerの走っているモデル番号を返す関数
    int GetDirection();                     //Player向きのモデル番号を返す関数
private:
    void AllFind();                         //Find処理をすべてまとめる関数
    void PlayerRightMove();                 //Playerの右操作をまとめる関数
    void PlayerLeftMove();                  //Playerの左操作をまとめる関数
    void Collision();                       //Playyerの当たり判定をまとめる関数
    void Reset();                           //初期位置に戻る処理をまとめた関数
    void Jump();                            //ジャンプの処理をまとめた関数
};
