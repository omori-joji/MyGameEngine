#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Shadow.h"


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
    bool isRecording_; //Playerの動きを記録しているか
    float move_; //Y軸の移動
    float gravity_; //重力



    int hModel_[2];
    Stage* pStage_;

public:
    XMFLOAT3 stertPos_; //影を再生したときに初期位置に戻るための変数
    DWORD frameCounter_; //フレーム数
    std::vector<XMFLOAT3>   recordData_;//プレイヤーの位置を記録する可変長配列


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
