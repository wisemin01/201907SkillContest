#include "DXUT.h"
#include "MultiTexture.h"

#include "SingleTexture.h"

MultiTexture::~MultiTexture()
{
	for each (auto iter in texVec)
	{
		SAFE_DELETE(iter);
	}
	texVec.clear();
}

void MultiTexture::Add(const std::string& path, int count)
{
	char str[256] = { 0 };
	texVec.reserve(count + 1);

	for (int i = 0; i <= count; i++)
	{
		sprintf(str, path.c_str(), i);
	
		Texture* t = new SingleTexture();

		t->Add(str, 0);

		texVec.push_back(t);
	}
}

Texture* MultiTexture::Get(int count)
{
	if (count == -1)
		return this;
	else
	{
		try {
			return texVec[count];
		}
		catch(object)
		{
			return nullptr;
		}
	}
}

unsigned int MultiTexture::Size()
{
	return texVec.size();
}
