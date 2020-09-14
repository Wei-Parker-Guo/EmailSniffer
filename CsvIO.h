#pragma once
#ifndef CSV_IO_H
#define CSV_IO_H

#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

typedef std::vector<std::string> set;
typedef std::pair<std::string, set> col;
typedef std::vector<col> dataset;

void write_csv(std::string filename, std::string colname, set vals);

void write_csv(std::string filename, dataset dataset);

dataset read_csv(std::string filename);

#endif // !CSV_IO_H
