#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "TestScene.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayerScene")
{
}

void PlayScene::Initialize()
{	
	Instantiate<TestScene>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
