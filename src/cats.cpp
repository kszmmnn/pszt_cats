#include "Layers.hpp"
#include "Utils.hpp"
#include "FileReader.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <filesystem>

int main()
{
    unsigned successCount = 0;
    unsigned countFemale = 0;
    unsigned tries = 0;
    RandomNumber randNum();
    std::string fileName = "cats.csv";
    FileReader *fileReader = FileReader::GetInstance(fileName);

    // num of inputs, { hidden layer}, num of outputs
    Layers layers(2, { 20 }, 2);
    std::tuple<bool, double, double> config;
    double bwt;
    double hwt;

    while (fileReader->ParseConfig(config))
    {
        bwt = std::get<1>(config);
        hwt = std::get<2>(config);
        layers.Activate(bwt, hwt);
        std::vector<double> out;
        bool isFemale = std::get<0>(config);

        if (isFemale == layers.IsOutputFemale())
        {
            ++successCount;
        }
        
        if (isFemale)
        {
            countFemale++;
        }

        ++tries;
    }
    std::cout << "Female: " << countFemale << std::endl;
    printf("Proby przed uczeniem:  %u/%u \n", successCount, tries);


    for (int i = 0; i < 10; i++)
    {
        successCount = 0;
        tries = 0;
        fileReader->seekToStart();

        while (fileReader->ParseConfig(config))
        {
            bwt = std::get<1>(config);
            hwt = std::get<2>(config);

            layers.Activate(bwt, hwt);

            std::vector<double> out;
            bool isFemale = std::get<0>(config);

            if (isFemale == true)
            {
                out = { 1, 0 };
            }
            else
            {
                out = { 0, 1 };
            }

            if (isFemale == layers.IsOutputFemale())
            {
                ++successCount;
            }

            ++tries;

            layers.Derive();
            layers.Propagate(out);
            // printf("%f  \n", layers.Cost(out));
        }

        printf("Proby podczas uczenia:  %u/%u \n", successCount, tries);
    }
    fileReader->seekToStart();

    successCount = 0;
    tries = 0;
    int test = 0;
    while (fileReader->ParseConfig(config))
    {
        bwt = std::get<1>(config);
        hwt = std::get<2>(config);

        layers.Activate(bwt, hwt);
        std::vector<double> out;
        bool isFemale = std::get<0>(config);

        if (isFemale == layers.IsOutputFemale())
        {
            ++successCount;
        }

        if (layers.IsOutputFemale())
        {
            test++;
        }

        ++tries;
    }
    std::cout << "Wykrytych jako zenskie: " << test << std::endl;
    printf("Proby po uczeniu:  %u/%u \n", successCount, tries);
    return 0;
}

//w jednym miejscu error, w drugim gradient - zdecydowac sie
