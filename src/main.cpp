#include "Network.h"
#include "FileReader.h"
#include "DataSet.h"
#include <iostream>

int main()
{
    FileReader* fileReader = FileReader::GetInstance("cats2.csv");
    Network* network;
    DataSet dataSet;

    int repeat = 10;
    int epochs = 10;

    int startHidden = 1;
    int endHidden = 100;
    int step = 2;

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

    int sumSuccess = 0;
    int successCount = 0;
    int tries;

    for (int hidden = startHidden; hidden <= endHidden; hidden += step)
    {
        for (int r = 0; r < repeat; r++)
        {
            network = new Network(2, { hidden }, 2);
            network->SetLearningRate(1);

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

                tries++;
            }

            delete network;
            sumSuccess += successCount;
        }

        

        sumSuccess /= repeat;
        std::cout << hidden << "," << sumSuccess << "," << (double)sumSuccess / 144 << std::endl;
    
        if (hidden == 1)
            hidden--;
    }

	return 0;
}