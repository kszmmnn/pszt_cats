#include "Layer.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cassert>

Layer::Layer(unsigned _neuronsCount, unsigned _inputCount, std::vector<std::vector<double>> &_weights) :
        neuronsCount(_neuronsCount), inputCount(_inputCount)
{
    auto ranum = RandomNumber::GetInstance();

    for (unsigned i = 0; i < neuronsCount; ++i)
    {
        assert(inputCount == _weights[i].size());

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
    assert(gradients.size() == neurons.size());

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

void Layer::Activate(std::vector<double> &inputs)
{
    assert(inputs.size() == inputCount);
    double sum;

    for (unsigned i = 0; i < neuronsCount; ++i)
    {
        sum = 0.0;

        for (unsigned j = 0; j < inputCount; ++j)
        {
            sum += inputs[j] * neurons[i].getWeight(j);
        }

        sum += neurons[i].GetBias();
        
        neurons[i].Active(sum);
    }
}

void Layer::CalculateOutputLayerGradient(const std::vector<double> &targets)
{
    double dCost;
    double dSigmoid;
    double error;

    for (unsigned i = 0; i < targets.size(); ++i)
    {
        dCost = 2 * (targets[i] - neurons[i].GetActivatedValue());
        dSigmoid = neurons[i].GetDerivedValue();
        error = dCost * dSigmoid;

        neurons[i].SetError(error);
    }
}

void Layer::CalculateHiddenLayerGradient(const Layer &nextLayer)
{
    double dSigmoid;
    double errorSum;
    double error;

    for (unsigned i = 0; i < neurons.size(); ++i)
    {
        dSigmoid = neurons[i].GetDerivedValue();
        errorSum = 0.0;

        for (unsigned j = 0; j < nextLayer.neurons.size(); ++j)
        {
            auto &neuron = nextLayer.neurons[j];
            errorSum += neuron.GetError() * neuron.getWeight(j);
        }

        error = dSigmoid * errorSum;
        neurons[i].SetError(error);
    }
}

void Layer::Derive()
{
    for (auto &neuron : neurons)
    {
        neuron.Derive();
    }
}

void Layer::UpdateWeights(Layer &prevLayer)
{
    double dWeight;

    for (unsigned i = 0; i < neurons.size(); ++i)
    {
        for (unsigned j = 0; j < neurons[i].GetWeights().size(); ++j)
        {
            Neuron &neuron = prevLayer.neurons[j];
            dWeight = /*learningrate*/0.1 * neurons[i].GetError()
                                             * neuron.GetActivatedValue();

            
            neurons[i].SetWeight(j, dWeight + neurons[i].getWeight(j));
        }

        neurons[i].SetBias(
                neurons[i].GetBias() + /*learningrate*/0.1
                        * neurons[i].GetError()); //mozebyczle
    }
}
