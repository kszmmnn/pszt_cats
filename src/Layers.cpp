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
            layers.push_back(Layer(dimensions[0], dimensions[2]));
        }
        else if (i == dimensions.size() - 1)
        {
            std::vector<std::vector<double>> weights;
            weights.resize(dimensions[i]);
            for (unsigned k = 0; k < dimensions[i]; ++k)
            {

                for (unsigned j = 0; j < dimensions[i - 1]; ++j)
                {
                    weights[k].push_back(0.0);
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
    for(auto &layer : layers)
    {
        layer.DeriveLayer();
    }
}

void Layers::CalculateHiddenLayerGradient()
{

}

void Layers::CalculateOutputLayerGradient()
{

}

void Layers::Propagate(double target)
{

    double delta = target - layers.back().GetActivatedValues().back();
    std::vector<double> outputGradientVec { delta * layers.back().GetDerivedValues().back()};
    printf("%d  %d", layers.back().GetNeurons().size(), layers.front().GetNeurons().size());
    puts("efs");
    layers.back().SetGradients(outputGradientVec);
    delta = std::abs(delta);

    previousError = (previousError * previousSmoothingFactor + delta)
            / (previousSmoothingFactor + 1.0);
}
