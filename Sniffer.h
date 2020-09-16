#pragma once
#ifndef SNIFFER_H
#define SNIFFER_H
//***************************************************************************************************
//CORE Module of Email Sniffer, this part contains algorithms and modes to extract features and stats
//***************************************************************************************************

#include <string>
#include <vector>
#include <map>

using namespace std;

//modes for the sniffer to operate under
enum class SnifferMode
{
	BAG_OF_WORDS,
	TFIDF,
	N_GRAM
};

class Sniffer {
public:
	//params
	SnifferMode mode;
	int max_feature_n; //maximum feature number
	map<string, int> cache_pool; //a cache pool to store all terms, thus determing highest freq words for features
	map<string, int> features; //features storage
	map<string, int> result; //cache map to pool all features

	//constructor
	Sniffer(const SnifferMode mode, const int max_feature_n);
	
	//methods
	void update_cache_pool(const vector<string>& tokens); //take in a list of tokens and update cache pool accordingly

	map<string, int> get_result(const vector<string>& tokens); //get specific result of this list of tokens 

	void extract_features(); //extract feature according to max_feature_n from cache pool
};



#endif // !SNIFFER_H
