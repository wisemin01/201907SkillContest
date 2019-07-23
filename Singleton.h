#pragma once


template <typename _Ty>
class Singleton
{
private:
	static _Ty* inst;

public:

	static _Ty& GetInstance()
	{
		if (inst == nullptr)
			inst = new _Ty();

		return *inst;
	}

	static void Destroy()
	{
		SAFE_DELETE(inst);
	}
};

template <typename _Ty>
_Ty* Singleton<_Ty>::inst = nullptr;