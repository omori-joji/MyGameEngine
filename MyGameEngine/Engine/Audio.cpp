#include "Audio.h"

#define SAFE_DELETE_ARRAY(p) if(p){delete[] p; p = nullptr;}

namespace Audio
{
	//XAudio本体
	IXAudio2* pXAudio = nullptr;

	//マスターボイス
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;

	//ファイル毎に必要な情報
	struct AudioData
	{
		//サウンド情報
		XAUDIO2_BUFFER buf = {};

		//ソースボイス
		IXAudio2SourceVoice** pSourceVoice = nullptr;

		//同時再生最大数
		int svNum;

		//ファイル名
		std::string fileName;
	};
	std::vector<AudioData>	audioDatas;
}

//初期化
void Audio::Initialize()
{
	XAudio2Create(&pXAudio);
	pXAudio->CreateMasteringVoice(&pMasteringVoice);
}

//サウンドファイル(.wav）をロード
int Audio::Load(std::string fileName, int svNuM)
{
	//すでに同じファイルを使ってないかチェック
	for (int i = 0; i < audioDatas.size(); i++)
	{
		if (audioDatas[i].fileName == fileName)
		{
			return i;
		}
	}

	struct Chunk
	{
		char	id[4]; 		// ID
		unsigned int	size;	// サイズ
	};

	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwBytes = 0;

	Chunk riffChunk;
	ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL);
	ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL);

	char wave[4];
	ReadFile(hFile, &wave, 4, &dwBytes, NULL);

	Chunk formatChunk;
	while (formatChunk.id[0] != 'f') {
		ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL);
	}
	ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL);

	WAVEFORMATEX fmt;

	ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL);
	ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL);
	ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL);
	ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL);
	ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL);
	ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL);

	/*
	fmt.wFormatTag = WAVE_FORMAT_PCM;
	fmt.nChannels = 2;
	fmt.nSamplesPerSec = 44100L;
	fmt.nAvgBytesPerSec = 176400L;
	fmt.nBlockAlign = 4;
	fmt.wBitsPerSample = 16;
	fmt.cbSize = 0;
	*/

	Chunk data;

	while (data.id[0] != 'd') {
		ReadFile(hFile, &data.id, 4, &dwBytes, NULL);
	}
	ReadFile(hFile, &data.size, 4, &dwBytes, NULL);

	char* pBuffer = new char[data.size];
	ReadFile(hFile, pBuffer, data.size, &dwBytes, NULL);
	CloseHandle(hFile);


	AudioData ad;

	ad.fileName = fileName;

	ad.buf.pAudioData = (BYTE*)pBuffer;
	ad.buf.Flags = XAUDIO2_END_OF_STREAM;
	ad.buf.AudioBytes = data.size;

	ad.pSourceVoice = new IXAudio2SourceVoice * [svNuM];

	for (int i = 0; i < svNuM; i++)
	{
		pXAudio->CreateSourceVoice(&ad.pSourceVoice[i], &fmt);
	}
	ad.svNum = svNuM;
	audioDatas.push_back(ad);

	//SAFE_DELETE_ARRAY(pBuffer);

	return (int)audioDatas.size() - 1;
}

//再生
void Audio::Play(int ID)
{
	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		XAUDIO2_VOICE_STATE state;
		audioDatas[ID].pSourceVoice[i]->GetState(&state);

		if (state.BuffersQueued == 0)
		{
			audioDatas[ID].pSourceVoice[i]->SubmitSourceBuffer(&audioDatas[ID].buf);
			audioDatas[ID].pSourceVoice[i]->Start();
			break;
		}
	}
}

//停止
void Audio::Stop(int ID)
{
	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		audioDatas[ID].pSourceVoice[i]->Stop();
		audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
	}
}

//すべて開放
void Audio::Release()
{
	for (int i = 0; i < audioDatas.size(); i++)
	{
		for (int j = 0; j < audioDatas[i].svNum; j++)
		{
			audioDatas[i].pSourceVoice[j]->DestroyVoice();
		}
		SAFE_DELETE_ARRAY(audioDatas[i].buf.pAudioData);
	}

	CoUninitialize();
	if (pMasteringVoice)
	{
		pMasteringVoice->DestroyVoice();
	}
	pXAudio->Release();
}

