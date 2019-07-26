#pragma once

class Component;
class Renderer;
class Transform;
class Rigidbody;
class Collider;

class GameObject
{
	friend class ObjectManager;
private:
	int layer;

	bool isDisplay;
	bool isActive;
	bool isDie;

	std::map<int, Component*> componentContainer;

	string tag;

public:
	Renderer* renderer = nullptr;
	Transform* transform = nullptr;
	Rigidbody* rigidbody = nullptr;
	Collider* collider = nullptr;

private:


	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	void ComUpdate();
	void ComDestroy();

public:
	__declspec(property(get = GetTag, put = SetTag)) string Tag;

	string GetTag() { return tag; }
	void SetTag(const string& t) { tag = t; }

public:
	virtual void OnCollision(Collider* other) {}
	void OnCollisionBase(Collider* other);

public:
	template <typename _Ty>
	_Ty* GetComponent()
	{
		auto find = componentContainer.find(typeid(_Ty).hash_code());

		if (find == componentContainer.end())
			return nullptr;

		return static_cast<_Ty*>(find->second);
	}

	template <typename _Ty>
	_Ty* AddComponent()
	{
		int hash = typeid(_Ty).hash_code();
		auto find = componentContainer.find(hash);

		if (find != componentContainer.end())
			return static_cast<_Ty*>(find->second);

		_Ty* com = new _Ty();
		com->gameObject = this;
		com->Init();

		componentContainer.insert(make_pair(hash, com));
		return com;
	}

	void Kill() { isDie = true; }
	void Kill(GameObject* other) { other->Kill(); }

	void SetRenderBegin(function<void()> begin);
	void SetRenderEnd(function<void()> end);
};

