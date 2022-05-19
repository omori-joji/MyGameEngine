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

//������
GameObject::GameObject(GameObject* parent, const std::string& name) :
	pParent_(parent),		//�e���
	objectName_(name),		//���O
	isDead_(false),			//�I�u�W�F�N�g�������t���O
	pCollider_(nullptr)		//�����蔻��B���������牽��������
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
	//������Draw���Ă�
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

	//���ׂĂ̎q����T���ď�����t���O���������炻���̃����[�X���Ă�ŏ���
	for (auto i = childList_.begin(); i != childList_.end(); )
	{
		if ((*i)->isDead_ == true)
		{
			(*i)->ReleaseSub();
			SAFE_DELETE(*i);
			i = childList_.erase(i);
		}
		//�t���O�������Ă��Ȃ���Ύ��̎q����T��
		else
		{
			i++;
		}
	}

}

//�����Ǝq����Relese���ĂԊ֐�
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

void GameObject::KillAllChildren()
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g��1���폜
	while (it != end)
	{
		KillObjectSub(*it);
		delete* it;
		it = childList_.erase(it);
	}

	//���X�g���N���A
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

//�����蔻��
//������������̏���Collider�N���X�̊֐��ɓn��
void GameObject::Collision(GameObject* target)
{
	if (target->pCollider_ != nullptr && target != this)
	{
		//transform_.position_��XMVECTOR�Ȃ̂�XMLoadFloat3�ɕς��Ă�����
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

//�����̎q����T��
GameObject* GameObject::FindSub(std::string objectName)
{
	//�T���Ă���̂�������������
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

//��������GetRootJob����T���͖̂ʓ|�Ȃ̂ł����ŌĂ�ł����Ă��Ƃ�Find��T�������ł���
GameObject* GameObject::Find(std::string objectName)
{
	return GetRootJob()->FindSub(objectName);
}
