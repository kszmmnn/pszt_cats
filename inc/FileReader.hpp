#ifndef FILEREADER_HPP_
#define FILEREADER_HPP_

#include <fstream>
#include <string>
#include <iostream>
#include <tuple>

class FileReader
{
public:
    FileReader() = delete;
    FileReader(FileReader& clone) = delete;
    ~FileReader();

    static FileReader* GetInstance(std::string fileName);
    

    bool ParseConfig(std::tuple<bool, double, double> &ret);
    std::tuple<bool, double, double> GetSingleConfig(std::string line);
    void seekToStart();

private:
    std::fstream file;
    std::string fileName;
    static FileReader *_instance;

    FileReader(std::string _fileName);
    void OpenFile();
};

#endif /* FILEREADER_HPP_ */
