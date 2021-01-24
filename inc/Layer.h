#pragma once
#include <vector>
#include <memory>
#include "Neuron.h"

using Neurons = std::vector<std::shared_ptr<Neuron>>;

class Layer
{
public:
	Layer();
	Layer(int numOfInputs, int numOfNeurons, bool outputLayer = false);

	void Activate(const std::vector<double>& input);
	void CalcGradient(const std::shared_ptr<Layer>& nextLayer);
	void CalcOutputLayerGradient(const std::vector<double>& expectedValues);
	void UpdateWeights(const std::vector<double>& inputs, const double& learningRate);

	std::vector<double> GetActivationValues();
	std::vector<double> GetValues();
	std::shared_ptr<Neuron> GetNeuron(int index);
	int GetNeuronsCount();

private:
	int numOfInputs = 0;
	int numOfNeurons = 0;

	Neurons neurons;

	void initLayer();
	void initLayer(double maxWeight);
};

