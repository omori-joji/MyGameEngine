#pragma once
#include "Engine/Fbx.h"
#include "Engine/GameObject.h"

//クラスの前方宣言
class Player;
class Shadow;
class SceneManager;


//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hVfxA, hVfxB;



    int map_[28][23];   //ステージのマス情報
    int hModel_[500];   //モデル番号
    int shadowCount_;   //影の数
    int timeCount_;     //点滅ブロックの点滅間隔
    int hSound_;        //サウンドファイル
    int downNum_;

    const int VERTICAL_VALU_; //ステージの高さ
    const int BESIDE_VALU_;   //ステージの横幅
    const int BACK_GROUND_;
    const int PLAYER_GENERAT_POS_;  //Playerのリスポーン地点
    const int SHADOW_NAMBER_; //影の数
    const int ALL_GIMMICKS_; //ギミックのモデル番号を調べる繰り返し文のための定数
    const int RESET_VALU_; //初期化用の値
    const int CHENGE_POSITIVE_GIMMICKS_; //+10したモデル番号に変えるための定数
    const int BRINKING_BLOCKS_;
    const int FRAME_TIME_;
    const int DOBLE_BLOCKS_;
    const int TWO_BLOCKS_;
    const int MEANTIME_WALL_;
    const int MEANTIME_BUTTON_UP_;
    const int MEANTIME_BUTTON_DOWN_;
    const int MEANTIME_BLOCK_ALPHA_;
    const int WARP_BLOCK_ENTRANS_;
    const int WARP_BLOCK_EXIT_;
    const int GOAL_BLOCK_;



    bool isBlinking_;      //ブロックが消えたかどうか
    bool isWarp_;          //ワープしたか塚
    bool isDoubleButton_[2]; //同時ボタンの片方を押した
    bool isButtonMenberFlg[9];



    Player* pPlayer_;             //Playerクラスを格納するポインタ
    SceneManager* pSceneManager_; //SceneManagerクラスを格納するポインタ
    Shadow* pShadow_[6];          //Shadowクラスを格納するポインタ型の配列


    XMFLOAT3 stertPos; //Playerがリセットした時のリセット位置を記憶する変数

public:
    int steppingNumber[10];//何人踏んでいるか
    int steppingNumber1[10];//何人踏んでいるか
    int steppingNumber2[10];//何人踏んでいるか
    bool isOnButton;
    bool buttonNumber[10];


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

    //まとめてモデルをロードする関数
    void ModelLoad();

    //ぶつかるかどうか
    bool isCrash(int x , int y);

    //すべてのボタンを管理する関数
    bool MeanTimeButton(int x, int y);

    bool DoubleButton(int x, int y);
    bool OrDoubleButton(int x, int y);

    void CollisionExit();


    //モデルを切り替える関数
    //第一引数は切り替えたいモデル番号
    //第二引数はtrueが第一引数に+10されたモデル番号に切り替える
    //falseが第一引数に-10されたモデル番号に切り替える
    void CheckBlock(int find , bool which);


    //点滅ブロックのギミックをまとめた関数
    //第一引数が点滅させたいブロックのモデル番号
    //第二引数が点滅する時間の間隔(単位はフレーム)
    void Blinking(int blockNum, int time);

    //ゴールを判定する関数
    //引数はプレイヤーの位置
    void GoalCol(int x, int y);

    //ワープブロックの出口のギミックをまとめた関数
    //引数はプレイヤーの位置
    void WarpBlockCollision(int getX, int getY);

    //初期スポーン地点を返すゲッター
    XMFLOAT3 GetStartPosition();

    //壁のモデルとボタンのモデルを切り替える関数
    void ChengeButtonAndWall(int x, int y);

    //ボタンに乗っている人数をカウントアップする関数
    void SetMeanTimeStepNumberCountUp(int a);

    //ボタンに乗っている人数をカウントアップする関数
    void SetMeanTimeStepNumberCountDown(int a);

    //同時押しボタンの片方のボタンの乗っている人数をカウントする関数
    void SetOnDoubleStepNumberCountUp(int b);
    void SetOnDoubleStepNumberCountDown(int b);

    void SetOrDoubleStepNumberCountUp(int c);
    void SetOrDoubleStepNumberCountDown(int c);

    void SimultaneousWallOpen();
    int CheckFootBlock(int x, int y);
};