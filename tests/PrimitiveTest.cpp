#include "Primitive.hpp"

using namespace simplex;

int main(int argc, char* argv[])
{
    std::string convert{argv[1]};
    if(convert == "0")
    {
        Primative<int> first = 5;
        Primative<int> second = 3;
        if(first - second == 2)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
}