#pragma once
#include <vector>
#include <tuple>

using DataRow = std::tuple<bool, double, double>;

class DataSet
{
public:
	DataSet();
	~DataSet();
	void AddDataRow(bool isFemale, double bwt, double hwt);
	void AddDataRow(DataRow dataRow);
	void CalcMean();
	void CalcStdError();

	double GetStandardizedBwt(int row);
	double GetStandardizedHwt(int row);
	std::vector<double> GetBinaryOutput(int row);
	bool GetBoolOutput(int row);
	int GetDataSetSize();
private:
	std::vector<DataRow> dataRows;
	double bwtMean = 0.0;
	double hwtMean = 0.0;
	double bwtStdError = 0.0;
	double hwtStdError = 0.0;
};

