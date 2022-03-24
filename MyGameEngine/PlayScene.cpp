#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayerScene")
{
}

void PlayScene::Initialize()
{	
	Instantiate<Stage>(this);
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
