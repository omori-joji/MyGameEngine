#include "Rootjob.h"
#include "SceneManager.h"
#include "../PlayScene.h"

Rootjob::Rootjob()
{
}

Rootjob::~Rootjob()
{
}

void Rootjob::Initialize()
{
	Instantiate<SceneManager>(this);
}

void Rootjob::Update()
{
}

void Rootjob::Draw()
{
}

void Rootjob::Release()
{
}
