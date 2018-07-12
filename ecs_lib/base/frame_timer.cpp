#include "frame_timer.h"

using namespace terra;

FrameTimer::FrameTimer()
{
#ifdef _WIN32
	LARGE_INTEGER perf_freq;
	QueryPerformanceFrequency(&perf_freq);
	perf_count_duration_ = 1.0 / perf_freq.QuadPart;

	QueryPerformanceCounter(&start_time_);

	frame_start_time_ = GetTime();
#else
	start_time_ = high_resolution_clock::now();
#endif
}

void FrameTimer::Tick()
{
	double current_time = GetTime();
	frame_interval_ = (float)(current_time - frame_start_time_);
	frame_start_time_ = current_time;
}

double FrameTimer::GetTime() const
{
#ifdef _WIN32
	LARGE_INTEGER cur_time, time_since_start;
	QueryPerformanceCounter(&cur_time);

	time_since_start.QuadPart = cur_time.QuadPart - start_time_.QuadPart;

	return time_since_start.QuadPart * perf_count_duration_;
#else
	auto now = high_resolution_clock::now();
	auto ms = duration_cast<milliseconds>(now - start_time_).count();
	//a little uncool to then convert into a double just to go back, but oh well.
	return static_cast<double>(ms) / 1000;
#endif
}