#include "Network.h"
#include "FileReader.h"
#include <iostream>

int main()
{
    FileReader *fileReader = FileReader::GetInstance("cats.csv");

    int repeat = 10;
    int epochs = 10;

    Network *network;

    int sumSuccess = 0;
    int successCount = 0;
    int tries;

    std::tuple<bool, double, double> config;

    double bwtMean { 0.0 };
    double hwtMean { 0.0 };
    double bwtStdError { 0.0 };
    double hwtStdError { 0.0 };
    unsigned populationCount { 0 };
    fileReader->seekToStart();
    while (fileReader->ParseConfig(config))
    {
        bwtMean += std::get<1>(config);
        hwtMean += std::get<2>(config);
        populationCount++;
    }
    bwtMean /= populationCount;
    hwtMean /= populationCount;

    fileReader->seekToStart();
    while (fileReader->ParseConfig(config))
    {
        bwtStdError += std::pow(std::get<1>(config) - bwtMean, 2);
        hwtStdError += std::pow(std::get<2>(config) - hwtMean, 2);
    }
    bwtStdError /= populationCount;
    hwtStdError /= populationCount;
    bwtStdError = std::sqrt(bwtStdError);
    hwtStdError = std::sqrt(hwtStdError);

    for (int r = 0; r < repeat; r++)
    {
        network = new Network(2, { 40 }, 2);
        network->SetLearningRate(0.05);

        double bwt;
        double hwt;

        for (int i = 0; i < epochs; i++)
        {
            fileReader->seekToStart();
            while (fileReader->ParseConfig(config))
            {
                bwt = (std::get<1>(config) - bwtMean)/bwtStdError;
                hwt = (std::get<2>(config) - hwtMean)/hwtStdError;
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

                network->SetDataRow( { bwt, hwt }, out);
                network->Activate();

                network->Backpropagation();
            }
        }

        successCount = 0;
        tries = 0;

        fileReader->seekToStart();

        while (fileReader->ParseConfig(config))
        {
            bwt = std::get<1>(config);
            hwt = std::get<2>(config);
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

            network->SetDataRow( { bwt, hwt }, out);
            network->Activate();

            if (isFemale == network->IsFemale())
            {
                ++successCount;
            }

            ++tries;

        }
        delete network;
        sumSuccess += successCount;
    }
    sumSuccess /= repeat;

    std::cout << sumSuccess << "," << (double) sumSuccess / 144 << std::endl;

    return 0;
}
