#include "Neuron.h"
#include <iostream>

Neuron::Neuron(int numOfInputs, double maxWeight) : numOfInputs(numOfInputs)
{
	RandomNumber* randomNum = RandomNumber::GetInstance();
	
	for (int i = 0; i < numOfInputs; i++)
	{
		weights.push_back(randomNum->RandomDouble(-maxWeight, maxWeight));
	}
}

void Neuron::CalcValue(const std::vector<double>& inputs)
{
	double sum = 0.0;

	for (int i = 0; i < numOfInputs; i++)
	{
		sum += inputs[i] * weights[i];
	}

	value = sum;
}

void Neuron::CalcActivation()
{
	activationValue = 1.0 / (1.0 + std::exp(value));
}


double Neuron::CalcDerivative()
{
	return activationValue * (1.0 - activationValue);
}

void Neuron::SetWeight(double weight, int index)
{
	weights[index] = weight;
}

void Neuron::SetError(double error)
{
	this->error = error;
}

void Neuron::UpdateWeight(double weight, int index)
{
	weights[index] -= weight;
}

double Neuron::GetWeight(int index)
{
	return weights[index];
}

double Neuron::GetActivationValue()
{
	return activationValue;
}

double Neuron::GetValue()
{
	return value;
}

double Neuron::GetError()
{
	return error;
}
