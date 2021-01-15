#include "Layers.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cassert>
#include <cstdio>

Layers::Layers(int numOfInputs, std::vector<unsigned> hiddenLayers, int numOfOutputs)
{
    initHiddenLayers(numOfInputs, hiddenLayers);
    initOutputLayer(numOfOutputs, hiddenLayers.back());
}


Layers::~Layers()
{
}


void Layers::initHiddenLayers(int numOfInputs, std::vector<unsigned>& hiddenLayers)
{
    int previousLayerOutputs = numOfInputs;

    for (unsigned i = 0; i < hiddenLayers.size(); ++i)
    {
        initHiddenLayer(hiddenLayers[i], previousLayerOutputs);
        previousLayerOutputs = hiddenLayers[i];
    }
}

void Layers::initHiddenLayer(int numOfNeutrons, int previousLayerOutputs)
{
    RandomNumber* ranum = RandomNumber::GetInstance();

    std::vector<std::vector<double>> weights;
    weights.resize(numOfNeutrons);
    double maxVal = 1 / std::sqrt(numOfNeutrons);

    for (unsigned k = 0; k < numOfNeutrons; ++k)
    {
        for (unsigned j = 0; j < previousLayerOutputs; ++j)
        {
            weights[k].push_back(
                ranum->RandomDouble(-maxVal, maxVal));
        }
    }

    layers.push_back(Layer(numOfNeutrons, previousLayerOutputs, weights));
}

void Layers::initOutputLayer(int numOfOutputs, int lastLayerOutputs)
{
    std::vector<std::vector<double>> weights;
    weights.resize(numOfOutputs);

    weights = std::vector<std::vector<double>>(numOfOutputs,
                                                std::vector<double>(lastLayerOutputs, 0.0));

    layers.push_back(Layer(numOfOutputs, lastLayerOutputs, weights));
}

Layer& Layers::getLastHiddenLayer()
{
    return layers[layers.size() - 2];
}

void Layers::Activate(const double& bwt, const double& hwt)
{
    std::vector<double> input = { bwt, hwt };

    for (auto& layer : layers)
    {
        layer.Activate(input);
        input = layer.GetOutputValues();
    }
}

void Layers::Derive()
{
    for (auto& layer : layers)
    {
        layer.Derive();
    }
}

void Layers::Propagate(std::vector<double> &target)
{
    auto& lastHiddenLayer = getLastHiddenLayer();
    Layer& outputLayer = layers.back();
    outputLayer.CalculateOutputLayerError(target);


    for (int i = layers.size() - 2; i >= 0; --i)
    {
        Layer& lastLayer = layers[i + 1];
        Layer &layer = layers[i];
        layer.CalculateHiddenLayerError(lastLayer);
    }

    for (unsigned i = 1; i < layers.size(); ++i)
    {
        layers[i].UpdateWeights(layers[i - 1], learningRate);
    }
}

bool Layers::IsOutputFemale()
{
    const auto output = layers.back().GetOutputValues();
    return (output[0] > output[1]);
}

double Layers::Cost(std::vector<double>& target)
{
    double cost{ 0.0 };
    auto& outputNeurons = layers.back().GetNeurons();

    assert(target.size() == outputNeurons.size());

    for (unsigned i = 0; i < target.size(); ++i)
    {
        cost += std::pow((outputNeurons[i].GetOutputValue() - target[i]), 2);
    }

    return cost;
}

void Layers::setLearningRate(double learningRate)
{
    this->learningRate = learningRate;
}
