#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Stage.h"
#include "Player.h"
#include "Shadow.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    isOpenWall_(true),
    pPlayer_(nullptr),
    shadowCount_(0),
    timeCount_(0),
    isBlinking_(true)
{

}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    ModelLoad();


    //Csvファイルの読み込み
    CsvReader csv;
    csv.Load("Assets/Stage1.csv");


    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            map_[x][y] = csv.GetValue(x, 11 - y); //エクセルだとyの値が逆なので-9をしてあげる

            if (map_[x][y] == 99)
            {
                //プレイヤーの生成
                //プレイヤーの位置決定
                //プレイヤーの初期位置を記憶する
                Player* pPlayer = (Player*)Instantiate<Player>(this->pParent_);
                pPlayer->transform_.position_.x = x;
                pPlayer->transform_.position_.y = y;
                stertPos = pPlayer->transform_.position_;
            }
        }
    }


    //影の生成
    pShadow[shadowCount_] = (Shadow*)Instantiate<Shadow>(this->pParent_);
}



//更新
void Stage::Update()
{
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }
    

    Blinking(71, 60);


    //再生スタート
    if (Input::IsKeyDown(DIK_1))
    {
        //すでに生成している影を表示し、もう一度再生する
        if (shadowCount_ <= 5)
        {
            //すでに生成している影をもう一度1から再生する
            for (int i = 0; i <= shadowCount_; i++)
            {
                //表示するフラグ
                pShadow[i]->Flag();
            }

            if (shadowCount_ <= 4)
            {
                //二体目以降の影の番号
                shadowCount_++;
            }
        }


        //影の生成
        if (shadowCount_ <= 5)
        {
            pShadow[shadowCount_] = (Shadow*)Instantiate<Shadow>(this);
        }
    }

    //保存された影の動きをすべてリセットする
    if (Input::IsKeyDown(DIK_2))
    {
        for (int i = 0; i <= shadowCount_; i++)
        {
            pShadow[i]->killMe();
        }

        shadowCount_ = 0;
    }
}





//描画
void Stage::Draw()
{
    //ブロックの配置
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            //プレイヤーの位置とブロックを置かない位置の場合
            if (map_[x][y] == 0 || map_[x][y] == 99)
            {
                continue;
            }

            //モデル番号の格納
            int type = map_[x][y] - 1;

            //位置
            Transform trans;
            trans.position_.x = x;
            trans.position_.y = y;

            //Calclationクラスで位置を変更する
            trans.Calclation();


            //モデルのロード
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
    //そこにはブロックはない
    if (map_[x][y] == 0 || map_[x][y] == 99)
    {
        return false;
    }
    //そこにはブロックがあるから通れない
    else
    {
        return true;
    }
}





//ボタンがPlayerの足元にあるかどうかを判断する関数
//ボタンが入っている配列はmap_[x][y] == 4が入っている
//この関数はPlayerクラスで常に呼ばれている
void Stage::DownButton(int x, int y)
{
    //押した後のモデルに差し替える
    if(map_[x][y] == 21)
    {
        map_[x][y] = map_[x][y] + 10;

        isOpenWall_ = false;//壁を開くよ

        OpenWall();//壁を開く処理
    }


    //Playerが離れたら
    if (map_[x][y] == 0 || Input::IsKeyDown(DIK_1))
    {
        //ボタンのモデルを切り替える
        CheckBrock(31 , false);

        //壁のモデルを切り替える
        CheckBrock(51 , false);
    }
}



//壁を開く関数
void Stage::OpenWall()
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            if (map_[x][y] == 41 && isOpenWall_ == false)
            {
                //壁が配置されていたら0を入れてあげる
                map_[x][y] = map_[x][y] + 10;
            }
        }
    }

    //壁が全部開いた
    isOpenWall_ = true;
}


//特定のブロックを探して、モデルを切り替える関数
//第一引数は切り替えたいブロックの番号
//第二引数はプラスかマイナスか
void Stage::CheckBrock(int find , bool which)
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            if (map_[x][y] == find && which == false)
            {
                map_[x][y] = map_[x][y] - 10;
            }
            else if(map_[x][y] == find && which == true)
            {
                map_[x][y] = find + 10;
            }
        }
    }
}

void Stage::Blinking(int blockNum, int time)
{
    timeCount_++;

    if (timeCount_ >= time && isBlinking_ == true)
    {
        //モデルを切り替える関数
        CheckBrock(blockNum , false);

        isBlinking_ = false;

        //計測時間をリセット
        timeCount_ = 0;
    }
    else if(timeCount_ >= time && isBlinking_ == false)
    {
        CheckBrock(blockNum - 10, true);

        isBlinking_ = true;

        //計測時間をリセット
        timeCount_ = 0;
    }
}



void Stage::ModelLoad()
{
    //ステージを構成するブロック
    hModel_[0] = Model::Load("Assets/BlueBlock.fbx");
    hModel_[1] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[2] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[3] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[4] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[5] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[6] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[7] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[8] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[9] = Model::Load("Assets/GreenBlock.fbx");


    //押したら発動するブロック
    hModel_[10] = Model::Load("Assets/PushButton.fbx");
    hModel_[11] = Model::Load("Assets/PushButton.fbx");
    hModel_[12] = Model::Load("Assets/PushButton.fbx");
    hModel_[13] = Model::Load("Assets/PushButton.fbx");
    hModel_[14] = Model::Load("Assets/PushButton.fbx");
    hModel_[15] = Model::Load("Assets/PushButton.fbx");
    hModel_[16] = Model::Load("Assets/PushButton.fbx");
    hModel_[17] = Model::Load("Assets/PushButton.fbx");
    hModel_[18] = Model::Load("Assets/PushButton.fbx");
    hModel_[19] = Model::Load("Assets/PushButton.fbx");


    //押している間だけ発動するブロック(押す前)
    hModel_[20] = Model::Load("Assets/UpButton.fbx");
    hModel_[21] = Model::Load("Assets/UpButton.fbx");
    hModel_[22] = Model::Load("Assets/UpButton.fbx");
    hModel_[23] = Model::Load("Assets/UpButton.fbx");
    hModel_[24] = Model::Load("Assets/UpButton.fbx");
    hModel_[25] = Model::Load("Assets/UpButton.fbx");
    hModel_[26] = Model::Load("Assets/UpButton.fbx");
    hModel_[27] = Model::Load("Assets/UpButton.fbx");
    hModel_[28] = Model::Load("Assets/UpButton.fbx");
    hModel_[29] = Model::Load("Assets/UpButton.fbx");


    //押している間だけ発動するブロック(押した後)
    hModel_[30] = Model::Load("Assets/UpButton2.fbx");
    hModel_[31] = Model::Load("Assets/UpButton2.fbx");
    hModel_[32] = Model::Load("Assets/UpButton2.fbx");
    hModel_[33] = Model::Load("Assets/UpButton2.fbx");
    hModel_[34] = Model::Load("Assets/UpButton2.fbx");
    hModel_[35] = Model::Load("Assets/UpButton2.fbx");
    hModel_[36] = Model::Load("Assets/UpButton2.fbx");
    hModel_[37] = Model::Load("Assets/UpButton2.fbx");
    hModel_[38] = Model::Load("Assets/UpButton2.fbx");
    hModel_[39] = Model::Load("Assets/UpButton2.fbx");


    //開く壁
    hModel_[40] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[41] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[42] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[43] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[44] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[45] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[46] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[47] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[48] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[49] = Model::Load("Assets/GreenBlock.fbx");


    //開いている間の何もないブロック
    hModel_[50] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[51] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[52] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[53] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[54] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[55] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[56] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[57] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[58] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[59] = Model::Load("Assets/YellowBlock.fbx");


    //消えるブロック(消える前)
    hModel_[60] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[61] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[62] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[63] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[64] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[65] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[66] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[67] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[68] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[69] = Model::Load("Assets/YellowBlock.fbx");


    //消えるブロック(消えた後)
    hModel_[70] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[71] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[72] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[73] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[74] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[75] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[76] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[77] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[78] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[79] = Model::Load("Assets/GreenBlock.fbx");
}

