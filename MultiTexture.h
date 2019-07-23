#pragma once
#include "Texture.h"

class MultiTexture :
	public Texture
{
private:
	std::vector<Texture*> texVec;
public:
	MultiTexture() {}
	~MultiTexture();

	virtual void Add(const std::string& path, int count = 0) override;
	virtual Texture* Get(int count = -1) override;
	virtual unsigned int Size() override;
};

