#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <cstdlib>
#include <random>

constexpr unsigned MAX_VAL { 100 };

class RandomNumber
{
private:
    static RandomNumber *_instance;
    std::random_device randomDevice;
    std::mt19937_64 mt;
    RandomNumber();

public:
    RandomNumber(RandomNumber &clone) = delete;
    static RandomNumber* GetInstance();
    virtual ~RandomNumber();

    int RandomInt(int min = -MAX_VAL, int max = MAX_VAL);
    double RandomDouble(double min = -(double) MAX_VAL, double max =
            (double) MAX_VAL);
};

#endif /* UTILS_HPP_ */
