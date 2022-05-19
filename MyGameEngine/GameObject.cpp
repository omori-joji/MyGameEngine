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

GameObject::GameObject(GameObject* parent, const std::string& name) :
	pParent_(parent), 
	objectName_(name),
	isDead_(false), 
	pCollider_(nullptr)
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
	//自分のDrawSubを呼ぶ
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



	for (auto i = childList_.begin(); i != childList_.end(); )
	{
		if ((*i)->isDead_ == true)
		{
			(*i)->ReleaseSub();
			SAFE_DELETE(*i);
			i = childList_.erase(i);
		}
		else
		{
			i++;
		}
	}

}

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

void GameObject::Collision(GameObject* target)
{
	if (target->pCollider_ != nullptr && target != this)
	{
		//transform_.position_がXMVECTORなのでXMLoadFloat3に変えてあげる
		XMVECTOR myPos = XMLoadFloat3(&transform_.position_);
		XMVECTOR targetPos = XMLoadFloat3(&target->transform_.position_);

		XMVECTOR d = myPos - targetPos;

		float length = XMVectorGetX(XMVector3Length(d));

		//float length = (transform_.position_.x - target->transform_.position_.x)
		//	* (transform_.position_.x - target->transform_.position_.x)
		//	+
		//	(transform_.position_.y - target->transform_.position_.y)
		//	* (transform_.position_.y - target->transform_.position_.y)
		//	+
		//	(transform_.position_.z - target->transform_.position_.z)
		//	* (transform_.position_.z - target->transform_.position_.z);

		float radius = pCollider_->GetRadius() + target->pCollider_->GetRadius();

		if (length <= radius * radius)
		{
			OnCollisionEnter(target);
		}
	}

	for (auto i = target->childList_.begin(); i != target->childList_.end(); i++)
	{
		Collision(*i);
	}

}

//自分の子孫を探す
GameObject* GameObject::FindSub(std::string objectName)
{
	
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

//いちいちGetRootJobから探す〜とかくのは面倒なのでここで呼んであげてあとはFindを探すだけでいい
GameObject* GameObject::Find(std::string objectName)
{
	return GetRootJob()->FindSub(objectName);
}
