/*
    BSD 3-Clause License
    
    Copyright (c) 2022, SudoCpp
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "DateTime.hpp"
#include <ctime>
#include <chrono>

using namespace std::chrono;

namespace simplex
{
	DateTime::DateTime()
	{
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = gmtime(&rawtime);

		localSec = timeinfo->tm_sec;
		localMin = timeinfo->tm_min;
		localHour = timeinfo->tm_hour;
		localMday = timeinfo->tm_mday;
		localMon = timeinfo->tm_mon;
		localYear = timeinfo->tm_year;
		localWday = timeinfo->tm_wday;
		localYday = timeinfo->tm_yday;
		dst = timeinfo->tm_isdst;
		secOffUTC = timeinfo->tm_gmtoff;
		timeAbbrv = string{timeinfo->tm_zone};

		timeinfo = localtime(&rawtime);

		utcSec = timeinfo->tm_sec;
		utcMin = timeinfo->tm_min;
		utcHour = timeinfo->tm_hour;
		utcMday = timeinfo->tm_mday;
		utcMon = timeinfo->tm_mon;
		utcYear = timeinfo->tm_year;
		utcWday = timeinfo->tm_wday;
		utcYday = timeinfo->tm_yday;
	}

	int32_t DateTime::localSecond()
	{
		return localSec;
	}

	int32_t DateTime::localMinute()
	{
		return localMin;
	}

	int32_t DateTime::local24Hour()
	{
		return localHour;
	}

	int32_t DateTime::local12Hour()
	{
		int32_t hour = localHour % 12;
		return (hour == 0) ? 12 : hour;
	}

	int32_t DateTime::localAmPm()
	{
		return localHour / 12;
	}

	int32_t DateTime::localDay()
	{
		return localMday;
	}

	int32_t DateTime::localMonth()
	{
		return localMon + 1;
	}

	int32_t DateTime::localYYYY()
	{
		return localYear + 1900;
	}

	int32_t DateTime::localYY()
	{
		return (localYear + 1900) % 100;
	}

	int32_t DateTime::currentCentury()
	{
		return (localYear + 1900) / 100 + 1;
	}

	bool DateTime::isDST()
	{
		return dst;
	}

	uint8_t DateTime::utcSecond()
	{
		return utcSec;
	}

	uint8_t DateTime::utcMinute()
	{
		return utcMin;
	}

	uint8_t DateTime::utc24Hour()
	{
		return utcHour;
	}

	uint8_t DateTime::utc12Hour()
	{
		int32_t hour = utcHour % 12;
		return (hour == 0) ? 12 : hour;
	}

	uint8_t DateTime::utcAmPm()
	{
		return utcHour / 12;
	}

	uint8_t DateTime::utcDay()
	{
		return utcMday;
	}

	uint8_t DateTime::utcMonth()
	{
		return utcMon + 1;
	}

	uint16_t DateTime::utcYYYY()
	{
		return utcYear + 1900;
	}

	uint8_t DateTime::utcYY()
	{
		return (utcYear + 1900) % 100;
	}

	// uint64_t DateTime::ticks()
	// {
	// 	return clock();
	// }
}