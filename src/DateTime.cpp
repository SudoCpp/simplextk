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

namespace simplex
{
	int32_t DateTime::LocalSecond()
	{
		return DateTime::getLocal().tm_sec;
	}

	int32_t DateTime::LocalMinute()
	{
		return DateTime::getLocal().tm_min;
	}

	int32_t DateTime::Local24Hour()
	{
		return DateTime::getLocal().tm_hour;
	}

	int32_t DateTime::Local12Hour()
	{
		int32_t hour = DateTime::getLocal().tm_hour % 12;
		return (hour == 0) ? 12 : hour;
	}

	int32_t DateTime::LocalAmPm()
	{
		return DateTime::getLocal().tm_hour / 12;
	}

	int32_t DateTime::LocalDay()
	{
		return DateTime::getLocal().tm_mday;
	}

	int32_t DateTime::LocalMonth()
	{
		return DateTime::getLocal().tm_mon + 1;
	}

	int32_t DateTime::LocalYYYY()
	{
		return DateTime::getLocal().tm_year + 1900;
	}

	int32_t DateTime::LocalYY()
	{
		return (DateTime::getLocal().tm_year + 1900) % 100;
	}

	int32_t DateTime::CurrentCentury()
	{
		return (DateTime::getLocal().tm_year + 1900) / 100 + 1;
	}

	bool DateTime::IsDST()
	{
		return (bool)DateTime::getLocal().tm_isdst;
	}

	int32_t DateTime::UtcSecond()
	{
		return DateTime::getUtc().tm_sec;
	}

	int32_t DateTime::UtcMinute()
	{
		return DateTime::getUtc().tm_min;
	}

	int32_t DateTime::Utc24Hour()
	{
		return DateTime::getUtc().tm_hour;
	}

	int32_t DateTime::Utc12Hour()
	{
		int32_t hour = DateTime::getUtc().tm_hour % 12;
		return (hour == 0) ? 12 : hour;
	}

	int32_t DateTime::UtcAmPm()
	{
		return DateTime::getUtc().tm_hour / 12;
	}

	int32_t DateTime::UtcDay()
	{
		return DateTime::getUtc().tm_mday;
	}

	int32_t DateTime::UtcMonth()
	{
		return DateTime::getUtc().tm_mon + 1;
	}

	int32_t DateTime::UtcYYYY()
	{
		return DateTime::getUtc().tm_year + 1900;
	}

	int32_t DateTime::UtcYY()
	{
		return (DateTime::getUtc().tm_year + 1900) % 100;
	}

	tm DateTime::getLocal()
	{
		time_t t = time(0);
		struct tm timeinfo;
		//localtime_s(&timeinfo, &t);
		return timeinfo;
	}

	tm DateTime::getUtc()
	{
		time_t t = time(0);
		struct tm timeinfo;
		//gmtime_s(&timeinfo, &t);
		return timeinfo;
	}
}