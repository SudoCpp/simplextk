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

#include <ctime>
#include <cstdint>

namespace simplex
{
	class DateTime
	{
		public:
			static int32_t LocalSecond();
			static int32_t LocalMinute();
			static int32_t Local24Hour();
			static int32_t Local12Hour();
			static int32_t LocalAmPm();
			static int32_t LocalDay();
			static int32_t LocalMonth();
			static int32_t LocalYY();
			static int32_t LocalYYYY();
			static bool IsDST();

			static int32_t UtcSecond();
			static int32_t UtcMinute();
			static int32_t Utc24Hour();
			static int32_t Utc12Hour();
			static int32_t UtcAmPm();
			static int32_t UtcDay();
			static int32_t UtcMonth();
			static int32_t UtcYY();
			static int32_t UtcYYYY();

			static int32_t CurrentCentury();

		private:
			DateTime() {}
			static struct tm getLocal();
			static struct tm getUtc();
	};
}
#endif //SIMPLEX_DATETIME_HPP