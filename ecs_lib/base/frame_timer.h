#pragma once

#include "core.h"

namespace terra
{
    class FrameTimer
    {
		MAKE_INSTANCE(FrameTimer)
    private:
#ifdef _WIN32
        LARGE_INTEGER start_time_{0};
#else
        high_resolution_clock::time_point start_time_;
#endif
        float frame_interval_;
        double frame_start_time_;
        double perf_count_duration_;

    public:
        FrameTimer();

        void Tick();
		float GetFrameTimeS() const { return frame_interval_; }
		int GetFrameTimeMs() const { return static_cast<int>(frame_interval_ * 1000); }
        float GetFrameTotalS() const { return static_cast<float>(GetTime()); }
		int64_t GetFrameTotalMs() const { return static_cast<int64_t>(GetTime() * 1000); }
		float GetFrameStartTimeS() const { return static_cast<float>(frame_start_time_); }
		int64_t GetFrameStartTimeMs() const { return static_cast<int64_t>(frame_start_time_) * 1000; }
	private:
		double GetTime() const;
    };
}