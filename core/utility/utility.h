#pragma once
#include <string>
using namespace std;

namespace UTIL
{
    void getCSVSize(const string& filename, int& rows, int& cols);

    string* lineParser(const string& line, int MAX_COL);

    string** CSVParser(const string& filename, int& rows, int& cols);

    void freeCSV(string** data, int rows);

    int stringToInt(const string& str);

    bool validateCNIC(const string& cnic);

    bool isNumeric(const string& str);
}
