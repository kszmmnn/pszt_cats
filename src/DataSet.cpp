#include <cmath>
#include "DataSet.h"


DataSet::DataSet()
{
}

DataSet::~DataSet()
{
}

void DataSet::AddDataRow(bool isFemale, double bwt, double hwt)
{
	DataRow dataRow = std::make_tuple(isFemale, bwt, hwt);
	dataRows.push_back(dataRow);
}

void DataSet::AddDataRow(DataRow dataRow)
{
	dataRows.push_back(dataRow);
}

double DataSet::GetStandardizedBwt(int row)
{
	double bwt = std::get<1>(dataRows[row]);

	return (bwt - bwtMean) / bwtStdError;
}

double DataSet::GetStandardizedHwt(int row)
{
	double hwt = std::get<2>(dataRows[row]);

	return (hwt - hwtMean) / hwtStdError;
}

std::vector<double> DataSet::GetBinaryOutput(int row)
{
	if (std::get<0>(dataRows[row]))
	{
		return std::vector<double>{1, 0};
	}
	else
	{
		return std::vector<double>{0, 1};
	}
}

bool DataSet::GetBoolOutput(int row)
{
	return std::get<0>(dataRows[row]);
}

void DataSet::CalcMean()
{
	double sumBwt = 0.0;
	double sumHwt = 0.0;

	for (int i = 0; i < dataRows.size(); i++)
	{
		sumBwt += std::get<1>(dataRows[i]);
		sumHwt += std::get<2>(dataRows[i]);
	}

	bwtMean = sumBwt / dataRows.size();
	hwtMean = sumHwt / dataRows.size();
}

void DataSet::CalcStdError()
{
	double bwt;
	double hwt;
	double sumStdBwt = 0.0;
	double sumStdHwt = 0.0;

	for (int i = 0; i < dataRows.size(); i++)
	{
		bwt = std::get<1>(dataRows[i]);
		hwt = std::get<2>(dataRows[i]);

		sumStdBwt += std::pow(bwt - bwtMean, 2);
		sumStdHwt += std::pow(hwt - hwtMean, 2);
	}

	bwtStdError = sumStdBwt / dataRows.size();
	bwtStdError = std::sqrt(bwtStdError);
	hwtStdError = sumStdHwt / dataRows.size();
	hwtStdError = std::sqrt(hwtStdError);
}


int DataSet::GetDataSetSize()
{
	return dataRows.size();
}
