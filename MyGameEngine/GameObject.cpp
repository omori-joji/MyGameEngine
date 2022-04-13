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
	pParent_(parent), objectName_(name),isDead_(false), pCollider_(nullptr)
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
	//Ž©•ª‚ÌDrawSub‚ðŒÄ‚Ô
	Draw();

	//‚·‚×‚Ä‚ÌŽq‹Ÿ‚ÌDrawSub‚ðŒÄ‚Ô
	for (auto i = childList_.begin(); i != childList_.end(); i++)
	{
		(*i)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	//Ž©•ª‚ÌUpdate‚ðŒÄ‚Ô
	Update();

	transform_.Calclation();

	//‚·‚×‚Ä‚ÌŽq‹Ÿ‚ÌUpdateSub‚ðŒÄ‚Ô
	for (auto i = childList_.begin(); i != childList_.end(); i++)
	{
		(*i)->UpdateSub();
	}

	//‘¼‚Ì‘Sˆõ‚Æ“–‚½‚Á‚Ä‚é‚©’²‚×‚é
	//“–‚½‚Á‚½‚çpCollider_‚É‰½‚©‚ª“ü‚é‚©‚ç
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
	//Ž©•ª‚ÌRelease‚ðŒÄ‚Ô
	Release();

	//‚·‚×‚Ä‚ÌŽq‹Ÿ‚ÌReleaseSub‚ðŒÄ‚Ô
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
		//transform_.position_‚ªXMVECTOR‚È‚Ì‚ÅXMLoadFloat3‚É•Ï‚¦‚Ä‚ ‚°‚é
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

//Ž©•ª‚ÌŽq‘·‚ð’T‚·
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
			GameObject* go = (*i)->FindSub(objectName);//’T‚µ‚Ä‚é‚â‚Â‚¾‚Á‚½‚ç‚»‚Ì–¼‘O‚ª“ü‚éB‚»‚¤‚¶‚á‚È‚©‚Á‚½‚çnull‚ª“ü‚é
			if (go != nullptr) //’T‚µ‚Ä‚é‚â‚Â‚¾‚Á‚½‚ç‚»‚¢‚Â‚ð•Ô‚·
			{
				return go;
			}
		}
	}
	return nullptr;
}

//‚¢‚¿‚¢‚¿GetRootJob‚©‚ç’T‚·`‚Æ‚©‚­‚Ì‚Í–Ê“|‚È‚Ì‚Å‚±‚±‚ÅŒÄ‚ñ‚Å‚ ‚°‚Ä‚ ‚Æ‚ÍFind‚ð’T‚·‚¾‚¯‚Å‚¢‚¢
GameObject* GameObject::Find(std::string objectName)
{
	return GetRootJob()->FindSub(objectName);
}
