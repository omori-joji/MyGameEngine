#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Engine/SceneManager.h"
#include "Stage.h"
#include "Player.h"
#include "Shadow.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hSound_(-1),
    isOpenWall_(true),
    pPlayer_(nullptr),
    shadowCount_(0),
    timeCount_(0),
    isBlinking_(true),
    verticalValu(0),     //マップ縦軸の値
    besideValu(0),       //マップ横軸の値
    pSceneManager_(nullptr)
{

}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //ブロックなどのモデルをロードする処理をまとめた関数
    ModelLoad();

    if (pSceneManager_ == nullptr)
    {
        pSceneManager_ = (SceneManager*)Find("SceneManager");
    }


    //Csvファイルの読み込み
    CsvReader csv;

    switch(pSceneManager_->nextSceneID_)
    {
    case SCENE_ID_STAGE1: csv.Load("Assets/Stage1.csv");break;
    case SCENE_ID_STAGE2: csv.Load("Assets/Stage2.csv");break;
    case SCENE_ID_STAGE3: csv.Load("Assets/Stage3.csv");break;

    }


    //Excelで設定したマスの値
    //縦
    verticalValu = 23;

    //横
    besideValu = 28;



    //プレイヤーの生成
    //200が入っているマスにプレイヤーが出現する
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
        {
            map_[x][y] = csv.GetValue(x, (verticalValu-1) - y); //エクセルだとyの値が逆なので縦軸-1をしてあげる

            if (map_[x][y] == 200)
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
    //Player情報の格納
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }


    //再生スタート
    if (Input::IsKeyDown(DIK_1))
    {
        //点滅ブロックの情報をリセット
        timeCount_ = 0;
        isBlinking_ = true;


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
        //今ある影分
        for (int i = 0; i <= shadowCount_; i++)
        {
            //解放処理
            pShadow[i]->killMe();
        }
        //影の数をリセット
        shadowCount_ = 0;
    }
    //一定時間ごとにブロックを入れ替える
    Blinking(81, 70);
}





//描画
void Stage::Draw()
{
    //ブロックの配置
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
        {
            //プレイヤーの位置とブロックを置かない位置の場合
            if (map_[x][y] == 0 || map_[x][y] == 200)
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

    //背景の生成
    //ど真ん中に出す
    Transform back;

    //横軸の真ん中
    back.position_.x = besideValu / 2;
    //縦軸の真ん中
    back.position_.y = verticalValu / 2 + 1;
    //少し奥に
    back.position_.z = 0.5;
    //位置の確定
    back.Calclation();

    Model::SetTransform(hModel_[3], back);
    Model::Draw(hModel_[3]);
}





//開放
void Stage::Release()
{
}







//そのマスに障害物があるかどうか
//戻り値、何かあるtrue,何もないfalse
bool Stage::isCrash(int x, int y)
{
    for (int i = 0; i < 9; i++)
    {
        //そこにはブロックはない
        if (map_[x][y] == 0 ||
            map_[x][y] == 3 ||
            map_[x][y] == 200 ||
            map_[x][y] == 91 ||
            map_[x][y] == 101 ||
            map_[x][y] == 61 ||
            map_[x][y] == 81)
        {
            return false;
        }
        //そこにはブロックがあるから通れない
        else
        {
            return true;
        }
    }

}





//ボタンがPlayerの足元にあるかどうかを判断する関数
//ボタンが入っている配列はmap_[x][y] == 4が入っている
//この関数はPlayerクラスで常に呼ばれている
void Stage::DownButton(int x, int y)
{
    for (int i = 0; i < 9; i++)
    {
        if (map_[x][y] == 31 + i)
        {

            //モデル変更
            CheckBlock(map_[x][y], true);


            //壁を開く処理
            CheckBlock(51 + i, true);
        }
    }
    
    

    //Playerが離れたら
    //もしくはリセットしたら
    if (map_[x][y] == 0||Input::IsKeyDown(DIK_1))
    {
        //押している間だけのボタンのモデルをリセットする
        for (int i = 0; i <= shadowCount_; i++)
        {
            if (pShadow[i]->isRecording_ == false)
            {
                for (int i = 0; i < 9; i++)
                {
                    //ボタンのモデルを切り替える
                    CheckBlock(41 + i, false);

                    //壁のモデルを切り替える
                    CheckBlock(60 + i, false);
                }
            }
        }
        for (int i = 0; i < 9; i++)
        {
            //ボタンのモデルを切り替える
            CheckBlock(41 + i, false);

            //壁のモデルを切り替える
            CheckBlock(60 + i, false);
        }
    }
}


//特定のブロックを探して、モデルを切り替える関数
//第一引数は切り替えたいブロックの番号
//第二引数はプラスかマイナスか
void Stage::CheckBlock(int find , bool which)
{
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
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

//点滅ブロック
//第一引数は点滅させたいブロックの番号
//第二引数は秒数。単位はフレーム
//変えたいモデル番号+10には透明のブロック設定しておく
void Stage::Blinking(int blockNum, int time)
{
    //計測
    timeCount_++;

    //透明にする
    if (timeCount_ >= time && isBlinking_ == true)
    {
        //モデルを切り替える関数
        CheckBlock(blockNum , false);

        isBlinking_ = false;

        //計測時間をリセット
        timeCount_ = 0;
    }
    //不透明にする
    else if(timeCount_ >= time && isBlinking_ == false)
    {
        CheckBlock(blockNum - 10, true);

        isBlinking_ = true;

        //計測時間をリセット
        timeCount_ = 0;
    }
}

//特定のブロックの位置にワープする関数
//引数は今プレイヤーのいる位置にあるマス
bool Stage::WarpBlockEnter(int x, int y)
{
    //そこはワープブロック
    if (map_[x][y] == 91)
    {
        return true;
    }
    //何もない
    else
    {
        return false;
    }
}

//ゴールの処理をする関数
//引数は今プレイヤーのいる位置にあるマス
void Stage::GoalCol(int x, int y)
{
    //そこはゴール
    if (map_[x][y] == 3)
    {
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }

}

//
void Stage::WarpBlockExit()
{
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
        {
            if (map_[x][y] == 101)
            {
                pPlayer_->transform_.position_.x = x;
                pPlayer_->transform_.position_.y = y;
            }
        }
    }
}



void Stage::ModelLoad()
{

    //ステージを構成するブロック
    hModel_[0] = Model::Load("Assets/Block.fbx");
    hModel_[1] = Model::Load("Assets/NaturalBlock.fbx");
    hModel_[2] = Model::Load("Assets/Goal.fbx");
    hModel_[3] = Model::Load("Assets/BackGround.fbx");
    hModel_[4] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[5] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[6] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[7] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[8] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[9] = Model::Load("Assets/GreenBlock.fbx");


    //押したら発動するbボタン
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


    //押したら開き続ける壁
    hModel_[20] = Model::Load("Assets/Wall.fbx");
    hModel_[21] = Model::Load("Assets/Wall.fbx");
    hModel_[22] = Model::Load("Assets/Wall.fbx");
    hModel_[23] = Model::Load("Assets/Wall.fbx");
    hModel_[24] = Model::Load("Assets/Wall.fbx");
    hModel_[25] = Model::Load("Assets/Wall.fbx");
    hModel_[26] = Model::Load("Assets/Wall.fbx");
    hModel_[27] = Model::Load("Assets/Wall.fbx");
    hModel_[28] = Model::Load("Assets/Wall.fbx");
    hModel_[29] = Model::Load("Assets/Wall.fbx");


    //押している間だけ発動するボタン(押す前)
    hModel_[30] = Model::Load("Assets/UpButton.fbx");
    hModel_[31] = Model::Load("Assets/UpButton.fbx");
    hModel_[32] = Model::Load("Assets/UpButton.fbx");
    hModel_[33] = Model::Load("Assets/UpButton.fbx");
    hModel_[34] = Model::Load("Assets/UpButton.fbx");
    hModel_[35] = Model::Load("Assets/UpButton.fbx");
    hModel_[36] = Model::Load("Assets/UpButton.fbx");
    hModel_[37] = Model::Load("Assets/UpButton.fbx");
    hModel_[38] = Model::Load("Assets/UpButton.fbx");
    hModel_[39] = Model::Load("Assets/UpButton.fbx");


    //押している間だけ発動するボタン(押した後)
    hModel_[40] = Model::Load("Assets/UpButton2.fbx");
    hModel_[41] = Model::Load("Assets/UpButton2.fbx");
    hModel_[42] = Model::Load("Assets/UpButton2.fbx");
    hModel_[43] = Model::Load("Assets/UpButton2.fbx");
    hModel_[44] = Model::Load("Assets/UpButton2.fbx");
    hModel_[45] = Model::Load("Assets/UpButton2.fbx");
    hModel_[46] = Model::Load("Assets/UpButton2.fbx");
    hModel_[47] = Model::Load("Assets/UpButton2.fbx");
    hModel_[48] = Model::Load("Assets/UpButton2.fbx");
    hModel_[49] = Model::Load("Assets/UpButton2.fbx");


    //開く壁
    hModel_[50] = Model::Load("Assets/Wall.fbx");
    hModel_[51] = Model::Load("Assets/Wall.fbx");
    hModel_[52] = Model::Load("Assets/Wall.fbx");
    hModel_[53] = Model::Load("Assets/Wall.fbx");
    hModel_[54] = Model::Load("Assets/Wall.fbx");
    hModel_[55] = Model::Load("Assets/Wall.fbx");
    hModel_[56] = Model::Load("Assets/Wall.fbx");
    hModel_[57] = Model::Load("Assets/Wall.fbx");
    hModel_[58] = Model::Load("Assets/Wall.fbx");
    hModel_[59] = Model::Load("Assets/Wall.fbx");


    //開いている間の何もないブロック
    hModel_[60] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[61] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[62] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[63] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[64] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[65] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[66] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[67] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[68] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[69] = Model::Load("Assets/AlphaBlock.fbx");


    //点滅するブロック(消える前)
    hModel_[70] = Model::Load("Assets/Wall.fbx");
    hModel_[71] = Model::Load("Assets/Wall.fbx");
    hModel_[72] = Model::Load("Assets/Wall.fbx");
    hModel_[73] = Model::Load("Assets/Wall.fbx");
    hModel_[74] = Model::Load("Assets/Wall.fbx");
    hModel_[75] = Model::Load("Assets/Wall.fbx");
    hModel_[76] = Model::Load("Assets/Wall.fbx");
    hModel_[77] = Model::Load("Assets/Wall.fbx");
    hModel_[78] = Model::Load("Assets/Wall.fbx");
    hModel_[79] = Model::Load("Assets/Wall.fbx");


    //点滅するブロック(消えた後)
    hModel_[80] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[81] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[82] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[83] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[84] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[85] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[86] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[87] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[88] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[89] = Model::Load("Assets/AlphaBlock.fbx");


    //ワープブロック(入口)
    hModel_[90] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[91] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[92] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[93] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[94] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[95] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[96] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[97] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[98] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[99] = Model::Load("Assets/WarpEntrance.fbx");


    //ワープブロック(出口)
    hModel_[100] = Model::Load("Assets/WarpExit.fbx");
    hModel_[101] = Model::Load("Assets/WarpExit.fbx");
    hModel_[102] = Model::Load("Assets/WarpExit.fbx");
    hModel_[103] = Model::Load("Assets/WarpExit.fbx");
    hModel_[104] = Model::Load("Assets/WarpExit.fbx");
    hModel_[105] = Model::Load("Assets/WarpExit.fbx");
    hModel_[106] = Model::Load("Assets/WarpExit.fbx");
    hModel_[107] = Model::Load("Assets/WarpExit.fbx");
    hModel_[108] = Model::Load("Assets/WarpExit.fbx");
    hModel_[109] = Model::Load("Assets/WarpExit.fbx");



    //同時押しボタン(押す前)
    hModel_[110] = Model::Load("Assets/&Button.fbx");
    hModel_[111] = Model::Load("Assets/&Button.fbx");
    hModel_[112] = Model::Load("Assets/&Button.fbx");
    hModel_[113] = Model::Load("Assets/&Button.fbx");
    hModel_[114] = Model::Load("Assets/&Button.fbx");
    hModel_[115] = Model::Load("Assets/&Button.fbx");
    hModel_[116] = Model::Load("Assets/&Button.fbx");
    hModel_[117] = Model::Load("Assets/&Button.fbx");
    hModel_[118] = Model::Load("Assets/&Button.fbx");
    hModel_[119] = Model::Load("Assets/&Button.fbx");


    //同時押しボタン(押した後)
    hModel_[120] = Model::Load("Assets/OrButton.fbx");
    hModel_[121] = Model::Load("Assets/OrButton.fbx");
    hModel_[122] = Model::Load("Assets/OrButton.fbx");
    hModel_[123] = Model::Load("Assets/OrButton.fbx");
    hModel_[124] = Model::Load("Assets/OrButton.fbx");
    hModel_[125] = Model::Load("Assets/OrButton.fbx");
    hModel_[126] = Model::Load("Assets/OrButton.fbx");
    hModel_[127] = Model::Load("Assets/OrButton.fbx");
    hModel_[128] = Model::Load("Assets/OrButton.fbx");
    hModel_[129] = Model::Load("Assets/OrButton.fbx");


    //開く壁(開く前)
    hModel_[130] = Model::Load("Assets/Wall.fbx");
    hModel_[131] = Model::Load("Assets/Wall.fbx");
    hModel_[132] = Model::Load("Assets/Wall.fbx");
    hModel_[133] = Model::Load("Assets/Wall.fbx");
    hModel_[134] = Model::Load("Assets/Wall.fbx");
    hModel_[135] = Model::Load("Assets/Wall.fbx");
    hModel_[136] = Model::Load("Assets/Wall.fbx");
    hModel_[137] = Model::Load("Assets/Wall.fbx");
    hModel_[138] = Model::Load("Assets/Wall.fbx");
    hModel_[139] = Model::Load("Assets/Wall.fbx");



    //開く壁(開いた後)
    hModel_[140] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[141] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[142] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[143] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[144] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[145] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[146] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[147] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[148] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[149] = Model::Load("Assets/AlphaBlock.fbx");
}

