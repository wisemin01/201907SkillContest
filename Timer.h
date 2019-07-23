#pragma once

class Timer
{
private:
	float anyTime;

	bool isPause = false;
	bool isEnd = false;

	void Update(float elapsedTime);
public:
	Timer(float delay);

	~Timer() {

	}

	void Reset(float delay);
	void Pause(bool flag);

	bool GetEnd() { return isEnd; }
	bool GetPause() { return isPause; }

	__declspec(property(get = GetEnd)) bool IsEnd;
	__declspec(property(get = GetPause)) bool IsPause;

	// ========================================================
	// STATIC FIELD
	// ========================================================

private:
	static std::list<Timer*> timerContainer;

public:
	static void TimerUpdate(float elapsedTime);

	static Timer* Create(float delay);

	static void PauseAll(bool flag);

	static void RemoveTimer(Timer* timer);

	static void RemoveAll();
};
