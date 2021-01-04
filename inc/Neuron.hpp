#ifndef NEURON_HPP_
#define NEURON_HPP_

#include <vector>

class Neuron
{
public:
    Neuron(std::vector<double> &_weights, double _bias);
    virtual ~Neuron();
    void Activate(double value);
    void Derive(double value);

    double GetActivatedValue() const;
    double GetDerivedValue() const;
    double GetValue() const;
    double GetBias() const;
    double GetGradient() const;
    void SetGradient(double _gradient);

    void SetWeights(std::vector<double> &_weights);
    std::vector<double> GetWeights() const;

private:
    double value { 0.0 };
    double activatedValue { 0.0 };
    double derivedValue { 0.0 };
    double gradient {0.0};

    std::vector<double> weights;
    double bias { 0.0 };
};

#endif /* NEURON_HPP_ */
