#include "Neuron.hpp"
#include <cmath>
#include <iostream>

Neuron::Neuron(std::vector<double> &_weights, double _bias) :
        weights(_weights), bias(_bias)
{
}

Neuron::~Neuron()
{
}

void Neuron::Active(double value)
{
    this->value = value;
    outputValue = 1 / (1 + std::exp(-value));
}

void Neuron::Derive()
{
    derivedValue = std::exp(-value) / std::pow(1 + std::exp(-value), 2);
}

double Neuron::GetOutputValue() const
{
    return outputValue;
}

double Neuron::GetDerivedValue() const
{
    return derivedValue;
}

double Neuron::GetValue() const
{
    return value;
}

double Neuron::GetBias() const
{
    return bias;
}

void Neuron::SetWeights(std::vector<double> &_weights)
{
    weights = _weights;
}

void Neuron::SetBias(double _bias)
{
    bias = _bias;
}

std::vector<double> Neuron::GetWeights() const
{
    return weights;
}

double Neuron::getWeight(int index) const
{
    return weights[index];
}

void Neuron::SetError(double _error)
{
    error = _error;
}

double Neuron::GetError() const
{
    return error;
}

void Neuron::SetWeight(unsigned pos, double _weight)
{
    weights[pos] = _weight;
}
