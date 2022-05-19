#include <Windows.h>
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Rootjob.h"
#include "Engine/Model.h"
#include "Engine/VisualEffect.h"
#include "Engine/Audio.h"
#include <stdlib.h>
#include "Engine/GameObject.h"

#pragma comment(lib, "winmm.lib")


const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;               //ウィンドウの幅
const int WINDOW_HEIGHT = 600;              //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Rootjob* pRootJob;


//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    //ウィンドウクラス（設計図）を作成
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
    wc.hInstance = hInstance;                   //インスタンスハンドル
    wc.lpszClassName = WIN_CLASS_NAME;          //ウィンドウクラス名
    wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
    wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
    wc.lpszMenuName = NULL;                     //メニュー（なし）
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

    RegisterClassEx(&wc);  //クラスを登録

    //ウィンドウサイズの計算
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;                    //ウィンドウ幅
    int winH = winRect.bottom - winRect.top;                    //ウィンドウ高さ


    //ウィンドウを作成
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //ウィンドウクラス名
        "RAN BACK AND RUN",     //タイトルバーに表示する内容
        WS_OVERLAPPEDWINDOW,    //スタイル（普通のウィンドウ）
        CW_USEDEFAULT,          //表示位置左（おまかせ）
        CW_USEDEFAULT,          //表示位置上（おまかせ）
        winW,                   //ウィンドウ幅
        winH,                   //ウィンドウ高さ
        NULL,                   //親ウインドウ（なし）
        NULL,                   //メニュー（なし）
        hInstance,              //インスタンス
        NULL                    //パラメータ（なし）
    );

    //ウィンドウを表示
    ShowWindow(hWnd, nCmdShow);

    //クラスの初期化
    Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
    Input::Initialize(hWnd);
    Camera::Initialize();
    VisualEffect::Initialize();
    Audio::Initialize();

    pRootJob = new Rootjob;
    pRootJob->Initialize();

    //メッセージループ（何か起きるのを待つ）
    MSG msg;
    //0にしておく
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
            //タイマーの最小精度を1ミリ秒にする
            timeBeginPeriod(1);

            //経過時間を取得する
            static DWORD countFps = 0;              //カウンター。何回画面が更新したか
            static DWORD startTime = timeGetTime(); //プログラムを起動してからの時間を格納
            DWORD nowTime = timeGetTime();          //PCが起動してからの時間を格納
            static DWORD lastUpdateTime = nowTime;  //現在の計測時間

            //タイマーの最小精度を戻す
            timeEndPeriod(1);

            //現在の時間ースタートした時の時間が1000(1秒)経ったら
            if (nowTime - startTime >= 1000)
            {
                countFps = 0;           //カウントをリセットする
                startTime = nowTime;    //startTimeをその時の時間にする
            }

            //1ミリ秒たったら
            if ((nowTime - lastUpdateTime) * 60 <= 1000.0f)
            {
                continue;
            }
            //前回Updateが呼ばれた時間を記録
            lastUpdateTime = nowTime;
            //カウントアップ
            countFps++;

            //ゲームの処理
            //実際に使うクラスのUpdate関数を呼ぶ
            Input::Update();
            pRootJob->UpdateSub();
            Camera::Update();
            VisualEffect::Update();
            Direct3D::BeginDraw();

            //描画処理
            //実際に使うクラスのUpdate関数を呼ぶ
            pRootJob->DrawSub();
            VisualEffect::Draw();
            Direct3D::EndDraw();
        }
    }

    //解放処理
    VisualEffect::Release();
    Model::AllRelease();
    pRootJob->ReleaseSub();
    SAFE_DELETE(pRootJob);
    Input::Release();
    Direct3D::Release();
	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:

         PostQuitMessage(0);  //プログラム終了
         return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}