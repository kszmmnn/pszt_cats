#include "Layers.hpp"
#include "Utils.hpp"
#include "FileReader.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
int main()
{
    unsigned successCount = 0;
    unsigned tries = 0;
    RandomNumber randNum();
    std::string filename = "cats.csv";
    FileReader *freader = FileReader::GetInstance(filename);
    std::vector<unsigned> dimensions = { 2,  100, 2 };
    Layers l(dimensions);

    std::tuple<bool, double, double> config;
    while (freader->ParseConfig(config))
    {
        l.ActivateAndDeriveAll(std::get<1>(config), std::get<2>(config));
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
        if(isFemale == l.IsOutputFemale())
        {
            ++successCount;
        }
        ++tries;
        l.Propagate(out);
        printf("%f  \n", l.Cost(out));
    }

    printf("success %u   tries %u", successCount, tries);
    return 0;
}

//w jednym miejscu error, w drugim gradient - zdecydowac sie
