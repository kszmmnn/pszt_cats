#include <iostream>
#include "Network.h"

Network::Network(int numOfInputs, const std::vector<int>& hiddenLayersSize, int numOfOutputs) : numOfInputs(numOfInputs), numOfOutputs(numOfOutputs)
{
	initHiddenLayers(hiddenLayersSize);
	initOutputLayer(hiddenLayersSize.back());
}

void Network::initHiddenLayers(const std::vector<int>& hiddenLayersSize)
{
	int inputs = numOfInputs + 1;

	for (unsigned int i = 0; i < hiddenLayersSize.size(); i++)
	{
		std::shared_ptr<Layer> newLayer = std::make_shared<Layer>(inputs, hiddenLayersSize[i], false);
		hiddenLayers.push_back(newLayer);

		inputs = hiddenLayersSize[i] + 1;
	}
}

void Network::initOutputLayer(const double& inputs)
{
	outputLayer = std::make_shared<Layer>(inputs + 1, numOfOutputs, true);
}

Network::~Network()
{
}

void Network::Activate()
{
	std::vector<double> input = inputs;

	Layers::iterator it;

	for (it = hiddenLayers.begin(); it != hiddenLayers.end(); it++)
	{
		(*it)->Activate(input);
		input = (*it)->GetActivationValues();
		input.push_back(1.0); // Bias
	}

	outputLayer->Activate(input);
}


void Network::SetDataRow(std::vector<double> inputs, std::vector<double> expected)
{
	inputs.push_back(1.0); // bias
	this->inputs = inputs;
	this->expected = expected;
}

void Network::SetLearningRate(double learningRate)
{
	this->learningRate = learningRate;
}

double Network::CalcCost()
{
	std::vector<double> output = outputLayer->GetActivationValues();
	double cost = 0.0;

	for (int i = 0; i < numOfOutputs; i++)
	{
		cost += std::pow((output[i] - expected[i]), 2);
	}

	cost /= 2;
	return cost;
}

void Network::Backpropagation()
{	
	outputLayer->CalcOutputLayerGradient(expected);
	std::shared_ptr<Layer> nextLayer = outputLayer;

	for (int j = hiddenLayers.size() -1; j >= 0; j--)
	{
		hiddenLayers[j]->CalcGradient(nextLayer);

		nextLayer = hiddenLayers[j];
	}

	std::vector<double> previousOutput = inputs;

	for (unsigned int j = 0; j < hiddenLayers.size(); j++)
	{
		hiddenLayers[j]->UpdateWeights(previousOutput, learningRate);

		previousOutput = hiddenLayers[j]->GetActivationValues();
		previousOutput.push_back(1.0); // Bias
	}

	outputLayer->UpdateWeights(previousOutput, learningRate);
}

bool Network::IsFemale()
{
	std::vector<double> actValues = outputLayer->GetActivationValues();
	return actValues[0] > actValues[1];
}