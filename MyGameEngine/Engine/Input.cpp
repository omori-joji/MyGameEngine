#include "Input.h"

//���O���
namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;			//DirectInput�̗p��
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;	//�L�[�{�[�h�̏���p��	
	BYTE keyState[256] = { 0 };					//�L�[�̐�(�ꉞ�]���ɗp�ӂ��Ă���)
	BYTE prevKeyState[256];						//�O�t���[���ł̊e�L�[�̏��

	//������
	void Initialize(HWND hWnd)
	{
		//DirectInput�̗p��
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		//�L�[�{�[�h�̏���p��
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	//�X�V
	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));

		//���̃L�[��������Ă��邩�𒲂ׂ�
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	//�����ŃL�[�R�[�h���󂯎��
	//������Ă��邩�𒲂ׂ�̂Ŗ߂�l��bool�^�ɂ���
	bool IsKey(int keyCode)
	{
		//�n���ꂽ�L�[�ԍ��̔z���1������Atrue���Ԃ����
		if (keyState[keyCode] & 0x80) //0x80 != 0�̏ȗ�
		{
			return true;
		}
		return false;
	}

	//��ō�����֐����g���A�������u�Ԃ��擾����
	//�������u�Ԃ𒲂ׂ�̂Ŗ߂�l��bool�^�ɂ���
	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//�������u�Ԃ𒲂ׂ�
	//���ꂽ�u�Ԃ𒲂ׂ�̂Ŗ߂�l��bool�^�ɂ���
	bool IsKeyUp(int keyCode)
	{
		//���͉������Ȃ��A�O��͉����Ă���
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//���
	void Release()
	{
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}
}
