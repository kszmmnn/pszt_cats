#include "Network.h"
#include "FileReader.h"
#include "DataSet.h"
#include <iostream>

int main()
{
    FileReader* fileReader = FileReader::GetInstance("cats.csv");
    Network* network;
    DataSet dataSet;

    int repeat = 25;
    int epochs = 10;


    std::tuple<bool, double, double> config;

    fileReader->seekToStart();
    while (fileReader->ParseConfig(config))
    {
        dataSet.AddDataRow(config);
    }

    dataSet.CalcMean();
    dataSet.CalcStdError();

    int dataSetSize = dataSet.GetDataSetSize();

    std::vector<double> out;
    double bwt;
    double hwt;

    double sumSuccess = 0.0;
    int successCount = 0;
    int tries;

    for (int r = 0; r < repeat; r++)
    {
        network = new Network(2, { 30, 19, 10 }, 2);
        network->SetLearningRate(0.1);

        // Uczenie 
        for (int i = 0; i < epochs; i++)
        {
            for (int row = 0; row < dataSetSize; row++)
            {
                bwt = dataSet.GetStandardizedHwt(row);
                hwt = dataSet.GetStandardizedBwt(row);
                out = dataSet.GetBinaryOutput(row);

                network->SetDataRow({ bwt, hwt }, out);
                network->Activate();

                network->Backpropagation();
            }
        }

        successCount = 0;
        tries = 0;
        int female = 0;

        // Testowanie predykcji
        for (int row = 0; row < dataSetSize; row++)
        {
            bwt = dataSet.GetStandardizedHwt(row);
            hwt = dataSet.GetStandardizedBwt(row);
            out = dataSet.GetBinaryOutput(row);

            network->SetDataRow({ bwt, hwt }, out);
            network->Activate();

            if (dataSet.GetBoolOutput(row) == network->IsFemale())
            {
                ++successCount;
            }

            if (network->IsFemale())
                female++;

            tries++;
        }

        delete network;
        sumSuccess += successCount;
    }


    sumSuccess /= repeat;
    std::cout << sumSuccess << "," << sumSuccess / 144 << std::endl;

	return 0;
}