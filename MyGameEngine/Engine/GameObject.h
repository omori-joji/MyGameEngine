#pragma once
#include "Transform.h"
#include "Collider.h"
#include <list>
#include <string>

using namespace std;

class GameObject
{
protected:
	std::list<GameObject*> childList_; //子リスト
	GameObject*	 pParent_; //親オブジェクト
	string	     objectName_; //オブジェクトの名前
	bool         isDead_;
	Collider*    pCollider_;


public:
	Transform	 transform_; //位置、角度、拡大



private:
	GameObject* FindSub(std::string objectName);


public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	//子オブジェクトを消すときに子のデストラクタ呼ばれず
	//親のデストラクタが呼ばれる仕様なので
	//子オブジェクトを消すときは親オブジェクトのデストラクタに
	//virtualをつけてあげる
	virtual ~GameObject();

	virtual void Initialize() =0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	void killMe();

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
		childList_.push_back(p);
		return p;
	}

	int DeltaTime();
};