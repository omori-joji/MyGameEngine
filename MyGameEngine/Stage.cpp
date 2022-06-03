#include "Player.h"
#include "Stage.h"
#include "Shadow.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    hModel_(),                              //すべてのステージモデルを格納する変数
    map_(),                                 //ステージを管理する多次元配列
    hSound_(),                              //SEとBGMを格納する変数
    PLAYER_GENERAT_POS_(200),               //Playerの初期位置
    SHADOW_NAMBER_(5),                      //影の最大数
    ALL_GIMMICKS_(10),                      //1種類のギミックを何個あるか調べる値
    RESET_VALU_(0),                         //初期化用の値
    CHENGE_POSITIVE_GIMMICKS_(10),          //モデルを変更するための値
    BRINKING_BLOCKS_(81),                   //点滅するブロック
    FRAME_TIME_(60),                        //点滅する間隔
    BACK_GROUND_(3),                        //背景のモデル番号
    MEANTIME_BUTTON_UP_(31),                //踏んでいる間発動するボタンの踏む前のモデル番号
    MEANTIME_BUTTON_DOWN_(41),              //踏んでいる間発動するボタンの踏んだあとのモデル番号
    MEANTIME_WALL_(51),                     //ボタンが踏まれていない間閉じている壁のモデル番号
    MEANTIME_BLOCK_ALPHA_(61),              //ボタンが踏まれている間開いている壁のモデル番号
    NO1_WARP_BLOCK_(91),                    //片方のワープブロックのモデル番号
    NO2_WARP_BLOCK_(101),                   //もう片方のワープブロックのモデル番号
    GOAL_BLOCK_(3),                         //ゴールブロックのモデル番号
    shadowCount_(0),                        //今いる影の数
    timeCount_(0),                          //秒数を格納する変数
    FILE_PAS_("Assets/StageBlock/"),        //モデルのファイルパス
    pPlayer_(nullptr),                      //Playerクラスを格納するポインタ
    pShadow_(),                             //Shadowクラスを格納するポインタ
    pSceneManager_(nullptr),                //SceneManagerクラスを格納するポインタ
    stertPos_(0,0,0),                       //Playerの初期位置を記憶する変数
    isBlinking_(true),                      //壁が消えたか消えていないか
    isWarp_(true),                          //ワープしたかしていないか
    isMultiButton_(),                       //同時押しボタンの二つ押したか判別するフラグ
    steppingNumberMeanTime_(),              //ボタンに乗っている人数を記憶する変数
    steppingNumber_No1Multi_(),             //ボタンに乗っている人数を記憶する変数
    steppingNumber_No2Multi_(),             //ボタンに乗っている人数を記憶する変数
    NO1_MULTI_BUTTON_UP_(111),              //同時押しボタンの片方。踏んでいない状態のモデル番号
    NO1_MULTI_BUTTON_DOWN_(121),            //同時押しボタンの片方。踏んでいる状態のモデル番号
    NO2_MULTI_BUTTON_UP_(131),              //同時押しボタンのもう片方。踏んでいない状態のモデル番号
    NO2_MULTI_BUTTON_DOWN_(141),            //同時押しボタンの片方。踏んでいる状態のモデル番号
    MULTI_BUTTON_WALL_(151),                //同時押しボタンに対応した壁。開いてない状態のモデル番号
    MULTI_BUTTON_WALL_ALPHA_(161)           //同時押しボタンに対応した壁。開いている状態のモデル番号
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
    //Csvファイルの読み込み
    CsvReader csv;
    //SceneManagerクラスの情報を格納する
    if (pSceneManager_ == nullptr) pSceneManager_ = (SceneManager*)Find("SceneManager");

    //読み込まれたステージIDに対応するCSVファイルを読み込む
    switch (pSceneManager_->nextSceneID_)
    {
    case SCENE_ID_STAGE1: csv.Load("Assets/Stage/Stage1.csv"); break;
    case SCENE_ID_STAGE2: csv.Load("Assets/Stage/Stage2.csv"); break;
    case SCENE_ID_STAGE3: csv.Load("Assets/Stage/Stage3.csv"); break;
    case SCENE_ID_STAGE4: csv.Load("Assets/Stage/Stage4.csv"); break;
    case SCENE_ID_DEBUG: csv.Load("Assets/Stage/Debug.csv"); break;
    }

    //プレイヤーの生成
    //200が入っているマスにプレイヤーが出現する
    //横
    for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
    {
        //縦
        for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
        {
            //エクセルだとyの値が逆なので縦軸-1をしてあげる
            map_[x][y] = csv.GetValue(x, (MAP_VERTICAL - 1) - y);

            if (map_[x][y] == PLAYER_GENERAT_POS_)
            {
                //プレイヤーの生成
                //プレイヤーの位置決定
                //プレイヤーの初期位置を記憶する
                Player* pPlayer = (Player*)Instantiate<Player>(this->pParent_);
                pPlayer->transform_.position_.x = (float)x;
                pPlayer->transform_.position_.y = (float)y;
                stertPos_ = pPlayer->transform_.position_;
            }
        }
    }

    //影の生成
    //最初は非表示で影を生成する
    pShadow_[shadowCount_] = (Shadow*)Instantiate<Shadow>(this->pParent_);

    //BGNを鳴らす
    Audio::Play(hSound_[BGM]);
}

//更新
void Stage::Update()
{
    //Player情報の格納
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }

    //影を再生する処理をまとめた関数
    PlayRecord();

    //一定時間ごとにブロック切り替える
    Blinking(BRINKING_BLOCKS_, FRAME_TIME_);
}

//描画
void Stage::Draw()
{
    //背景の生成
    //ど真ん中に出す
    Transform back;

    //横軸の真ん中
    back.position_.x = MAP_BESIDE_ / 2;

    //縦軸の真ん中
    back.position_.y = MAP_VERTICAL / 2 + 1;

    //少し奥に
    back.position_.z = 0.5;

    //Calclationクラスで移動、回転、拡大行列の処理をする
    back.Calclation();

    //モデルの表示
    Model::SetTransform(hModel_[BACK_GROUND_], back);
    Model::Draw(hModel_[BACK_GROUND_]);

    //ブロックの配置
    for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
    {
        for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
        {
            //プレイヤーの位置とブロックを置かない位置
            //その場合はそれ以降の処理はしない
            if (map_[x][y] == RESET_VALU_ || map_[x][y] == PLAYER_GENERAT_POS_) continue;

            //モデル番号の格納
            int type = map_[x][y] - 1;

            //位置
            //transの位置情報を決める
            Transform trans;
            trans.position_.x = (float)x;
            trans.position_.y = (float)y;

            //Calclationクラスで移動、回転、拡大行列の処理をする
            trans.Calclation();

            //モデルの表示
            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
        }
    }
}

//踏んでいる間発動するボタンがあるかどうかの処理を実行する
//引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
//戻り値：踏んでいればtrue踏んでいなければfalse
bool Stage::MeanTimeButton(int x, int y)
{
    //押している間ボタン
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //下にあるボタンが踏んでいる間だけのボタンもしくは踏んだ後のボタンだったら
        if (map_[x][y] == MEANTIME_BUTTON_UP_ + i || map_[x][y] == MEANTIME_BUTTON_DOWN_ + i) return true;
    }

    //離れた時の処理
    CollisionExit();
    return false;
}

//同時押しボタンの片方に乗ったらtrueそれ以外はfalseを返す関数
//引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
//戻り値：踏んでいればtrue踏んでいなければfalse
bool Stage::No1MultiButton(int x, int y)
{
    //同時押しボタン
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //下にあるボタンが同時押しボタンの押す前、もしくは押した後のモデルだったら
        if (map_[x][y] == NO1_MULTI_BUTTON_UP_ + i || map_[x][y] == NO1_MULTI_BUTTON_DOWN_ + i) return true;
    }
    //離れた時の処理
    CollisionExit();
    return false;
}

//同時押しボタンのもう片方に乗ったらtrueそれ以外はfalseを返す関数
//引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
//戻り値：踏んでいればtrue踏んでいなければfalse
bool Stage::No2MultiButton(int x, int y)
{
    //同時押しボタン
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //下にあるボタンが同時押しボタンの押す前、もしくは押した後のモデルだったら
        if (map_[x][y] == NO2_MULTI_BUTTON_UP_ + i || map_[x][y] == NO2_MULTI_BUTTON_DOWN_ + i) return true;
    }
    //離れた時の処理
    CollisionExit();
    return false;
}

//ボタンから離れたら呼ばれる関数、モデルを切り替える処理を行う
//引数：なし
//戻り値：なし
void Stage::CollisionExit()
{
    //押している間だけのボタン
    //すべてのギミックを調べる
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //押している間だけ発動するボタンに乗っている人数が0人だったら
        if (steppingNumberMeanTime_[i] == 0)
        {
            //ボタンのモデルを切り替える
            CheckBlock(MEANTIME_BUTTON_DOWN_ + i, false);

            //壁のモデルを切り替える
            CheckBlock(MEANTIME_BLOCK_ALPHA_ + i, false);
        }
    }

    //同時押しボタンの片方のボタン
    //すべてのギミックを調べる
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //同時押しボタンの片方のボタンに乗っている人数が0人だったら
        if (steppingNumber_No1Multi_[i] == 0)
        {
            //ボタンのモデルを切り替える
            CheckBlock(NO1_MULTI_BUTTON_DOWN_ + i, false);

            //壁を開くフラグをtrueにする
            isMultiButton_[0] = false;
        }
    }

    //同時押しボタンのもう片方のボタン
    //すべてのギミックを調べる
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //同時押しボタンのもう片方のボタンに乗っている人数が0人だったら
        if (steppingNumber_No2Multi_[i] == 0)
        {
            //ボタンのモデルを切り替える
            CheckBlock(NO2_MULTI_BUTTON_DOWN_ + i, false);

            //壁を開くフラグをtrueにする
            isMultiButton_[1] = false;
        }
    }
}

//壁のモデルとボタンのモデルを切り替える関数。
//引数：なし
//戻り値：なし
void Stage::ChengeButtonAndWall()
{
    //押している間発動するボタン
    //すべての壁を探す
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //誰かが押している間発動するボタンに乗っていたら
        if (steppingNumberMeanTime_[i] != 0)
        {
            //モデル変更
            //ボタンを先に変えるとそれに対応した壁をひらけないので壁を先に変える
            CheckBlock((MEANTIME_BUTTON_UP_ + i) + 20, true);

            //ボタンのモデル
            CheckBlock(MEANTIME_BUTTON_UP_ + i, true);
        }
    }

    //片方の同時押しボタン
    //すべての壁を調べる
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //誰かが同時ボタンに乗っていたら
        if (steppingNumber_No1Multi_[i] != 0)
        {
            //モデル変更
            CheckBlock(NO1_MULTI_BUTTON_UP_ + i, true);

            //壁を開くフラグをtrueにする
            isMultiButton_[0] = true;

            //同時ボタンが2つとも押されていたら壁を開く処理をする関数
            SimultaneousWallOpen();
        }
    }

    //上記と同じ処理なのでコメントは省略
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        if (steppingNumber_No2Multi_[i] != 0)
        {
            CheckBlock(NO2_MULTI_BUTTON_UP_ + i, true);
            isMultiButton_[1] = true;
            SimultaneousWallOpen();
        }
    }
}

//同時押しボタンがどちらも押されていたら。壁を開き、それ以外の条件だったら壁を閉じる関数
//引数：なし
//戻り値：なし
void Stage::SimultaneousWallOpen()
{
    //同時ボタンのギミック
    //どちらもボタンを押していたら壁を開く
    if (isMultiButton_[0] && isMultiButton_[1]) CheckBlock(MULTI_BUTTON_WALL_, true);

    //それ以外の条件の場合
    //壁を閉じる
    else CheckBlock(MULTI_BUTTON_WALL_ALPHA_, false);
}

//足元のブロックのモデル番号を引数で受け取り、それの1の位を返す関数
//引数：Player、ShadowのPosition.x_とPosition.y_ -1(足元)
//戻り値：ボタンのモデル番号の1の位
int Stage::CheckFootBlock(int x, int y)
{
    //1の位を返す
    return (map_[x][y] % 10) -1;
}

//影の再生するフラグと生成の処理を行う関数
//引数：なし
//戻り値：なし
void Stage::PlayRecord()
{
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
                pShadow_[i]->ShadowIsPlayFlag();
            }

            //影の数がまだ余っていたら
            //二体目以降の影の番号
            if (shadowCount_ <= SHADOW_NAMBER_ -1) shadowCount_++;
        }
        //影の生成
        if (shadowCount_ <= SHADOW_NAMBER_) { pShadow_[shadowCount_] = (Shadow*)Instantiate<Shadow>(this); }
    }

    if (Input::IsKeyDown(DIK_3))
    {
        for (int i = 0; i < shadowCount_; i++)
        {
            pShadow_[i]->killMe();
        }
        shadowCount_ = 0;
    }
}

//ボタンに乗っている人数をカウントアップする関数
//引数：踏んでいる間発動するボタンのモデル番号の1の位
//戻り値：なし
void Stage::SetMeanTimeStepNumberCountUp(int meanTimeNum)
{
    steppingNumberMeanTime_[meanTimeNum]++;
}

//ボタンに乗っている人数をカウントダウンする関数
//引数：踏んでいる間発動するボタンのモデル番号の1の位
//戻り値：なし
void Stage::SetMeanTimeStepNumberCountDown(int meanTimeNum)
{
    steppingNumberMeanTime_[meanTimeNum]--;
}

//同時押しボタンの片方のボタンの乗っている人数をカウントアップする関数
//引数：同時押しボタンのモデル番号の1の位
//戻り値：なし
void Stage::SetNo1MultiStepNumberCountUp(int onDoubleNum)
{
    steppingNumber_No1Multi_[onDoubleNum]++;
}

//同時押しボタンの片方のボタンの乗っている人数をカウントダウンする関数
//引数：同時押しボタンのモデル番号の1の位
//戻り値：なし
void Stage::SetNo1MultiStepNumberCountDown(int onDoubleNum)
{
    steppingNumber_No1Multi_[onDoubleNum]--;
}

//同時押しボタンのもう片方のボタンの乗っている人数をカウントアップする関数
//引数：同時押しボタンのモデル番号の1の位
//戻り値：なし
void Stage::SetNo2MultiStepNumberCountUp(int orDunbleNum)
{
    steppingNumber_No2Multi_[orDunbleNum]++;
}

//同時押しボタンのもう片方のボタンの乗っている人数をカウントダウンする関数
//引数：同時押しボタンのモデル番号の1の位
//戻り値：なし
void Stage::SetNo2MultiStepNumberCountDown(int orDunbleNum)
{
    steppingNumber_No2Multi_[orDunbleNum]--;
}

//ワープブロックのギミックをまとめた関数。
//引数：getX, getY プレイヤーの位置
//戻値：なし
void Stage::WarpBlockCollision(int getX, int getY)
{
    //すべてのワープブロックを調べる
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //そこがワープブロックだったら
        if (map_[getX][getY] == NO1_WARP_BLOCK_ + i && isWarp_ == true)
        {
            //Stageのサイズ分調べる
            //横
            for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
            {
                //縦
                for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
                {
                    //そこがワープブロックの出口だったら
                    if (map_[x][y] == NO2_WARP_BLOCK_ + i)
                    {
                        //Playerの位置をそこのワープブロックに反映させる
                        pPlayer_->transform_.position_.x = (float)x;
                        pPlayer_->transform_.position_.y = (float)y;

                        //永久ループ防止のためにフラグ処理をしておく
                        isWarp_ = false;
                    }
                }
            }
        }
    }

    //すべてのワープブロックを調べる
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //そこがワープブロックだったら
        if (map_[getX][getY] == NO2_WARP_BLOCK_ + i && isWarp_ == true)
        {
            //Stageのサイズ分調べる
            //横
            for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
            {
                //縦
                for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
                {
                    //そこがワープブロックの出口だったら
                    if (map_[x][y] == NO1_WARP_BLOCK_ + i)
                    {
                        //Playerの位置をそこのワープブロックに反映させる
                        pPlayer_->transform_.position_.x = (float)x;
                        pPlayer_->transform_.position_.y = (float)y;

                        //永久ループ防止のためにフラグ処理をしておく
                        isWarp_ = false;
                    }
                }
            }
        }
    }
    //フラグ処理の初期化
    //Playerがワープブロックから離れたら
    //ワープブロックから離れたらフラグを初期化してもう一度入れるようにする
    if (map_[getX][getY] == RESET_VALU_) isWarp_ = true;
}

//点滅ブロックのギミックをまとめた関数。
//引数：点滅したいブロックのモデル番号, 点滅間隔。単位はフレーム
//戻り値：なし
void Stage::Blinking(int blockNum, int time)
{
    //計測
    timeCount_++;

    //透明にする
    if (timeCount_ >= time && isBlinking_ == true)
    {
        //モデルを切り替える関数
        CheckBlock(blockNum, false);

        //フラグをfalseにする
        isBlinking_ = false;

        //計測時間をリセット
        timeCount_ = RESET_VALU_;
    }
    //不透明にする
    else if (timeCount_ >= time && isBlinking_ == false)
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

//モデルを切り替える関数。
//引数：変更したいモデル番号, trueで+10されたモデルに、falseで-10されたモデルに変更
//戻り値：なし
void Stage::CheckBlock(int find, bool which)
{
    //Stageのサイズ分調べる
    //横
    for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
    {
        //縦
        for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
        {
            //そこが引数で受け取ったブロックだったら
            //第二引数がfalseでモデル番号-10のモデルに切り替える
            if (map_[x][y] == find && which == false) map_[x][y] = find - CHENGE_POSITIVE_GIMMICKS_;

            //そこが引数で受け取ったブロックだったら
            //第二引数がtrueでモデル番号+10のモデルに切り替える
            else if (map_[x][y] == find && which == true) map_[x][y] = find + CHENGE_POSITIVE_GIMMICKS_;
        }
    }
}

//ゴールを判定し、シーンを切り替える関数
//引数：PlayerのPosition.x_とPosition.y_
//戻り値：なし
void Stage::GoalCol(int x, int y)
{
    //そこはゴール
    if (map_[x][y] == GOAL_BLOCK_)
    {
        Audio::Stop(hSound_[0]);
        //シーン移動
        //Find関数でSceneManagerクラスを探して
        //ChangeScene関数の引数に移動したいシーンのIDを渡す
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}

//ぶつかったかどうか
//引数：PlayerのPosition.x_とPosition.y_
//戻り値：ぶつかったらfalse、何もなければtrue
bool Stage::isCrash(int x, int y)
{
    //当たり判定のないブロックを設定する
    if (map_[x][y] == 0 ||
        map_[x][y] == BACK_GROUND_ ||
        map_[x][y] == PLAYER_GENERAT_POS_ ||
        map_[x][y] == NO1_WARP_BLOCK_ ||
        map_[x][y] == NO2_WARP_BLOCK_ ||
        map_[x][y] == MEANTIME_BLOCK_ALPHA_ ||
        map_[x][y] == MEANTIME_BLOCK_ALPHA_ + 1 ||
        map_[x][y] == BRINKING_BLOCKS_ ||
        map_[x][y] == MULTI_BUTTON_WALL_ALPHA_)
    {
        return false;
    }
    return true;
}

//初期スポーン地点を返すゲッター
//引数：なし
 //戻り値：stertPos_
XMFLOAT3 Stage::GetStartPosition()
{
    return stertPos_;
}

//開放
void Stage::Release()
{
}

//Load処理を10回ループする関数
//引数：モデルを格納したい配列の初期値, ファイルネーム(fbxの名前だけでOK)
//戻り値：なし
void Stage::LoopLoad(int modelNum, string modelName)
{
    for (int i = modelNum; i < modelNum + 10; i++)
    {
        hModel_[i] = Model::Load(FILE_PAS_ + modelName);
    }
}


//モデルをロードする処理をまとめた関数
//引数：なし
//戻り値：なし
void Stage::ModelLoad()
{
    //サウンドデータのロード
    hSound_[BGM] = Audio::Load("Assets/Sound/GameBGM.wav", 4);
    hSound_[SE_GOAl] = Audio::Load("Assets/Sound/Goal.wav",4);
    hSound_[SE_WARPE] = Audio::Load("Assets/Sound/Warpe.wav",4);

    //ステージを構成するブロック
    hModel_[0] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[1] = Model::Load(FILE_PAS_ + "Block_03.fbx");
    hModel_[2] = Model::Load(FILE_PAS_ + "Goal.fbx");
    hModel_[3] = Model::Load(FILE_PAS_ + "GameBG.fbx");
    hModel_[4] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[5] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[6] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[7] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[8] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[9] = Model::Load(FILE_PAS_ + "Block_01.fbx");

    //押したら発動するボタン
    LoopLoad(10, "PushButton.fbx");

    //押したら開き続ける壁
    LoopLoad(20, "Wall_01.fbx");

    //押している間だけ発動するボタン(押す前)
    LoopLoad(30, "MeantimeButto_up.fbx");

    //押している間だけ発動するボタン(押した後)
    LoopLoad(40, "MeantimeButto_down.fbx");

    //開く壁
    LoopLoad(50, "Wall_01.fbx");

    //開いている間の何もないブロック
    LoopLoad(60, "Wall_02.fbx");

    //点滅するブロック(消える前)
    LoopLoad(70, "Wall_01.fbx");

    //点滅するブロック(消えた後)
    LoopLoad(80, "Wall_02.fbx");

    //ワープブロック(入口)
    LoopLoad(90, "WarpEntrance.fbx");

    //ワープブロック(出口)
    LoopLoad(100, "WarpExit.fbx");

    //同時押しボタン(押す前)
    LoopLoad(110, "MultiButton_01_up.fbx");

    //同時押しボタン(押した後)
    LoopLoad(120, "MultiButton_01_down.fbx");

    //同時押しボタン(押す前)
    LoopLoad(130, "MultiButton_02_up.fbx");

    //同時押しボタン(押した後)
    LoopLoad(140, "MultiButton_02_down.fbx");

    //同時ボタンが押されたら開く壁
    LoopLoad(150, "Wall_01.fbx");

    //同時ボタンが離れたら閉じる壁
    LoopLoad(160, "Wall_02.fbx");
}

