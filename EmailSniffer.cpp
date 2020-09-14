// EmailSniffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CsvIO.h"

using namespace std;

int main() {
	//uncomment this section to test IO
	//set test = { "1", "2", "3" };
	//col num_col = { "numbers", test };
	//set test2 = { "a", "b", "c" };
	//col letter_col = { "letters", test2 };
	//dataset data = { num_col, letter_col };
	//write_csv("test.csv", data);

	//read source dataset
	char file_buf[32];
	printf("Enter source email dataset: ");
	scanf_s("%s", file_buf, 32);
	printf("\nReading from %s ... ", file_buf);
	dataset src_dataset = read_csv(file_buf);
	printf("done.");

}
