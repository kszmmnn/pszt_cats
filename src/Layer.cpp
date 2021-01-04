#include "Layer.hpp"
#include "Utils.hpp"

#include <cassert>

Layer::Layer(unsigned _neuronsCount, unsigned _inputCount,
             std::vector<std::vector<double>> &_weights) :
        neuronsCount(_neuronsCount), inputCount(_inputCount)
{
    auto ranum = RandomNumber::GetInstance();
    for (unsigned i = 0; i < neuronsCount; ++i)
    {
        assert(inputCount == _weights[i].size() && "Layer constructor");
        neurons.push_back(Neuron(_weights[i], ranum->RandomDouble()));
    }
}

Layer::Layer(unsigned _neuronsCount, unsigned _inputCount) :
        neuronsCount(_neuronsCount), inputCount(_inputCount)
{
    auto ranum = RandomNumber::GetInstance();
    for (unsigned i = 0; i < neuronsCount; ++i)
    {
        std::vector<double> weights;
        for (unsigned j = 0; j < inputCount; ++j)
        {
            weights.push_back(ranum->RandomDouble());
        }
        neurons.push_back(Neuron(weights, ranum->RandomDouble()));
    }
}

Layer::~Layer()
{
}

void Layer::SetGradients(std::vector<double>&gradients)
{
    assert(gradients.size() == neurons.size() && "set gradients");
    for (unsigned i = 0; i < neurons.size(); ++i)
    {
        neurons[i].SetGradient(gradients[i]);
    }
}

std::vector<double> Layer::GetActivatedValues() const
{
    std::vector<double> ret;
    for (const auto &neuron : neurons)
    {
        ret.push_back(neuron.GetActivatedValue());
    }
    return ret;
}

std::vector<double> Layer::GetDerivedValues() const
{
    std::vector<double> ret;
    for (const auto &neuron : neurons)
    {
        ret.push_back(neuron.GetDerivedValue());
    }
    return ret;
}

std::vector<Neuron> Layer::GetNeurons() const
{
    return neurons;
}

void Layer::ActivateLayer(std::vector<double> &inputs)
{
    assert(inputs.size() == inputCount && "ActivateLayer");

    for (unsigned i = 0; i < neuronsCount; ++i)
    {
        double sum { 0.0 };
        for (unsigned j = 0; j < neuronsCount; ++j)
        {
            sum += inputs[j] * neurons[i].GetWeights()[j];
        }
        sum += neurons[i].GetBias();
        neurons[i].Activate(sum);
    }
}

void Layer::DeriveLayer()
{
    for(auto& neuron : neurons)
    {
        neuron.Derive(neuron.GetValue());
    }
}
