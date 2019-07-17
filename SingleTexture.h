#pragma once
#include "Texture.h"

class SingleTexture :
	public Texture
{
	virtual void Add(const std::string& path, int count = 0) override;
	virtual Texture* Get(int count = -1) override;
	virtual unsigned int Size() override;
};

