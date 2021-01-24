#include "FileReader.h"

FileReader* FileReader::_instance = nullptr;

FileReader::FileReader(std::string _fileName) :
    fileName(_fileName)
{
    OpenFile();
}

FileReader::~FileReader()
{
    file.close();
}

FileReader* FileReader::GetInstance(std::string fileName)
{
    if (_instance == nullptr)
        _instance = new FileReader(fileName);

    return _instance;
}

void FileReader::OpenFile()
{
    file.open(fileName, std::ios::in | std::ios::binary);
    if (file.fail())
    {
        std::cout << "fileError" << std::endl;
    }
}

bool FileReader::ParseConfig(std::tuple<bool, double, double>& ret)
{
    std::string line;

    if (std::getline(file, line))
    {
        ret = GetSingleConfig(line);
        return true;
    }
    return false;
}

std::tuple<bool, double, double> FileReader::GetSingleConfig(std::string line)
{
    std::tuple<bool, double, double> item;
    std::string delimiter = ",";

    size_t position = line.find(delimiter);

    std::string sex = line.substr(0, position - 1);
    sex = sex.substr(1, sex.length() - 1);

    bool isFemale = false;
    if (sex == "F")
    {
        isFemale = true;
    }

    position = line.find(delimiter, 2);

    double bwt = std::stod(
        line.substr(position + 1, line.find(delimiter, 4) - 1));
    double hwt = std::stod(
        line.substr(line.find(delimiter, 4) + 1, line.length() - 1));

    item = std::make_tuple(isFemale, bwt, hwt);
    return item;
}

void FileReader::seekToStart()
{
    file.clear();
    file.seekg(0);
}