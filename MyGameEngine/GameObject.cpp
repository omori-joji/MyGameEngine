#include "Engine\GameObject.h"
#include "Engine/Common.h"
#include <Windows.h>
#include <time.h>
#include "time.h"
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")

GameObject::GameObject()
{

}

//初期化
GameObject::GameObject(GameObject* parent, const std::string& name) :
	pParent_(parent),		//親情報
	objectName_(name),		//名前
	isDead_(false),			//オブジェクトを消すフラグ
	pCollider_(nullptr)		//当たり判定。当たったら何かが入る
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}

void GameObject::Release()
{
}

void GameObject::DrawSub()
{
	//自分のDrawを呼ぶ
	Draw();

	//すべての子供のDrawSubを呼ぶ
	for (auto i = childList_.begin(); i != childList_.end(); i++)
	{
		(*i)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	//自分のUpdateを呼ぶ
	Update();

	transform_.Calclation();

	//すべての子供のUpdateSubを呼ぶ
	for (auto i = childList_.begin(); i != childList_.end(); i++)
	{
		(*i)->UpdateSub();
	}

	//他の全員と当たってるか調べる
	//当たったらpCollider_に何かが入るから
	if (pCollider_ != nullptr)
	{
		Collision(GetRootJob());
	}

	//すべての子供を探して消えるフラグが立ったらそいつのリリースを呼んで消す
	for (auto i = childList_.begin(); i != childList_.end(); )
	{
		if ((*i)->isDead_ == true)
		{
			(*i)->ReleaseSub();
			SAFE_DELETE(*i);
			i = childList_.erase(i);
		}
		//フラグが立っていなければ次の子供を探す
		else
		{
			i++;
		}
	}

}

//自分と子供のReleseを呼ぶ関数
void GameObject::ReleaseSub()
{
	//自分のReleaseを呼ぶ
	Release();

	//すべての子供のReleaseSubを呼ぶ
	for (auto i = childList_.begin(); i != childList_.end(); i++)
	{
		(*i)->ReleaseSub();
		SAFE_DELETE(*i);
	}
}

void GameObject::killMe()
{
	isDead_ = true;
}

void GameObject::KillAllChildren()
{
	//子供がいないなら終わり
	if (childList_.empty())
		return;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトを1個ずつ削除
	while (it != end)
	{
		KillObjectSub(*it);
		delete* it;
		it = childList_.erase(it);
	}

	//リストをクリア
	childList_.clear();
}

void GameObject::KillObjectSub(GameObject* obj)
{
	if (!childList_.empty())
	{
		auto list = obj->GetChildList();
		auto it = list->begin();
		auto end = list->end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete* it;
			it = list->erase(it);
		}
		list->clear();
	}
	obj->Release();
}

std::list<GameObject*>* GameObject::GetChildList()
{
	return &childList_;
}

void GameObject::AddCollider(Collider* collider)
{
	pCollider_ = collider;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}

	return pParent_->GetRootJob();
}

//当たり判定
void GameObject::Collision(GameObject* target)
{
	if (target->pCollider_ != nullptr && target != this)
	{
		//transform_.position_がXMVECTORなのでXMLoadFloat3に変えてあげる
		XMVECTOR myPos = XMLoadFloat3(&transform_.position_);
		XMVECTOR targetPos = XMLoadFloat3(&target->transform_.position_);

		XMVECTOR d = myPos - targetPos;

		float length = XMVectorGetX(XMVector3Length(d));

		float radius = pCollider_->GetRadius() + target->pCollider_->GetRadius();

		if (length <= radius * radius)
		{
			OnCollisionEnter(target);
		}
	}

	for (auto i = target->childList_.begin(); i != target->childList_.end(); i++)
	{
		Collision(*i);
		SAFE_DELETE(*i);
	}
}

//自分の子孫を探す
GameObject* GameObject::FindSub(std::string objectName)
{
	//探しているのがそいつだったら
	if (objectName == this->objectName_)
	{
		return this;
	}
	else
	{
		for (auto i = childList_.begin(); i != childList_.end(); i++)
		{
			GameObject* go = (*i)->FindSub(objectName);//探してるやつだったらその名前が入る。そうじゃなかったらnullが入る
			if (go != nullptr) //探してるやつだったらそいつを返す
			{
				return go;
			}
		}
	}
	return nullptr;
}

//いちいちGetRootJobから探すのは面倒なのでここで呼んであげてあとはFindを探すだけでいい
GameObject* GameObject::Find(std::string objectName)
{
	return GetRootJob()->FindSub(objectName);
}
