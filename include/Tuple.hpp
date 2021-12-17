#ifndef SIMPLEX_TUPLE_HPP
#define SIMPLEX_TUPLE_HPP

#include <tuple>

namespace simplex
{
    template<typename ...Args>
    class Tuple
    {
        std::tuple<Args...> data;
        public:
        Tuple(Args ...args) : data{ std::make_tuple(args...) } {}
        
        template<int index>
        auto at() 
        { 
            return std::get<index>(data);
        }

        void getAll(Args&... args)
        {
            std::tie(args...) = data;
        }

    };
}

#endif //SIMPLEX_TUPLE_HPP