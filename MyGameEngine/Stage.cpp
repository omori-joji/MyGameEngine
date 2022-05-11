#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Engine/SceneManager.h"
#include "Stage.h"
#include "Player.h"
#include "Shadow.h"
#include "Engine/Audio.h"

#include "Engine/VisualEffect.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hSound_(-1),
    PLAYER_GENERAT_POS_(200),
    VERTICAL_VALU_(23),     //マップ縦軸の値
    BESIDE_VALU_(28),       //マップ横軸の値
    SHADOW_NAMBER_(5),
    ALL_GIMMICKS_(9),
    RESET_VALU_(0),
    CHENGE_POSITIVE_GIMMICKS_(10),
    BRINKING_BLOCKS_(81),
    FRAME_TIME_(60),
    DOBLE_BLOCKS_(151),
    BACK_GROUND_(3),
    TWO_BLOCKS_(161),
    MEANTIME_WALL_(51),
    MEANTIME_BUTTON_UP_(31),
    MEANTIME_BUTTON_DOWN_(41),
    MEANTIME_BLOCK_ALPHA_(61),
    WARP_BLOCK_ENTRANS_(91),
    WARP_BLOCK_EXIT_(101),
    GOAL_BLOCK_(3),


    shadowCount_(0),
    timeCount_(0),


    pPlayer_(nullptr),
    pSceneManager_(nullptr),


    isBlinking_(true),
    isWarp_(true),
    isdoubleButton1_(false),
    isdoubleButton2_(false),

    steppingNumber(0),
    isOnButton(false)
{

}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //サウンドデータのロード
    hSound_ = Audio::Load("Assets/get1.wav");
    assert(hSound_ >= 0);

    //エフェクトの画像をロード
    //引数は「ファイル名」「横に何個並んでるか」「縦に何個並んでるか」
    //戻り値は画像番号
    hVfxA = VisualEffect::Load("Assets/SampleEffectA.png", 7, 7);
    hVfxB = VisualEffect::Load("Assets/SampleEffectB.png", 6, 5);


    //1個エフェクトを出す
    Transform transform;
    transform.position_ = XMFLOAT3(6, 7, -1);       //位置
    transform.scale_ = XMFLOAT3(3.0f, 3.0f, 1.0f);  //サイズ（デフォルトだと1辺が2ｍ）
    VisualEffect::Add(hVfxA, transform, 0.5f, true);//出す（引数は「画像番号」「トランスフォーム」「再生速度」「ループさせるかどうか」）




    //ブロックなどのモデルをロードする処理をまとめた関数
    ModelLoad();


    //SceneManagerクラスの情報を格納する
    if (pSceneManager_ == nullptr)
    {
        pSceneManager_ = (SceneManager*)Find("SceneManager");
    }


    //Csvファイルの読み込み
    CsvReader csv;


    //読み込まれたステージIDに対応するCSVファイルを読み込む
    switch(pSceneManager_->nextSceneID_)
    {
    case SCENE_ID_STAGE1: csv.Load("Assets/Stage/Stage1.csv");break;
    case SCENE_ID_STAGE2: csv.Load("Assets/Stage/Stage2.csv");break;
    case SCENE_ID_STAGE3: csv.Load("Assets/Stage/Stage3.csv");break;
    case SCENE_ID_STAGE4: csv.Load("Assets/Stage/Stage4.csv");break;
    }

    //プレイヤーの生成
    //200が入っているマスにプレイヤーが出現する
    //横
    for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
    {
        //縦
        for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
        {
            //エクセルだとyの値が逆なので縦軸-1をしてあげる
            map_[x][y] = csv.GetValue(x, (VERTICAL_VALU_-1) - y); 

            if (map_[x][y] == PLAYER_GENERAT_POS_)
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
    //最初は非表示で影を生成する
    pShadow_[shadowCount_] = (Shadow*)Instantiate<Shadow>(this->pParent_);
}



//更新
void Stage::Update()
{
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //1個エフェクトを出す
        Transform transform;
        transform.position_ = XMFLOAT3(15, 15, -1);       //位置
        transform.scale_ = XMFLOAT3(3.0f, 3.0f, 1.0f);  //サイズ（デフォルトだと1辺が2ｍ）
        VisualEffect::Add(hVfxB, transform, 0.5f, false);//出す（引数は「画像番号」「トランスフォーム」「再生速度」「ループさせるかどうか」）
    }




    //Player情報の格納
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }


    //再生スタート
    if (Input::IsKeyDown(DIK_1))
    {
        //点滅ブロックの情報をリセット
        timeCount_ = RESET_VALU_;
        isBlinking_ = true;


        //すでに生成している影を表示し、もう一度再生する
        if (shadowCount_ <= SHADOW_NAMBER_)
        {
            //すでに生成している影をもう一度1から再生する
            for (int i = RESET_VALU_; i <= shadowCount_; i++)
            {
                //表示するフラグ
                pShadow_[i]->ShadowDisplayFlag();
            }

            if (shadowCount_ <= SHADOW_NAMBER_ -1)
            {
                //二体目以降の影の番号
                shadowCount_++;
            }
        }

        //影の生成
        if (shadowCount_ <= SHADOW_NAMBER_)
        {
            pShadow_[shadowCount_] = (Shadow*)Instantiate<Shadow>(this);
        }
    }

    //保存された影の動きをすべてリセットする
    if (Input::IsKeyDown(DIK_2))
    {
        //今ある影分
        for (int i = RESET_VALU_; i <= shadowCount_; i++)
        {
            //解放処理
            pShadow_[i]->killMe();
        }
        //影の数をリセット
        shadowCount_ = RESET_VALU_;
    }

    //一定時間ごとにブロック切り替える
    Blinking(BRINKING_BLOCKS_, FRAME_TIME_);


    //同時ボタンのギミック
    //どちらもボタンを押していたら発動する
    if (isdoubleButton1_ && isdoubleButton2_)
    {
        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        {
            //モデルを切り替える
            CheckBlock(151 + i, true);
        }
    }
    //どちらかが、あるいはどちらも押していなければボタンは元に戻る
    else
    {
        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        {
            //モデルを切り替える
            CheckBlock(161 + i, false);
        }
    }
    ChengeButton();
}


//描画
void Stage::Draw()
{
    //ブロックの配置
    for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
    {
        for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
        {
            //プレイヤーの位置とブロックを置かない位置
            //その場合はそれ以降の処理はしない
            if (map_[x][y] == RESET_VALU_ || map_[x][y] == PLAYER_GENERAT_POS_)
            {
                continue;
            }

            //モデル番号の格納
            int type = map_[x][y] - 1;

            //位置
            //transの位置情報を決める
            Transform trans;
            trans.position_.x = x;
            trans.position_.y = y;

            //Calclationクラスで移動、回転、拡大行列の処理をする
            trans.Calclation();


            //モデルの表示
            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
        }
    }

    //背景の生成
    //ど真ん中に出す
    Transform back;

    //横軸の真ん中
    back.position_.x = BESIDE_VALU_ / 2;

    //縦軸の真ん中
    back.position_.y = VERTICAL_VALU_ / 2 + 1;

    //少し奥に
    back.position_.z = 0.5;

    //Calclationクラスで移動、回転、拡大行列の処理をする
    back.Calclation();

    //モデルの表示
    Model::SetTransform(hModel_[BACK_GROUND_], back);
    Model::Draw(hModel_[BACK_GROUND_]);
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
    if (map_[x][y] == 0 ||
        map_[x][y] == BACK_GROUND_ ||
        map_[x][y] == PLAYER_GENERAT_POS_ ||
        map_[x][y] == 91||
        map_[x][y] == 101||
        map_[x][y] == MEANTIME_BLOCK_ALPHA_ ||
        map_[x][y] == 62||
        map_[x][y] == 81||
        map_[x][y] == 161)
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
bool Stage::DownButton(int x, int y)
{
    //押している間ボタン
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        if (map_[x][y] == MEANTIME_BUTTON_UP_ + i || map_[x][y] == MEANTIME_BUTTON_DOWN_ + i)
        {

            return true;
        }
    }


    
    //同時押しボタン
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        if (map_[x][y] == 111 + i)
        {
            //ボタンのモデルを切り替える
            CheckBlock(map_[x][y], true);

            //フラグをtrueにする
            isdoubleButton1_ = true;
        }
        else if(map_[x][y] == 131 + i)
        {
            //ボタンのモデルを切り替える
            CheckBlock(map_[x][y], true);

            //フラグをtrueにする

            isdoubleButton2_ = true;
        }
    }
    


    //Playerが離れたら
    //もしくはリセットしたら
    if (steppingNumber == 0)
    {
        //押している間だけのボタンのモデルをリセットする
        //for (int i = RESET_VALU_; i <= shadowCount_; i++)
        //{
        //    if (pShadow_[i]->isRecording_ == false)
        //    {
        //        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        //        {
        //            //ボタンのモデルを切り替える
        //            CheckBlock(MEANTIME_BUTTON_DOWN_ + i, false);

        //            //壁のモデルを切り替える
        //            CheckBlock(MEANTIME_BLOCK_ALPHA_ + i, false);
        //        }
        //    }
        //}


        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        {
            //ボタンのモデルを切り替える
            CheckBlock(MEANTIME_BUTTON_DOWN_ + i, false);

            //壁のモデルを切り替える
            CheckBlock(MEANTIME_BLOCK_ALPHA_ + i, false);

            //押した後のボタンを切り替える
            CheckBlock(121 + i, false);

            //開いた壁を元に戻す
            CheckBlock(141 + i, false);
        }

        //同時ボタンのフラグ処理を初期化
        isdoubleButton1_ = false;
        isdoubleButton2_ = false;
    }
    return false;
}


//すべてのブロックを探して、モデルを切り替える関数
//第一引数は切り替えたいブロックの番号
//第二引数はプラスかマイナスか
void Stage::CheckBlock(int find , bool which)
{
    //横
    for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
    {
        //縦
        for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
        {

            //そこが引数で受け取ったブロックだったら
            //第二引数がfalseでモデル番号-10のモデルに切り替える
            if (map_[x][y] == find && which == false)
            {
                map_[x][y] = find - CHENGE_POSITIVE_GIMMICKS_;
            }

            //そこが引数で受け取ったブロックだったら
            //第二引数がtrueでモデル番号+10のモデルに切り替える
            else if(map_[x][y] == find && which == true)
            {
                map_[x][y] = find + CHENGE_POSITIVE_GIMMICKS_;
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

        //フラグをfalseにする
        isBlinking_ = false;

        //計測時間をリセット
        timeCount_ = RESET_VALU_;
    }
    //不透明にする
    else if(timeCount_ >= time && isBlinking_ == false)
    {
        //モデルを切り替える関数
        //引数に渡された値の-10のモデル番号を変える
        CheckBlock(blockNum - CHENGE_POSITIVE_GIMMICKS_, true);

        //フラグをtrueにする
        isBlinking_ = true;

        //計測時間をリセット
        timeCount_ = RESET_VALU_;
    }
}

//ゴールの処理をする関数
//引数は今プレイヤーのいる位置にあるマス
void Stage::GoalCol(int x, int y)
{
    //そこはゴール
    if (map_[x][y] == GOAL_BLOCK_)
    {
        //シーン移動
        //Find関数でSceneManagerクラスを探して
        //ChangeScene関数の引数に移動したいシーンのIDを渡す
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}

//
void Stage::WarpBlockCollision(int getX,int getY)
{
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //PlayerのPositionを引数で受け取る
        //そこがワープブロックだったら
        if (map_[getX][getY] == WARP_BLOCK_ENTRANS_ + i && isWarp_ == true)
        {
            //Stageのサイズ分調べる
            //横
            for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
            {
                //縦
                for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
                {
                    //そこがワープブロックの出口だったら
                    if (map_[x][y] == WARP_BLOCK_EXIT_ + i)
                    {
                        //Playerの位置をそこのワープブロックに反映させる
                        pPlayer_->transform_.position_.x = x;
                        pPlayer_->transform_.position_.y = y;

                        //永久ループ防止のためにフラグ処理をしておく
                        isWarp_ = false;
                    }
                }
            }
        }
    }


    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {

        //PlayerのPositionを引数で受け取る
        //そこがワープブロックだったら
        if (map_[getX][getY] == WARP_BLOCK_EXIT_ + i && isWarp_ == true)
        {

            //Stageのサイズ分調べる
            //横
            for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
            {
                //縦
                for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
                {
                    //そこがワープブロックの出口だったら
                    if (map_[x][y] == WARP_BLOCK_ENTRANS_ + i)
                    {
                        //Playerの位置をそこのワープブロックに反映させる
                        pPlayer_->transform_.position_.x = x;
                        pPlayer_->transform_.position_.y = y;

                        //永久ループ防止のためにフラグ処理をしておく
                        isWarp_ = false;
                    }
                }
            }
        }
    }


    //フラグ処理の初期化
    //引数はPlayerの位置
    //ワープブロックから離れたらフラグを初期化してもう一度入れるようにする
    if (map_[getX][getY] == RESET_VALU_)
    {
        isWarp_ = true;
    }
}

XMFLOAT3 Stage::GetStartPosition()
{
    steppingNumber = 0;
    return stertPos;
}

void Stage::Reset(int x, int y)
{
    if (map_[x][y] <= 2)
    {
        isOnButton = false;
    }
}

void Stage::ChengeButton()
{
    if (steppingNumber != 0)
    {
        //モデル変更
        CheckBlock(MEANTIME_BUTTON_UP_, true);

        //壁を開く処理
        CheckBlock(MEANTIME_WALL_, true);
    }
}

void Stage::StepNumberCountUp()
{
    steppingNumber++;
}

void Stage::StepNumberCountDown()
{
    steppingNumber--;
}



void Stage::ModelLoad()
{

    //ステージを構成するブロック
    hModel_[0] = Model::Load("Assets/StageBlock/Block.fbx");
    hModel_[1] = Model::Load("Assets/StageBlock/NaturalBlock.fbx");
    hModel_[2] = Model::Load("Assets/StageBlock/Goal.fbx");
    hModel_[3] = Model::Load("Assets/StageBlock/BackGround.fbx");
    hModel_[4] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[5] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[6] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[7] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[8] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[9] = Model::Load("Assets/GreenBlock.fbx");


    //押したら発動するボタン
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



    //開く壁(開く前)
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




    //同時押しボタン(押す前)
    hModel_[130] = Model::Load("Assets/&Button.fbx");
    hModel_[131] = Model::Load("Assets/&Button.fbx");
    hModel_[132] = Model::Load("Assets/&Button.fbx");
    hModel_[133] = Model::Load("Assets/&Button.fbx");
    hModel_[134] = Model::Load("Assets/&Button.fbx");
    hModel_[135] = Model::Load("Assets/&Button.fbx");
    hModel_[136] = Model::Load("Assets/&Button.fbx");
    hModel_[137] = Model::Load("Assets/&Button.fbx");
    hModel_[138] = Model::Load("Assets/&Button.fbx");
    hModel_[139] = Model::Load("Assets/&Button.fbx");



    //開く壁(開いた後)
    hModel_[140] = Model::Load("Assets/OrButton.fbx");
    hModel_[141] = Model::Load("Assets/OrButton.fbx");
    hModel_[142] = Model::Load("Assets/OrButton.fbx");
    hModel_[143] = Model::Load("Assets/OrButton.fbx");
    hModel_[144] = Model::Load("Assets/OrButton.fbx");
    hModel_[145] = Model::Load("Assets/OrButton.fbx");
    hModel_[146] = Model::Load("Assets/OrButton.fbx");
    hModel_[147] = Model::Load("Assets/OrButton.fbx");
    hModel_[148] = Model::Load("Assets/OrButton.fbx");
    hModel_[149] = Model::Load("Assets/OrButton.fbx");


    //同時ボタンが押されたら開く壁
    hModel_[150] = Model::Load("Assets/Wall.fbx");
    hModel_[151] = Model::Load("Assets/Wall.fbx");
    hModel_[152] = Model::Load("Assets/Wall.fbx");
    hModel_[153] = Model::Load("Assets/Wall.fbx");
    hModel_[154] = Model::Load("Assets/Wall.fbx");
    hModel_[155] = Model::Load("Assets/Wall.fbx");
    hModel_[156] = Model::Load("Assets/Wall.fbx");
    hModel_[157] = Model::Load("Assets/Wall.fbx");
    hModel_[158] = Model::Load("Assets/Wall.fbx");
    hModel_[159] = Model::Load("Assets/Wall.fbx");


    //同時ボタンが離れたら閉じる壁
    hModel_[160] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[161] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[162] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[163] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[164] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[165] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[166] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[167] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[168] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[169] = Model::Load("Assets/AlphaBlock.fbx");
}

