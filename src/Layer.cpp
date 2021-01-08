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

void Layer::SetGradients(std::vector<double> &gradients)
{
    assert(gradients.size() == neurons.size() && "set gradients");
    for (unsigned i = 0; i < neurons.size(); ++i)
    {
        neurons[i].SetError(gradients[i]);
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

std::vector<Neuron>& Layer::GetNeurons()
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

void Layer::CalculateOutputLayerGradient(const std::vector<double> &targets)
{
    for (unsigned i = 0; i < targets.size(); ++i)
    {
        double dCost = 2 * (targets[i] - neurons[i].GetActivatedValue());
        double dSigmoid = neurons[i].GetDerivedValue();
        neurons[i].SetError(dSigmoid * dCost);
    }
}

void Layer::CalculateHiddenLayerGradient(const Layer &nextLayer)
{

    for (unsigned i = 0; i < neurons.size(); ++i)
    {
        double dSigmoid = neurons[i].GetDerivedValue();
        double errorSum { 0.0 };
        for (unsigned j = 0; j < nextLayer.neurons.size(); ++j)
        {
            auto &neuron = nextLayer.neurons[j];
            errorSum += neuron.GetError() * neuron.GetWeights()[j];
        }
        neurons[i].SetError(dSigmoid * errorSum);
    }
}

void Layer::DeriveLayer()
{
    for (auto &neuron : neurons)
    {
        neuron.Derive();
    }
}

void Layer::UpdateWeights(Layer &prevLayer)
{
    for (unsigned i = 0; i < neurons.size(); ++i)
    {
        for (unsigned j = 0; j < neurons[i].GetWeights().size(); ++j)
        {
            Neuron &neuron = prevLayer.neurons[j];
            double dWeight = /*learningrate*/0.1 * neurons[i].GetError()
                                             * neuron.GetActivatedValue();

            neurons[i].SetWeight(j, dWeight + neurons[i].GetWeights()[j]);
        }
        neurons[i].SetBias(
                neurons[i].GetBias() + /*learningrate*/0.1
                        * neurons[i].GetError()); //mozebyczle
    }
}
