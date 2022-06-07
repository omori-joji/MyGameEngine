#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <list>
#include "VisualEffect.h"
#include "Transform.h"
#include "Collider.h"
#include "Common.h"
#include "Input.h"
#include "Audio.h"
#include "Model.h"
#include "time.h"
#include "Fbx.h"
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

using namespace std;

class GameObject
{
protected:
	std::list<GameObject*> childList_;	//�q���X�g
	GameObject*	 pParent_;				//�e�I�u�W�F�N�g
	Collider*    pCollider_;			//�����蔻��
	string	     objectName_;			//�I�u�W�F�N�g�̖��O
	bool         isDead_;				//�������������ĂȂ���
public:
	Transform	 transform_;			//�ʒu�A�p�x�A�g��
private:
	GameObject* FindSub(std::string objectName);				//�I�u�W�F�N�g��T���֐�
public:
	GameObject();												//�R���X�g���N�^
	GameObject(GameObject* parent, const std::string& name);	//�R���X�g���N�^
	//�q�I�u�W�F�N�g�������Ƃ��Ɏq�̃f�X�g���N�^�Ă΂ꂸ
	//�e�̃f�X�g���N�^���Ă΂��d�l�Ȃ̂�
	//�q�I�u�W�F�N�g�������Ƃ��͐e�I�u�W�F�N�g�̃f�X�g���N�^��
	//virtual�����Ă�����
	//���z�֐�
	virtual ~GameObject();										//�f�X�g���N�^
	virtual void Initialize() =0;								//������
	virtual void Update() = 0;									//�X�V
	virtual void Draw() = 0;									//�`��
	virtual void Release() = 0;									//���
	void DrawSub();												//�`��̃T�u
	void UpdateSub();											//�X�V�̃T�u
	void ReleaseSub();											//����̃T�u
	void killMe();												//�I�u�W�F�N�g�������֐�
	void KillAllChildren();										//�q�I�u�W�F�N�g�����ׂď����֐�
	void KillObjectSub(GameObject* obj);						//�I�u�W�F�N�g�������֐��̃T�u
	std::list<GameObject*>* GetChildList();						//�q��T���֐�
	void AddCollider(Collider* collider);						//�����蔻��
	GameObject* GetRootJob();									//�e��T���֐�
	void Collision(GameObject* target);							//�����蔻��
	virtual void OnCollisionEnter(GameObject* target) {};		//�����蔻��
	GameObject* Find(std::string objectName);					//�N���X��T���֐�

	template<class T>

	//�I�u�W�F�N�g�𐶐�����֐�
	GameObject* Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		childList_.push_front(p);
		return p;
	}
};