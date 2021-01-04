#include "Neuron.hpp"
#include <cmath>

Neuron::Neuron(std::vector<double> &_weights, double _bias) :
        weights(_weights), bias(_bias)
{
}

Neuron::~Neuron()
{
}

void Neuron::Activate(double value)
{
    this->value = value;
    activatedValue = 1 / (1 + std::exp(-value));
}

void Neuron::Derive(double value)
{
    this->value = value;
    derivedValue = std::exp(-value) / std::pow(1 + std::exp(-value), 2);
}

double Neuron::GetActivatedValue() const
{
    return activatedValue;
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

std::vector<double> Neuron::GetWeights() const
{
    return weights;
}

void Neuron::SetGradient(double _gradient)
{
    gradient = gradient;
}

double Neuron::GetGradient() const
{
    return gradient;
}
