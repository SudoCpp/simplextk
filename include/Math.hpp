/*
    BSD 3-Clause License
    
    Copyright (c) 2021, SudoCpp
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

#ifndef SIMPLEX_MATH_HPP
#define SIMPLEX_MATH_HPP

#include <algorithm>
#include <cmath>
#ifdef _LIBCPP_HAS_COMMENT_LIB_PRAGMA
    #pragma comment(lib, "m")
#endif

namespace simplex
{
    namespace Math
    {
        template <typename type> type Abs(type number)
        {
            return std::abs(number);
        }

        template <typename type> type ArcCos(type number)
        {
            return std::acos(number);
        }

        template <typename type> type ArcCosH(type number)
        {
            return std::acosh(number);
        }

        template <typename type> type ArcSin(type number)
        {
            return std::asin(number);
        }

        template <typename type> type ArcSinH(type number)
        {
            return std::asinh(number);
        }

        template <typename type> type ArcTan(type number)
        {
            return std::atan(number);
        }

        template <typename type, typename type2> type ArcTan2(type number1, type2 number2)
        {
            return std::atan2(number1, number2);
        }

        template <typename type> type ArcTanH(type number)
        {
            return std::atanh(number);
        }

        template <typename type> type Cube(type number)
        {
            return std::pow(number, 3);
        }

        template <typename type> type CubeRoot(type number)
        {
            return std::cbrt(number);
        }

        template <typename type> type Ceiling(type number)
        {
            return std::ceil(number);
        }

        template <typename type> type Cos(type number)
        {
            return std::cos(number);
        }

        template <typename type> type CosH(type number)
        {
            return std::cosh(number);
        }

        template <typename type> type Floor(type number)
        {
            return std::floor(number);
        }

        template <typename type> type Log(type number)
        {
            return std::log(number);
        }

        template <typename type> type Log10(type number)
        {
            return std::log10(number);
        }

        template <typename type> type Max(type number1, type number2)
        {
            return std::max(number1, number2);
        }

        template <typename type> type Min(type number1, type number2)
        {
            return std::min(number1, number2);
        }

        template <typename type, typename type2> type Power(type base, type2 exponent)
        {
            return std::pow(base, exponent);
        }

        template <typename type> type Remainder(type number1, type number2)
        {
            return std::remainder(number1, number2);
        }

        template <typename type> type Round(type number)
        {
            return std::round(number);
        }

        template <typename type> type Round(type number, double decimalPlaces)
        {
            return (type)(Math::Round(number * Math::Power(10, decimalPlaces)) / Math::Power(10, decimalPlaces));
        }

        template <typename type> type Sin(type number)
        {
            return std::sin(number);
        }

        template <typename type> type SinH(type number)
        {
            return std::sinh(number);
        }

        template <typename type> type Square(type number)
        {
            return std::pow(number, 2);
        }

        template <typename type> type SquareRoot(type number)
        {
            return std::sqrt(number);
        }

        template <typename type> type Tan(type number)
        {
            return std::tan(number);
        }

        template <typename type> type TanH(type number)
        {
            return std::tanh(number);
        }
    };
}

#endif //SIMPLEX_MATH_HPP