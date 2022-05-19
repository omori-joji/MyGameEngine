#pragma once
#include "Transform.h"
#include "Collider.h"
#include <list>
#include <string>
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

using namespace std;

class GameObject
{
protected:
	std::list<GameObject*> childList_; //�q���X�g
	GameObject*	 pParent_; //�e�I�u�W�F�N�g
	string	     objectName_; //�I�u�W�F�N�g�̖��O
	bool         isDead_;
	Collider*    pCollider_;


public:
	Transform	 transform_; //�ʒu�A�p�x�A�g��


private:
	GameObject* FindSub(std::string objectName);


public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	//�q�I�u�W�F�N�g�������Ƃ��Ɏq�̃f�X�g���N�^�Ă΂ꂸ
	//�e�̃f�X�g���N�^���Ă΂��d�l�Ȃ̂�
	//�q�I�u�W�F�N�g�������Ƃ��͐e�I�u�W�F�N�g�̃f�X�g���N�^��
	//virtual�����Ă�����
	virtual ~GameObject();

	virtual void Initialize() =0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	void killMe();

	void KillAllChildren();

	void KillObjectSub(GameObject* obj);

	std::list<GameObject*>* GetChildList();

	void AddCollider(Collider* collider);

	GameObject* GetRootJob();

	void Collision(GameObject* target);

	virtual void OnCollisionEnter(GameObject* target) {};

	
	GameObject* Find(std::string objectName);

	template<class T>

	GameObject* Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		childList_.push_front(p);
		return p;
	}
};