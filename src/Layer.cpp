#include "Layer.h"

#include <iostream>

Layer::Layer()
{
}

Layer::Layer(int numOfInputs, int numOfNeurons, bool outputLayer) : numOfInputs(numOfInputs), numOfNeurons(numOfNeurons)
{
	if (!outputLayer)
	{
		initLayer();
	}
	else
	{
		// warstwa wyjœciowa inicjalizowana zerowymi wagami
		initLayer(0.0); 
	}
}

void Layer::initLayer()
{
	double maxWeight = 1 / std::sqrt(numOfInputs);
	initLayer(maxWeight);
}

void Layer::initLayer(double maxWeight)
{
	for (int i = 0; i < numOfNeurons; i++)
	{
		std::shared_ptr<Neuron> neuron = std::make_shared<Neuron>(numOfInputs, maxWeight);

		neurons.push_back(neuron);
	}
}

void Layer::Activate(const std::vector<double>& input)
{
	std::shared_ptr<Neuron> neuron;
	for (int i = 0; i < numOfNeurons; i++)
	{
		neuron = neurons[i];
		neuron->CalcValue(input);
		neuron->CalcActivation();
	}
}

void Layer::CalcGradient(const std::shared_ptr<Layer>& nextLayer)
{
	double error;
	int nextLayerSize = nextLayer->GetNeuronsCount();
	std::shared_ptr<Neuron> nextLayerNeuron;

	for (int i = 0; i < numOfNeurons; i++)
	{
		error = 0.0;
		
		for (int j = 0; j < nextLayerSize; j++)
		{
			nextLayerNeuron = nextLayer->GetNeuron(j);
			error += nextLayerNeuron->GetError() * nextLayerNeuron->GetWeight(i);
		}
		
		error *= neurons[i]->CalcDerivative();
		neurons[i]->SetError(error);
	}
}

void Layer::CalcOutputLayerGradient(const std::vector<double>& expectedValues)
{
	double error;
	double output;

	for (int i = 0; i < numOfNeurons; i++)
	{
		output = neurons[i]->GetActivationValue();
		error = neurons[i]->CalcDerivative();
		//error *= (expectedValues[i] - output);
		
		error *= (output - expectedValues[i]);

		neurons[i]->SetError(error);
	}
}

void Layer::UpdateWeights(const std::vector<double>& inputs, const double& learningRate)
{
	std::shared_ptr<Neuron> neuron;
	double deltaForAll;
	double delta;

	for (int i = 0; i < numOfNeurons; i++)
	{
		neuron = neurons[i];
		deltaForAll = learningRate * neuron->GetError();

		for (int j = 0; j < numOfInputs; j++)
		{
			delta = deltaForAll * inputs[j];
			neuron->UpdateWeight(delta, j);
		}
	}
}

std::vector<double> Layer::GetActivationValues()
{
	std::vector<double> values;

	for (int i = 0; i < numOfNeurons; i++)
	{
		values.push_back(neurons[i]->GetActivationValue());
	}

	return values;
}

std::vector<double> Layer::GetValues()
{
	std::vector<double> values;

	for (int i = 0; i < numOfNeurons; i++)
	{
		values.push_back(neurons[i]->GetValue());
	}

	return values;
}

int Layer::GetNeuronsCount()
{
	return numOfNeurons;
}

std::shared_ptr<Neuron> Layer::GetNeuron(int index)
{
	return neurons[index];
}