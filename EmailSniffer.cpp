// EmailSniffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CsvIO.h"
#include "Tokenizer.h"
#include "Sniffer.h"

using namespace std;

int main() {
	//uncomment this section to test IO, current build is for Winx64
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
	printf("Reading from %s ... ", file_buf);
	dataset src_dataset = read_csv(file_buf);
	printf("done.\n");

	//initialize tokenizer, put it on heap for better mem management
	char file_buf1[32];
	printf("Enter stopwords set (should be a txt): ");
	scanf_s("%s", file_buf1, 32);
	Tokenizer* tokenizer = new Tokenizer(file_buf1);

	//initialize Sniffer, put it on heap also
	printf("[Sniffer Config]\nMaximum feature list length: ");
	int max_feature_n = 10; //default feature list length to 10
	scanf_s("%d", &max_feature_n, 1);
	Sniffer* sniffer = new Sniffer(SnifferMode::BAG_OF_WORDS, max_feature_n);

	//initialize output dataset
	dataset out_data = src_dataset;

	//loop through each entry, tokenize them with stopwords removed and add to output dataset
	printf("\nStart sniffing (preprocessing) ... ");
	col text_col = out_data[0];
	col class_col = out_data[1];

	//initialize output cols
	col token_col;
	token_col.first = "Tokens";
	out_data.push_back(token_col);
	int non_vec_col_n = out_data.size(); //record fixed col number for later manipulation
	for (int i = 0; i < max_feature_n; i++) {
		col vec_col;
		out_data.push_back(vec_col);
	}
	
	//go through the text loop once to initialize cache for our sniffer
	for (int i = 0; i < out_data[0].second.size(); i++) {
		string text = text_col.second.at(i);
		vector<string> tokens;
		tokenizer->tokenize_with_stopwords_rm(text, tokens);
		//update cache pool for our sniffer
		sniffer->update_cache_pool(tokens);

		//record concatenated tokens to out data
		string concat_tokens = "";
		for (string token : tokens) concat_tokens = concat_tokens + " " + token;
		out_data[2].second.push_back(concat_tokens);
	}
	//extract features for sniffer after this loop
	sniffer->extract_features();

	//loop again, process each entry's output cols and attach to out dataset
	for (int i = 0; i < out_data[0].second.size(); i++) {
		string text = text_col.second.at(i);
		vector<string> tokens;
		tokenizer->tokenize_with_stopwords_rm(text, tokens);
		//get result word vector
		map<string, int> result = sniffer->get_result(tokens);

		//uncomment this to produce verbose outputs
		//printf("Entry %d vector = [ ", i);
		//for (std::map<string, int>::iterator it = result.begin(); it != result.end(); ++it) {
		//	printf("%s : %d; ", it->first.c_str(), it->second);
		//}
		//printf("]\n");

		//attach vector cols to out data
		int index = 0;
		for (std::map<string, int>::iterator it = result.begin(); it != result.end(); ++it) {
			out_data[index + non_vec_col_n].first = it->first;
			out_data[index + non_vec_col_n].second.push_back(to_string((int)it->second));
			index += 1;
		}
	}

	printf("done.\n");

	//write output to user file
	printf("\nEnter output file name (.csv): ");
	char file_buf2[32];
	scanf_s("%s", file_buf2, 32);
	printf("Writing to %s ... ", file_buf2);
	write_csv(file_buf2, out_data);
	printf(" done.\n");
}
