#pragma once
#include <vector>
#include "RandomNumber.h"

class Neuron
{
public:
	Neuron(int numOfInputs, double maxWeight);

	void CalcValue(const std::vector<double>& inputs);
	void CalcActivation();
	double CalcDerivative();
	void UpdateWeight(double weight, int index);

	void SetWeight(double weight, int index);
	void SetError(double error);
	
	double GetWeight(int index);
	double GetActivationValue();
	double GetValue();
	double GetError();

private:
	double value = 0.0;
	double activationValue = 0.0;
	double error = 0.0;

	int numOfInputs;

	std::vector<double> weights;
};

