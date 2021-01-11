#ifndef LAYERS_HPP_
#define LAYERS_HPP_

#include "Layer.hpp"

#include <vector>

class Layers
{
public:
    Layers(int numOfInputs, std::vector<unsigned> hiddenLayer, int numOfOutputs);
    virtual ~Layers();

    void Activate(const double &bwt, const double &hwt);
    void Derive();
    void Propagate(std::vector<double> &target);
    bool IsOutputFemale();

    double Cost(std::vector<double> &target);
  
private:
    std::vector<Layer> layers;

    Layer& getLastHiddenLayer();
    void initHiddenLayers(int numOfInputs, std::vector<unsigned>& hiddenLayers);
    void initHiddenLayer(int numOfNeutrons, int previousLayerOutputs);
    void initOutputLayer(int numOfOutputs, int lastLayerOutputs);
};

//https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
//https://www.youtube.com/watch?v=tIeHLnjs5U8
#endif /* LAYERS_HPP_ */
