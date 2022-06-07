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
	std::list<GameObject*> childList_;	//子リスト
	GameObject*	 pParent_;				//親オブジェクト
	Collider*    pCollider_;			//当たり判定
	string	     objectName_;			//オブジェクトの名前
	bool         isDead_;				//消えたか消えてないか
public:
	Transform	 transform_;			//位置、角度、拡大
private:
	GameObject* FindSub(std::string objectName);				//オブジェクトを探す関数
public:
	GameObject();												//コンストラクタ
	GameObject(GameObject* parent, const std::string& name);	//コンストラクタ
	//子オブジェクトを消すときに子のデストラクタ呼ばれず
	//親のデストラクタが呼ばれる仕様なので
	//子オブジェクトを消すときは親オブジェクトのデストラクタに
	//virtualをつけてあげる
	//仮想関数
	virtual ~GameObject();										//デストラクタ
	virtual void Initialize() =0;								//初期化
	virtual void Update() = 0;									//更新
	virtual void Draw() = 0;									//描画
	virtual void Release() = 0;									//解放
	void DrawSub();												//描画のサブ
	void UpdateSub();											//更新のサブ
	void ReleaseSub();											//解放のサブ
	void killMe();												//オブジェクトを消す関数
	void KillAllChildren();										//子オブジェクトをすべて消す関数
	void KillObjectSub(GameObject* obj);						//オブジェクトを消す関数のサブ
	std::list<GameObject*>* GetChildList();						//子を探す関数
	void AddCollider(Collider* collider);						//当たり判定
	GameObject* GetRootJob();									//親を探す関数
	void Collision(GameObject* target);							//当たり判定
	virtual void OnCollisionEnter(GameObject* target) {};		//当たり判定
	GameObject* Find(std::string objectName);					//クラスを探す関数

	template<class T>

	//オブジェクトを生成する関数
	GameObject* Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		childList_.push_front(p);
		return p;
	}
};