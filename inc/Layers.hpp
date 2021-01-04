#ifndef LAYERS_HPP_
#define LAYERS_HPP_

#include "Layer.hpp"

#include <vector>

class Layers
{
public:
    Layers(std::vector<unsigned>& dimensions);
    virtual ~Layers();

    void ActivateAndDeriveAll(double bwt, double hwt);
    void Propagate(double target);
    void CalculateHiddenLayerGradient();
    void CalculateOutputLayerGradient();


private:
    std::vector<Layer> layers;

    double previousError {0.0};
    double previousSmoothingFactor {100.0};
};

#endif /* LAYERS_HPP_ */
