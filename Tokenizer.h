#pragma once
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

using namespace std;

class Tokenizer {
public:
	//params
	string stopword_selection;
	vector<string> stopwords;
	
	//constructor specifying the stopwords we are using
	Tokenizer(const string stopword_selection);

	//method to return a text's tokenized list tl with stopwords removed
	void tokenize_with_stopwords_rm(const string txt, vector<string>& tl);
private:
	void construct_stopwords();
};

#endif // !TOKENIZER_H
