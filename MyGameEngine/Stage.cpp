#include "Stage.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Engine/CsvReader.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")//, hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    hModel_[0] = Model::Load("Assets/BlueBlock.fbx");
    hModel_[1] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[2] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[3] = Model::Load("Assets/PushButton.fbx");
    hModel_[4] = Model::Load("Assets/PushButton2.fbx");


    //Csvファイルの読み込み
    CsvReader csv;
    csv.Load("Assets/Stage1.csv");


    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            map_[x][y] = csv.GetValue(x, 9 - y); //エクセルだとyの値が逆なので-9をしてあげる

            if (map_[x][y] == 99)
            {
                Player* pPlayer = (Player*)Instantiate<Player>(this->pParent_);
                pPlayer->transform_.position_.x = x;
                pPlayer->transform_.position_.y = y;
            }
        }
    }
}

//更新
void Stage::Update()
{

}

//描画
void Stage::Draw()
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (map_[x][y] == 0 || map_[x][y] == 99)
            {
                continue;
            }

            int type = map_[x][y] - 1;
            Transform trans;
            trans.position_.x = x;
            trans.position_.y = y;
            trans.Calclation();



            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
        }
    }
}

//開放
void Stage::Release()
{
}

//そのマスに障害物があるかどうか
//戻り値、何かあるtrue,何もないfalse
bool Stage::isCrash(int x, int y)
{
    //配列に1が入っていれば通れない
    if (map_[x][y] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//ボタンがPlayerの足元にあるかどうかを判断する関数
//ボタンが入っている配列はmap_[x][y] == 4が入っている
//この関数はPlayerクラスで常に呼ばれている
void Stage::Button(int x, int y)
{
    //押す前のボタンを返す
    if(map_[x][y] == 4)
    {
        map_[x][y] = 5;
    }
}

void Stage::Down(int x, int y)
{
    
}
