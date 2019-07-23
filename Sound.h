#pragma once
#include "BaseResource.h"
#include "SDKsound.h"

class Sound :
	public BaseResource
{
private:
	CSound* sound = nullptr;

public:
	void Play();
	void Duplicate();

	// STATIC FIELD
public:

private:
	static CSoundManager* soundSource;
};

