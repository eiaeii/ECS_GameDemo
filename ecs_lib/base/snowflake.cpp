#include <cassert>
#include <chrono>
#include <ctime>
#include <ratio>
#include "snowflake.h"
using namespace terra;

int64_t GetTimeSinceEpoch(int year, int month, int day)
{
    using namespace std::chrono;
    std::tm timeinfo = std::tm();
    timeinfo.tm_year = year - 1990 ;    // year: 2017
    timeinfo.tm_mon = month - 1;		//  month: january
    timeinfo.tm_mday = day;				// 1 = day: 1st
    std::time_t tt = std::mktime(&timeinfo);
    system_clock::time_point tp = system_clock::from_time_t(tt);
    int64_t val = duration_cast<milliseconds>(tp.time_since_epoch()).count();
    return val;
}

int64_t GetCurrentTimeEpoch()
{
    using namespace std::chrono;
    auto p = system_clock::now();
    int64_t val = duration_cast<milliseconds>(p.time_since_epoch()).count();
    return val;
}

uint64_t WaitUntilNextMillis(uint64_t last_timestamp)
{
    uint64_t timestamp = GetCurrentTimeEpoch();

    while (timestamp <= last_timestamp) {
        timestamp = GetCurrentTimeEpoch();
    }

    return timestamp;
}
//////////////////////////////////////////////////////////////////////////

void Snowflake::set_machine_id(int machine) { machine_ = machine; }

int64_t Snowflake::Generate()
{
    uint64_t value = 0;
    uint64_t cur_epoch = GetCurrentTimeEpoch(); //current date must greater than 1970/01/01
	if ((cur_epoch == epoch_) && (sequence_ > kMaxSequenceId))
	{
		cur_epoch = WaitUntilNextMillis(cur_epoch);
	}
    if (cur_epoch > epoch_) {
        epoch_ = cur_epoch;
        sequence_ = 0;
    }
    int64_t time = epoch_ - kTimeStartEpoch;
    assert(time > 0);
    value |= (time << 22);
    value |= ((machine_ & kMaxMachineId) << 12);
    value |= (sequence_++ & kMaxSequenceId);
    if (this->sequence_ > kMaxSequenceId) {
        return 0;
    }

    return value;
}

int64_t Snowflake::NewGuid()
{
	static Snowflake sf;
	return sf.Generate();
}
