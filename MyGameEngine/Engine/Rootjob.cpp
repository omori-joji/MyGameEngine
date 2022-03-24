#include "Rootjob.h"
#include "../PlayScene.h"

Rootjob::Rootjob()
{
}

Rootjob::~Rootjob()
{
}

void Rootjob::Initialize()
{
	Instantiate<PlayScene>(this);
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
