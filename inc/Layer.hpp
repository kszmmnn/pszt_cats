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
    std::vector<double> GetActivatedValues() const;
    std::vector<double> GetDerivedValues() const;
    void SetGradients(std::vector<double> &gradients);

    void Activate(std::vector<double> &inputs);
    void Derive();

    void CalculateOutputLayerGradient(const std::vector<double> &targets);
    void CalculateHiddenLayerGradient(const Layer &nextLayer);
    void UpdateWeights(Layer &prevLayer);

private:
    std::vector<Neuron> neurons;

    unsigned neuronsCount { 0 };
    unsigned inputCount { 0 };
};

#endif /* LAYER_HPP_ */
