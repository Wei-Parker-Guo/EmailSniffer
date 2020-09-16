#pragma once
#ifndef STRING_OP_H
#define STRING_OP_H

#include <string>

//some extra string ops are written here

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

#endif // !STRING_OP_H
