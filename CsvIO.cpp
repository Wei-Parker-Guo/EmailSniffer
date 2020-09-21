//******************************************************************************************************************
//CSV WRITE/READ IO, REFERRED & EDITED FROM https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
//******************************************************************************************************************

#include "CsvIO.h"
#include <algorithm> 
#include <cctype>
#include <locale>
#include "StringOp.h"

void write_csv(std::string filename, std::string colname, set vals) {
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // colname - the name of the one and only column
    // vals - an integer vector of values

    // Create an output filestream object
    std::ofstream myFile(filename);

    // Send the column name to the stream
    myFile << colname << "\n";

    // Send data to the stream
    for (int i = 0; i < vals.size(); ++i)
    {
        myFile << vals.at(i) << "\n";
    }

    // Close the file
    myFile.close();
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void write_csv(std::string filename, dataset dataset) {
    // Make a CSV file with one or more columns of string/integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Create an output filestream object
    std::ofstream myFile(filename);

    // Send column names to the stream
    for (int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for (int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (int j = 0; j < dataset.size(); ++j)
        {
            //if string content then quote with quotes
            std::string content = dataset.at(j).second.at(i);
            if (!is_number(content)) content = "\"" + content + "\"";
            
            myFile << content;
            if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
}


dataset read_csv(std::string filename) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, string vector> pairs to store the result
    dataset result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    std::string val;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while (std::getline(ss, colname, ',')) {

            // Initialize and add <colname, int vector> pairs to result
            result.push_back({ colname, std::vector<std::string> {} });
        }
    }

    // Read data, line by line
    while (std::getline(myFile, line))
    {
        std::string sub1 = line.substr(0, line.length() - 3);
        result[0].second.push_back(trim(sub1, "\""));
        std::string sub2 = line.substr(line.length() - 1, line.length() - 1);
        if (std::isdigit(sub2[0])) result[1].second.push_back(sub2);
        else result[1].second.push_back("-1");
    }

    // Close file
    myFile.close();

    return result;
}
