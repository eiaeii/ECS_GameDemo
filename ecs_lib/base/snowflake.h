#pragma once

#include <cstdint>

namespace terra
{
	class Snowflake
	{
	public:
		Snowflake() = default;
		~Snowflake() = default;
		void set_machine_id(int machine);
		int64_t Generate();
		static int64_t NewGuid();
	private:
		static const int64_t kTimeStartEpoch = 1483200000000; // 2017/01/01
		static const int kMaxMachineId = 0x3FF;
		static const int kMaxSequenceId = 0xFFF;
		uint64_t epoch_{ 0 };
		uint64_t time_{ 0 };
		int machine_{ 0 };
		int sequence_{ 0 };
	};
}