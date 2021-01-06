#include "Layers.hpp"
#include "Utils.hpp"

#include <cstdio>
#include <cstdlib>
int main()
{
    RandomNumber randNum();

    std::vector<unsigned> dimensions = {2,3,2};
    Layers l(dimensions);
    l.ActivateAndDeriveAll(2.5,12.7);
    std::vector<double> out = {1,0};
    l.Propagate(out);
    l.ActivateAndDeriveAll(2.5,12.7);
    l.Propagate(out);
    return 0;
}

//w jednym miejscu error, w drugim gradient - zdecydowac sie
