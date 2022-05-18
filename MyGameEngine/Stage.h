#pragma once
#include "Engine/VisualEffect.h"
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
//クラスの前方宣言
class Player;
class Shadow;
class SceneManager;

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    //int hVfxA, hVfxB;
    const int BACK_GROUND_;                         //背景のモデル番号
    const int PLAYER_GENERAT_POS_;                  //Playerのリスポーン地点
    const int SHADOW_NAMBER_;                       //影の数
    const int ALL_GIMMICKS_;                        //ギミックのモデル番号を調べる繰り返し文のための定数
    const int RESET_VALU_;                          //初期化用の値
    const int CHENGE_POSITIVE_GIMMICKS_;            //+10したモデル番号に変えるための定数
    const int BRINKING_BLOCKS_;                     //点滅するブロック
    const int FRAME_TIME_;                          //点滅する間隔
    const int MEANTIME_WALL_;                       //ボタンが踏まれていない間閉じている壁のモデル番号
    const int MEANTIME_BUTTON_UP_;                  //踏んでいる間発動するボタンの踏む前のモデル番号
    const int MEANTIME_BUTTON_DOWN_;                //踏んでいる間発動するボタンの踏んだあとのモデル番号
    const int MEANTIME_BLOCK_ALPHA_;                //ボタンが踏まれている間開いている壁のモデル番号
    const int ON_WARP_BLOCK_;                       //片方のワープブロックのモデル番号
    const int OR_WARP_BLOCK_;                       //もう片方のワープブロックのモデル番号
    const int GOAL_BLOCK_;                          //ゴールブロックのモデル番号
    const int ON_DOUBLE_BUTTON_UP_;                 //同時押しボタンの片方。踏んでいない状態のモデル番号
    const int ON_DOUBLE_BUTTON_DOWN_;               //同時押しボタンの片方。踏んでいる状態のモデル番号
    const int OR_DOUBLE_BUTTON_UP_;                 //同時押しボタンのもう片方。踏んでいない状態のモデル番号
    const int OR_DOUBLE_BUTTON_DOWN_;               //同時押しボタンの片方。踏んでいる状態のモデル番号
    const int DOUBLE_BUTTON_WALL_;                  //同時押しボタンに対応した壁。開いてない状態のモデル番号
    const int DOUBLE_BUTTON_WALL_ALPHA_;            //同時押しボタンに対応した壁。開いている状態のモデル番号
    int shadowCount_;                               //影の数
    int timeCount_;                                 //点滅ブロックの点滅間隔
    bool isBlinking_;                               //ブロックが消えたかどうか
    bool isWarp_;                                   //ワープしたか塚
    XMFLOAT3 stertPos;                              //Playerがリセットした時のリセット位置を記憶する変数
    Player* pPlayer_;                               //Playerクラスを格納するポインタ
    SceneManager* pSceneManager_;                   //SceneManagerクラスを格納するポインタ
    enum Direction
    {
        MAP_BESIDE_ = 28,
        MAP_VERTICAL = 23,
        MAX_MODEL = 200,
        MAX_SOUND = 4,
        MAX_STEPNUMBER = 10,
        MAX_DOUBLE_FLAG = 2,
        MAX_SHADOW_NUMBER = 6,
    };
    int map_[MAP_BESIDE_][MAP_VERTICAL];            //ステージのマス情報
    int hModel_[MAX_MODEL];                         //モデル番号
    int hSound_[MAX_SOUND];                         //サウンドファイル
    int steppingNumberMeanTime[MAX_STEPNUMBER];     //何人踏んでいるか
    int steppingNumber_OnDouble[MAX_STEPNUMBER];    //何人踏んでいるか
    int steppingNumber_OrDouble[MAX_STEPNUMBER];    //何人踏んでいるか
    bool isDoubleButton_[MAX_DOUBLE_FLAG];          //同時ボタンの片方を押した
    Shadow* pShadow_[MAX_SHADOW_NUMBER];            //Shadowクラスを格納するポインタ型の配列

public:
    Stage(GameObject* parent);                      //コンストラクタ
    ~Stage();                                       //デストラクタ
    void Initialize() override;                     //初期化
    void Update() override;                         //更新
    void Draw() override;                           //描画
    void Release() override;                        //開放
    void GoalCol(int x, int y);                     //ゴールを判定する関数。引数はプレイヤーの位置
    void WarpBlockCollision(int getX, int getY);    //ワープブロックのギミックをまとめた関数。引数はプレイヤーの位置
    void ChengeButtonAndWall();                     //壁のモデルとボタンのモデルを切り替える関数。
    void SetMeanTimeStepNumberCountUp(int a);       //ボタンに乗っている人数をカウントアップする関数
    void SetMeanTimeStepNumberCountDown(int a);     //ボタンに乗っている人数をカウントアップする関数
    void SetOnDoubleStepNumberCountUp(int b);       //同時押しボタンの片方のボタンの乗っている人数をカウントアップする関数
    void SetOnDoubleStepNumberCountDown(int b);     //同時押しボタンの片方のボタンの乗っている人数をカウントダウンする関数
    void SetOrDoubleStepNumberCountUp(int c);       //同時押しボタンのもう片方のボタンの乗っている人数をカウントアップする関数
    void SetOrDoubleStepNumberCountDown(int c);     //同時押しボタンのもう片方のボタンの乗っている人数をカウントダウンする関数
    int CheckFootBlock(int x, int y);               //足元のブロックのモデル番号を引数で受け取り、それの1の位を返す関数
    bool isCrash(int x, int y);                     //ぶつかるかどうか
    bool MeanTimeButton(int x, int y);              //すべてのボタンを管理する関数
    bool OnDoubleButton(int x, int y);              //同時押しボタンの片方に乗ったらtrueそれ以外はfalseを返す関数
    bool OrDoubleButton(int x, int y);              //同時押しボタンのもう片方に乗ったらtrueそれ以外はfalseを返す関数
    XMFLOAT3 GetStartPosition();                    //初期スポーン地点を返すゲッター
private:
    void ModelLoad();                               //まとめてモデルをロードする関数
    void CheckBlock(int find , bool which);         //モデルを切り替える関数。引数は(切り替えたいモデル番号, trueが第一引数に+10falseが第一引数に-10されたモデル番号に切り替える)
    void CollisionExit();                           //当たり判定。ボタンから離れたら呼ばれる
    void Blinking(int blockNum, int time);          //点滅ブロックのギミックをまとめた関数。引数は(第一引数が点滅させたいブロックのモデル番号, 第二引数が点滅する時間の間隔(単位はフレーム))
    void SimultaneousWallOpen();                    //同時押しボタンがどちらも押されていたら。壁を開き、それ以外の条件だったら壁を閉じる関数
    void ResetShadow();                             //記録した影の動きをすべてまっさらな状態にする処理をまとめた関数
    void PlayRecord();                              //影の再生をまとめた関数
    void AllFind();                                 //Find処理をまとめた関数
};