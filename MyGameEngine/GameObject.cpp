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
	//������DrawSub���Ă�
	Draw();

	//���ׂĂ̎q����DrawSub���Ă�
	for (auto i = childList_.begin(); i != childList_.end(); i++)
	{
		(*i)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	//������Update���Ă�
	Update();

	transform_.Calclation();

	//���ׂĂ̎q����UpdateSub���Ă�
	for (auto i = childList_.begin(); i != childList_.end(); i++)
	{
		(*i)->UpdateSub();
	}

	//���̑S���Ɠ������Ă邩���ׂ�
	//����������pCollider_�ɉ��������邩��
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
	//������Release���Ă�
	Release();

	//���ׂĂ̎q����ReleaseSub���Ă�
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
		//transform_.position_��XMVECTOR�Ȃ̂�XMLoadFloat3�ɕς��Ă�����
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

//�����̎q����T��
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
			GameObject* go = (*i)->FindSub(objectName);//�T���Ă��������炻�̖��O������B��������Ȃ�������null������
			if (go != nullptr) //�T���Ă��������炻����Ԃ�
			{
				return go;
			}
		}
	}
	return nullptr;
}

//��������GetRootJob����T���`�Ƃ����͖̂ʓ|�Ȃ̂ł����ŌĂ�ł����Ă��Ƃ�Find��T�������ł���
GameObject* GameObject::Find(std::string objectName)
{
	return GetRootJob()->FindSub(objectName);
}
