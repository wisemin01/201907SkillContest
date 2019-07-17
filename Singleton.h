#pragma once


template <typename _Ty>
class Singleton
{
public:

	static _Ty& GetInstance()
	{
		static _Ty pInst;
		return pInst;
	}
};

