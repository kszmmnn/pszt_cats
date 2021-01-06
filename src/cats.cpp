#include "Layers.hpp"
#include "Utils.hpp"

#include <cstdio>
#include <cstdlib>
int main()
{
    RandomNumber randNum();

    std::vector<unsigned> dimensions = { 2, 3, 2 };
    Layers l(dimensions);
    l.ActivateAndDeriveAll(2.5, 12.7);
    std::vector<double> out = { 0, 1 };
    l.Propagate(out);
    printf("%f  ", l.Cost(out));

    out = { 1, 0 };
    l.ActivateAndDeriveAll(2.1, 8.1);
    printf("%f  ", l.Cost(out));
    l.Propagate(out);

    l.ActivateAndDeriveAll(2.1, 8.1);
    printf("%f  ", l.Cost(out));
    l.Propagate(out);
    l.ActivateAndDeriveAll(2.1, 8.1);
    printf("%f  ", l.Cost(out));
    l.Propagate(out);
    l.ActivateAndDeriveAll(2.1, 8.1);
    printf("%f  ", l.Cost(out));
    l.Propagate(out);
    l.ActivateAndDeriveAll(2.1, 8.1);
    printf("%f  ", l.Cost(out));
    l.Propagate(out);
    l.ActivateAndDeriveAll(2.1, 8.1);
    printf("%f  ", l.Cost(out));
    l.Propagate(out);

    return 0;
}

//w jednym miejscu error, w drugim gradient - zdecydowac sie
