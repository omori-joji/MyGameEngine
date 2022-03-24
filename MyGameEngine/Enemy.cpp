#include "Enemy.h"
#include "Engine/Common.h"
#include "Engine/Model.h"
#include "Engine/Collider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Bullet"), hModel_(-1)
{
	transform_.position_.z = 10.0f;
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Assets/BlueBlock.fbx");

	Collider* pCollider = new Collider(0.5f);
	AddCollider(pCollider);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollisionEnter(GameObject* target)
{
	killMe();
}
