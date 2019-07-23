#pragma once

class Component;
class Renderer;
class Transform;

class GameObject
{
	friend class ObjectManager;
private:
	int layer;

	bool isDisplay;
	bool isActive;
	bool isDie;

	std::map<int, Component*> componentContainer;

public:
	Renderer* renderer = nullptr;
	Transform* transform = nullptr;

private:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	void ComUpdate();
	void ComDestroy();

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

