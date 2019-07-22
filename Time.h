#pragma once


static class Time
{
private:
	static float timeScale;
public:
	static inline float Now() { return DXUTGetTime(); }
	static inline float ElapsedTime() { return DXUTGetElapsedTime(); }
	static inline float DeltaTime() { return ElapsedTime() * timeScale; }

	static inline void	SetTimeScale(float s) { timeScale = s; }
	static inline float GetTimeScale() { return timeScale; }
};

