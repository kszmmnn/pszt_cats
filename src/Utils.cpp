#include "Utils.hpp"


RandomNumber * RandomNumber::_instance = nullptr;

RandomNumber* RandomNumber::GetInstance()
{
    if (_instance == nullptr)
        _instance = new RandomNumber();

    return _instance;
}

RandomNumber::~RandomNumber()
{
    delete _instance;
}

RandomNumber::RandomNumber()
{
    mt = std::mt19937_64(randomDevice());
}

int RandomNumber::RandomInt(int min, int max)
{
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(mt);
}

double RandomNumber::RandomDouble(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(mt);
}
