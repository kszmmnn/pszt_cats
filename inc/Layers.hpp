#ifndef LAYERS_HPP_
#define LAYERS_HPP_

#include "Layer.hpp"

#include <vector>

class Layers
{
public:
    Layers(std::vector<unsigned> &dimensions);
    virtual ~Layers();

    void ActivateAndDeriveAll(double bwt, double hwt);
    void Propagate(std::vector<double> &target);
    double Cost(std::vector<double> &target);

private:
    std::vector<Layer> layers;
};

//https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
//https://www.youtube.com/watch?v=tIeHLnjs5U8
#endif /* LAYERS_HPP_ */
