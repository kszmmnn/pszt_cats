#include "Layers.hpp"
#include "Utils.hpp"

#include <cstdio>
#include <cstdlib>
int main()
{
    RandomNumber randNum();

    std::vector<unsigned> dimensions = {2,3,2};
    Layers l(dimensions);
    l.ActivateAndDeriveAll(12, 13);
    l.Propagate(1);
    return 0;
}
