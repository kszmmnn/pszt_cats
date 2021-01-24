#pragma once
#include <vector>
#include <memory>
#include "Layer.h"

using Layers = std::vector<std::shared_ptr<Layer>>;

class Network
{
public:
	Network() = delete;
	Network(int numOfInputs, const std::vector<int>& hiddenLayersSize, int numOfOutputs);
	~Network();

	void Activate();
	void Backpropagation();

	double CalcCost();
	bool IsFemale();

	void SetDataRow(std::vector<double> inputs, std::vector<double> expected);
	void SetLearningRate(double learningRate);
	
private:
	int numOfInputs;
	int numOfOutputs;
	double learningRate = 0.1;

	Layers hiddenLayers;
	std::shared_ptr<Layer> outputLayer;

	std::vector<double> expected;
	std::vector<double> inputs;

	void initHiddenLayers(const std::vector<int>& hiddenLayersSize);
	void initOutputLayer(const double& inputs);
};

