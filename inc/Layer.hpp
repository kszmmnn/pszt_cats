#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "Neuron.hpp"

class Layer
{
public:
    Layer(unsigned _neuronsCount, unsigned _inputCount,
          std::vector<std::vector<double>> &_weights);
    Layer(unsigned _neuronsCount, unsigned _inputCount);
    ~Layer();

    std::vector<Neuron>& GetNeurons();
    std::vector<double> GetOutputValues() const;
    std::vector<double> GetDerivedValues() const;
    
    void Activate(std::vector<double> &inputs);
    void Derive();
    
    void CalculateOutputLayerError(const std::vector<double> &targets);
    void CalculateHiddenLayerError(const Layer &nextLayer);
    void UpdateWeights(Layer &prevLayer, const double& learningRate);

private:
    std::vector<Neuron> neurons;
    
    unsigned neuronsCount { 0 };
    unsigned inputCount{ 0 };
};

#endif /* LAYER_HPP_ */
