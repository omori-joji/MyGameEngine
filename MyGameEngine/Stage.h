#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[7];

public:

    int map_[20][10];

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

    //ぶつかるかどうか
    bool isCrash(int x , int y);

    void DownButton(int x, int y);
};

