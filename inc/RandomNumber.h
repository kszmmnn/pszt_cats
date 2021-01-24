#pragma once
#include <cstdlib>
#include <random>

class RandomNumber
{
private:
    static RandomNumber* _instance;
    std::random_device randomDevice;
    std::mt19937_64 mt;
    RandomNumber();

public:
    RandomNumber(RandomNumber& clone) = delete;
    static RandomNumber* GetInstance();
    virtual ~RandomNumber();

    int RandomInt(int min, int max);
    double RandomDouble(double min, double max);
};