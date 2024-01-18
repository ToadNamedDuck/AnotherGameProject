#include <Windows.h>
class DeltaTime {
private:
	float delta_time = (float)1/60;
	LARGE_INTEGER frame_begin;
	float performance_frequency;

public:
	//This should only be used once in the program, since it is the initial frame time, that all other calculations rely on.
	void SetFrameBegin()
	{
		QueryPerformanceCounter(&frame_begin);
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)(perf.QuadPart);
	}
	void ChangeDeltaTime()
	{
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin.QuadPart) / performance_frequency;
		frame_begin = frame_end_time;
	}
	float GetDeltaTime() {
		return delta_time;
	}
};