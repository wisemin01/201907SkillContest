#include "DXUT.h"
#include "Timer.h"

std::list<Timer*> Timer::timerContainer;

void Timer::Update(float elapsedTime)
{
	if (isEnd == true)
		return;

	if (isPause == false)
		anyTime -= Time::DeltaTime();

	if (anyTime <= 0)
	{
		isEnd = true;
		anyTime = 0;
	}
}

Timer::Timer(float delay)
{
	anyTime = delay;
}

void Timer::Reset(float delay)
{
	isEnd = false;
	isPause = false;

	anyTime = delay;
}

void Timer::Pause(bool flag)
{
	isPause = flag;
}

void Timer::TimerUpdate(float elapsedTime)
{
	for each (auto iter in timerContainer)
	{
		iter->Update(elapsedTime);
	}
}

Timer* Timer::Create(float delay)
{
	Timer* timer = new Timer(delay);
	timerContainer.push_back(timer);
	return timer;
}

void Timer::PauseAll(bool flag)
{
	for each (auto iter in timerContainer)
	{
		iter->Pause(flag);
	}
}

void Timer::RemoveTimer(Timer* timer)
{
	if (timer == nullptr)
		return;

	timerContainer.remove(timer);
	SAFE_DELETE(timer);
}

void Timer::RemoveAll()
{
	for each (auto iter in timerContainer)
	{
		SAFE_DELETE(iter);
	}

	timerContainer.clear();
}
