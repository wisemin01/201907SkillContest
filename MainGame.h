#pragma once


class MainGame
{
private:

public:
	MainGame() {}
	virtual ~MainGame() {}

	void Init();
	void Update();
	void Render();
	void Destroy();

	void OnReset();
	void OnLost();
};

