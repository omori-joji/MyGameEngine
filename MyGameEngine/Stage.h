#pragma once
#include "Engine/VisualEffect.h"
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

//Stageを管理するクラス
class Stage : public GameObject
{
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
    const int NO1_WARP_BLOCK_;                      //片方のワープブロックのモデル番号
    const int NO2_WARP_BLOCK_;                      //もう片方のワープブロックのモデル番号
    const int GOAL_BLOCK_;                          //ゴールブロックのモデル番号
    const int NO1_DOUBLE_BUTTON_UP_;                //同時押しボタンの片方。踏んでいない状態のモデル番号
    const int NO1_DOUBLE_BUTTON_DOWN_;              //同時押しボタンの片方。踏んでいる状態のモデル番号
    const int NO2_DOUBLE_BUTTON_UP_;                //同時押しボタンのもう片方。踏んでいない状態のモデル番号
    const int NO2_DOUBLE_BUTTON_DOWN_;              //同時押しボタンの片方。踏んでいる状態のモデル番号
    const int DOUBLE_BUTTON_WALL_;                  //同時押しボタンに対応した壁。開いてない状態のモデル番号
    const int DOUBLE_BUTTON_WALL_ALPHA_;            //同時押しボタンに対応した壁。開いている状態のモデル番号
    char shadowCount_;                              //今いる影の数
    const string FILE_PAS_;                         //Assetsファイルのパス
    int timeCount_;                                 //点滅ブロックの点滅間隔
    bool isBlinking_;                               //ブロックが消えたかどうか
    bool isWarp_;                                   //ワープしたか塚
    XMFLOAT3 stertPos_;                             //Playerがリセットした時のリセット位置を記憶する変数
    Player* pPlayer_;                               //Playerクラスを格納するポインタ
    SceneManager* pSceneManager_;                   //SceneManagerクラスを格納するポインタ
    enum
    {
        MAP_BESIDE_ = 28,                           //マップのX軸
        MAP_VERTICAL = 23,                          //マップのY軸
        MAX_MODEL = 200,                            //hModel_の要素数
        MAX_SOUND = 4,                              //hSound_の要素数
        MAX_STEPNUMBER = 10,                        //各ボタンが踏んでいる人数を記憶する配列の要素数
        MAX_DOUBLE_FLAG = 2,                        //同時ボタンの踏んでいるフラグの要素数
        MAX_SHADOW_NUMBER = 5,                      //影の最大生成数
    };
    int map_[MAP_BESIDE_][MAP_VERTICAL];            //ステージのマス情報
    int hModel_[MAX_MODEL];                         //モデル番号
    int hSound_[MAX_SOUND];                         //サウンドファイル
    char steppingNumberMeanTime_[MAX_STEPNUMBER];    //何人踏んでいるか
    char steppingNumber_No1Double_[MAX_STEPNUMBER];  //何人踏んでいるか
    char steppingNumber_No2Double_[MAX_STEPNUMBER];  //何人踏んでいるか
    bool isDoubleButton_[MAX_DOUBLE_FLAG];          //同時ボタンの片方を押した
    Shadow* pShadow_[MAX_SHADOW_NUMBER];            //Shadowクラスを格納するポインタ型の配列

public:
    Stage(GameObject* parent);                      //コンストラクタ
    ~Stage();                                       //デストラクタ
    void Initialize() override;                     //初期化
    void Update() override;                         //更新
    void Draw() override;                           //描画
    void Release() override;                        //開放

    //ゴールを判定し、シーンを切り替える関数
    //引数：PlayerのPosition.x_とPosition.y_
    //戻り値：なし
    void GoalCol(int x, int y);                     
    
    //ワープブロックのギミックをまとめた関数。
    //引数：getX, getY プレイヤーの位置
    //戻値：なし
    void WarpBlockCollision(int getX, int getY);    


    //壁のモデルとボタンのモデルを切り替える関数。
    //引数：なし
    //戻り値：なし
    void ChengeButtonAndWall();

    //ボタンに乗っている人数をカウントアップする関数
    //引数：踏んでいる間発動するボタンのモデル番号の1の位
    //戻り値：なし
    void SetMeanTimeStepNumberCountUp(int a);

    //ボタンに乗っている人数をカウントダウンする関数
    //引数：踏んでいる間発動するボタンのモデル番号の1の位
    //戻り値：なし
    void SetMeanTimeStepNumberCountDown(int a);

    //同時押しボタンの片方のボタンの乗っている人数をカウントアップする関数
    //引数：同時押しボタンのモデル番号の1の位
    //戻り値：なし
    void SetNo1DoubleStepNumberCountUp(int b);

    //同時押しボタンの片方のボタンの乗っている人数をカウントダウンする関数
    //引数：同時押しボタンのモデル番号の1の位
    //戻り値：なし
    void SetNo1DoubleStepNumberCountDown(int b);

    //同時押しボタンのもう片方のボタンの乗っている人数をカウントアップする関数
    //引数：同時押しボタンのモデル番号の1の位
    //戻り値：なし
    void SetNo2DoubleStepNumberCountUp(int c);

    //同時押しボタンのもう片方のボタンの乗っている人数をカウントダウンする関数
    //引数：同時押しボタンのモデル番号の1の位
    //戻り値：なし
    void SetNo2DoubleStepNumberCountDown(int c);

    //足元のブロックのモデル番号を引数で受け取り、それの1の位を返す関数
    //引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
    //戻り値：ボタンのモデル番号の1の位
    int CheckFootBlock(int x, int y);

    //ぶつかったかどうか
    //引数：PlayerのPosition.x_とPosition.y_
    //戻り値：ぶつかったらfalse、何もなければtrue
    bool isCrash(int x, int y);

    //踏んでいる間発動するボタンがあるかどうかの処理を実行する
    //引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
    //戻り値：踏んでいればtrue踏んでいなければfalse
    bool MeanTimeButton(int x, int y);

    //同時押しボタンの片方に乗ったらtrueそれ以外はfalseを返す関数
    //引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
    //戻り値：踏んでいればtrue踏んでいなければfalse
    bool No1DoubleButton(int x, int y);

    //同時押しボタンのもう片方に乗ったらtrueそれ以外はfalseを返す関数
    //引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
    //戻り値：踏んでいればtrue踏んでいなければfalse
    bool No2DoubleButton(int x, int y);


    //初期スポーン地点を返すゲッター
    //引数：なし
    //戻り値：stertPos_
    XMFLOAT3 GetStartPosition();
private:
    //モデルをロードする処理をまとめた関数
    //引数：なし
    //戻り値：なし
    void ModelLoad();

    //モデルを切り替える関数。
    //引数：変更したいモデル番号, trueで+10されたモデルに、falseで-10されたモデルに変更
    //戻り値：なし
    void CheckBlock(int find , bool which);

    //ボタンから離れたら呼ばれる関数、モデルを切り替える処理を行う
    //引数：なし
    //戻り値：なし
    void CollisionExit();


    //点滅ブロックのギミックをまとめた関数。
    //引数：点滅したいブロックのモデル番号, 点滅間隔。単位はフレーム
    //戻り値：なし
    void Blinking(int blockNum, int time);

    //同時押しボタンがどちらも押されていたら。壁を開き、それ以外の条件だったら壁を閉じる関数
    //引数：なし
    //戻り値：なし
    void SimultaneousWallOpen();

    //影の再生するフラグと生成の処理を行う関数
    //引数：なし
    //戻り値：なし
    void PlayRecord();
};