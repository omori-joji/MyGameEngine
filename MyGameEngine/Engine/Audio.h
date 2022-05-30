#pragma once
#include <xaudio2.h>
#include <vector>
#include <vector>
#include <string>
#include "Common.h"
//#include "Sound.h"


//-----------------------------------------------------------
//���ʉ����Ǘ�����
//-----------------------------------------------------------
namespace Audio
{
	//������
	//�����FhWnd	�E�B���h�E�n���h��
	void Initialize();


	//�T�E���h�t�@�C�������[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̃T�E���h�f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName, int svNuM);

	//�Đ�
	//�����Fhandle	�Đ��������T�E���h�̔ԍ�
	void Play(int handle);

	//��~
	//�����Fhandle	�~�߂����T�E���h�̔ԍ�
	void Stop(int handle);

	//�C�ӂ̃T�E���h���J��
	//�����Fhandle	�J���������T�E���h�̔ԍ�
	void Release();
}