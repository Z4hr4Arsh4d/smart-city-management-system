#include "utility.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace UTIL
{
    void getCSVSize(const string& filename, int& rows, int& cols)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "Error opening file. Recheck Path" << endl;
            rows = -1;
            cols = -1;
            return;
        }

        rows = 0;
        cols = 1;

        string line;
        getline(file, line);

        for (char ch : line)
            if (ch == ',') cols++;

        while (getline(file, line))
            rows++;

        file.close();
    }

    string* lineParser(const string& line, int MAX_COL)
    {
        string* data = new string[MAX_COL];
        string cell = "";
        int col = 0;

        for (char ch : line)
        {
            if (ch == ',')
            {
                if (col < MAX_COL) data[col++] = cell;
                cell = "";
            }
            else if (ch != '\r')
            {
                cell += ch;
            }
        }

        if (col < MAX_COL) data[col++] = cell;

        while (col < MAX_COL) data[col++] = "";

        return data;
    }

    string** CSVParser(const string& filename, int& rows, int& cols)
    {
        getCSVSize(filename, rows, cols);

        if (rows == -1 && cols == -1)
            return nullptr;

        ifstream file(filename);
        if (!file.is_open())
            return nullptr;

        string** data = new string * [rows];

        string line;
        if (!getline(file, line))
        {
            file.close();
            delete[] data;
            rows = 0;
            return nullptr;
        }

        int row = 0;
        while (row < rows && getline(file, line))
            data[row++] = lineParser(line, cols);

        while (row < rows)
        {
            data[row] = new string[cols];
            for (int c = 0; c < cols; c++) data[row][c] = "";
            row++;
        }

        file.close();
        return data;
    }

    void freeCSV(string** data, int rows)
    {
        if (!data || rows <= 0) return;

        for (int i = 0; i < rows; i++)
            delete[] data[i];

        delete[] data;
    }

    int stringToInt(const string& str)
    {
        int value = 0;
        for (char ch : str)
        {
            if (ch < '0' || ch > '9')
                return -1;

            value = value * 10 + (ch - '0');
        }
        return value;
    }


    bool validateCNIC(const string& cnic)
    {
        // valid format 61101-1111111-1
        if (cnic.length() != 15)
            return false;

        for (int i = 0; i < cnic.length(); i++)
        {
            if (i == 5 || i == 13)
            {
                if (cnic[i] != '-')
                    return false;
            }
            else
            {
                if (cnic[i] < '0' || cnic[i] > '9')
                    return false;
            }
        }
        return true;
    }

    bool isNumeric(const string& str)
    {
        if (str.empty())
            return false;

        bool hasDigit = false;
        bool dotSeen = false;

        for (char ch : str)
        {
            if (ch == '.')
            {
                if (dotSeen)
                    return false; // only one decimal point allowed
                dotSeen = true;
                continue;
            }

            if (ch >= '0' && ch <= '9')
            {
                hasDigit = true;
                continue;
            }

            return false; // any non-digit/non-dot character fails
        }

        return hasDigit; // need at least one digit (reject "." or "..")
    }
}
