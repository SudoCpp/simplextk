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

#ifndef SIMPLEX_DATETIME_HPP
#define SIMPLEX_DATETIME_HPP

#include <cstdint>
#include "string.hpp"

namespace simplex
{
	class DateTime
	{
		uint16_t localYday, localYear, utcYday, utcYear;
		uint8_t localSec, localMin, localHour, localMday, localMon, localWday;
		uint8_t utcSec, utcMin, utcHour, utcMday, utcMon, utcWday;
		bool dst;
		long int secOffUTC;
		string timeAbbrv;

		public:
			int32_t localSecond();
			int32_t localMinute();
			int32_t local24Hour();
			int32_t local12Hour();
			int32_t localAmPm();
			int32_t localDay();
			int32_t localMonth();
			int32_t localYY();
			int32_t localYYYY();
			bool isDST();

			uint8_t utcSecond();
			uint8_t utcMinute();
			uint8_t utc24Hour();
			uint8_t utc12Hour();
			uint8_t utcAmPm();
			uint8_t utcDay();
			uint8_t utcMonth();
			uint8_t utcYY();
			uint16_t utcYYYY();

			int32_t currentCentury();

			//uint64_t ticks();

			DateTime();
	};
}
#endif //SIMPLEX_DATETIME_HPP