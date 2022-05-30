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


const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const int WINDOW_WIDTH = 800;               //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600;              //�E�B���h�E�̍���

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Rootjob�N���X�̃|�C���^�쐬
Rootjob* pRootJob;


//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    //�E�B���h�E�N���X�i�݌v�}�j���쐬
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
    wc.lpszClassName = WIN_CLASS_NAME;          //�E�B���h�E�N���X��
    wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
    wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
    wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j

    RegisterClassEx(&wc);  //�N���X��o�^

    //�E�B���h�E�T�C�Y�̌v�Z
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

    int winW = winRect.right - winRect.left;                    //�E�B���h�E��
    int winH = winRect.bottom - winRect.top;                    //�E�B���h�E����


    //�E�B���h�E���쐬
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //�E�B���h�E�N���X��
        "RAN BACK AND RUN",     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW,    //�X�^�C���i���ʂ̃E�B���h�E�j
        CW_USEDEFAULT,          //�\���ʒu���i���܂����j
        CW_USEDEFAULT,          //�\���ʒu��i���܂����j
        winW,                   //�E�B���h�E��
        winH,                   //�E�B���h�E����
        NULL,                   //�e�E�C���h�E�i�Ȃ��j
        NULL,                   //���j���[�i�Ȃ��j
        hInstance,              //�C���X�^���X
        NULL                    //�p�����[�^�i�Ȃ��j
    );

    //�E�B���h�E��\��
    ShowWindow(hWnd, nCmdShow);

    //�N���X�̏�����
    Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
    Input::Initialize(hWnd);
    Camera::Initialize();
    VisualEffect::Initialize();
    Audio::Initialize();

    //Rootjob�̍쐬�Ə�����
    pRootJob = new Rootjob;
    pRootJob->Initialize();



    //���b�Z�[�W���[�v�i�����N����̂�҂j
    MSG msg;
    //0�ɂ��Ă���
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //�v���O�����̏I��
        if (Input::IsKey(DIK_ESCAPE))
        {
            PostQuitMessage(0);
        }

        //���b�Z�[�W�Ȃ�
        else
        {
            //�^�C�}�[�̍ŏ����x��1�~���b�ɂ���
            timeBeginPeriod(1);

            //�o�ߎ��Ԃ��擾����
            static DWORD countFps = 0;
            static DWORD startTime = timeGetTime();//�v���O�������N�����Ă���̎��Ԃ��i�[
            DWORD nowTime = timeGetTime(); //PC���N�����Ă���̎��Ԃ��i�[
            static DWORD lastUpdateTime = nowTime;


            timeEndPeriod(1);

            //���݂̎��ԁ[�X�^�[�g�������̎��Ԃ�1000(1�b)�o������
            if (nowTime - startTime >= 1000)
            {
                countFps = 0;           //�J�E���g�����Z�b�g����
                startTime = nowTime;    //startTime�����̎��̎��Ԃɂ���
            }


            if ((nowTime - lastUpdateTime) * 60 <= 1000.0f)
            {
                continue;
            }
            //�O��Update���Ă΂ꂽ���Ԃ��L�^
            lastUpdateTime = nowTime;


            countFps++;

            //�Q�[���̏���
            //���ۂɎg���N���X��Update�֐����Ă�
            Input::Update();
            pRootJob->UpdateSub();
            Camera::Update();
            VisualEffect::Update();
            Direct3D::BeginDraw();

            //�`�揈��
            //���ۂɎg���N���X��Update�֐����Ă�
            pRootJob->DrawSub();
            VisualEffect::Draw();
            Direct3D::EndDraw();
        }
    }

    //�������
    VisualEffect::Release();
    Model::AllRelease();
    pRootJob->ReleaseSub();
    SAFE_DELETE(pRootJob);
    Input::Release();
    Direct3D::Release();
	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:

         PostQuitMessage(0);  //�v���O�����I��
         return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}