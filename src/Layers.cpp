#include "Layers.hpp"
#include "Utils.hpp"

#include <cassert>
#include <cstdio>

Layers::Layers(std::vector<unsigned> &dimensions)
{
    auto ranum = RandomNumber::GetInstance();
    for (unsigned i = 0; i < dimensions.size(); ++i)
    {
        if (i == 0)
        {
            layers.push_back(Layer(dimensions[0], inputCount));
        }
        else if (i == dimensions.size() - 1)
        {
            std::vector<std::vector<double>> weights;
            weights.resize(dimensions[i]);
            for (unsigned k = 0; k < dimensions[i]; ++k)
            {

                for (unsigned j = 0; j < dimensions[i - 1]; ++j)
                {
                    weights[k].push_back(0);
                }
            }
            layers.push_back(Layer(dimensions[i], dimensions[i - 1], weights));

        }
        else
        {
            std::vector<std::vector<double>> weights;
            weights.resize(dimensions[i]);
            double maxVal = 1 / std::sqrt(dimensions[i - 1]);
            for (unsigned k = 0; k < dimensions[i]; ++k)
            {

                for (unsigned j = 0; j < dimensions[i - 1]; ++j)
                {
                    weights[k].push_back(
                                         ranum->RandomDouble(-maxVal, maxVal));
                }
            }
            layers.push_back(Layer(dimensions[i], dimensions[i - 1], weights));
        }
    }
}

Layers::~Layers()
{
}

void Layers::ActivateAndDeriveAll(double bwt, double hwt)
{
    std::vector<double> input = { bwt, hwt };

    for (auto &layer : layers)
    {
        layer.ActivateLayer(input);
        input = layer.GetActivatedValues();
    }
    for (auto &layer : layers)
    {
        layer.DeriveLayer();
    }
}

double Layers::Cost(std::vector<double> &target)
{
    double cost { 0.0 };
    auto &outputNeurons = layers.back().GetNeurons();
    assert(target.size() == outputNeurons.size());

    for (unsigned i = 0; i < target.size(); ++i)
    {
        cost += std::pow((outputNeurons[i].GetActivatedValue() - target[i]), 2);
    }
    return cost;
}

bool Layers::IsOutputFemale()
{
    const auto output = layers.back().GetActivatedValues();
    if (output[0] > output[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Layers::Propagate(std::vector<double> &target)
{
    double cost = Cost(target); //moze trzeba bedzie go zmienic na jamkas srednia
    auto &l = layers[layers.size() - 2];
    layers.back().CalculateOutputLayerGradient(target);
    l.CalculateHiddenLayerGradient(layers.back());
//
//        m_recentAverageError =
//                (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
//                / (m_recentAverageSmoothingFactor + 1.0);
//        // Calculate output layer gradients
//
    for (unsigned i = layers.size() - 2; i > 0; --i)
    {
        Layer &nextLayer = layers[i + 1];
        Layer &layer = layers[i];
        layer.CalculateHiddenLayerGradient(nextLayer);
    }

    for (unsigned i = 1; i < layers.size(); ++i)
    {
        layers[i].UpdateWeights(layers[i - 1]);
    }
}
