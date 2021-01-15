#ifndef NEURON_HPP_
#define NEURON_HPP_

#include <vector>

class Neuron
{
public:
    Neuron(std::vector<double> &_weights, double _bias);
    virtual ~Neuron();

    void Active(double value);
    void Derive();

    std::vector<double> GetWeights() const;
    double getWeight(int index) const;
    double GetOutputValue() const;
    double GetDerivedValue() const;
    double GetValue() const;
    double GetBias() const;
    double GetError() const;

    void SetError(double _error);
    void SetWeights(std::vector<double> &_weights);
    void SetWeight(unsigned pos, double _weight);
    void SetBias(double _bias);
  

private:
    double value { 0.0 };
    double outputValue { 0.0 };
    double derivedValue { 0.0 };
    double error { 0.0 };

    std::vector<double> weights;
    double bias { 0.0 };
};

#endif /* NEURON_HPP_ */

//https://machinelearningmastery.com/implement-backpropagation-algorithm-scratch-python/
