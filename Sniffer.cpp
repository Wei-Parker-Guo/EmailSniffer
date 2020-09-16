#include "Sniffer.h"


//constructor
Sniffer::Sniffer(const SnifferMode mode, const int max_feature_n) {
	this->mode = mode;
	this->max_feature_n = max_feature_n;
}

//methods
void Sniffer::update_cache_pool(const vector<string>& tokens) { //take in a list of tokens and update cache pool accordingly
	//loop through the given tokens, update their freqs
	for (string token : tokens) {
		if (this->cache_pool.find(token) == this->cache_pool.end()) {
			//not found, create new
			cache_pool[token] = 1;
		}
		else {
			//found, update freq
			cache_pool.find(token)->second += 1;
		}
	}
}

map<string, int> Sniffer::get_result(const vector<string>& tokens) { //get specific result of this list of tokens 
	//calculate result based on mode/algorithm selected
	this->result.clear();
	//create and default vector to zero
	for (std::map<string, int>::iterator it = features.begin(); it != features.end(); ++it) this->result[it->first] = 0;
	switch (this->mode)
	{
	case SnifferMode::BAG_OF_WORDS:
		for (std::map<string, int>::iterator it = result.begin(); it != result.end(); ++it) {
			string feature = it->first;
			//count features and update
			it->second = std::count(tokens.begin(), tokens.end(), feature);
		}
		break;
	case SnifferMode::TFIDF:
		break;
	case SnifferMode::N_GRAM:
		break;
	default:
		break;
	}

	return this->result;
}

void Sniffer::extract_features() { //extract feature according to max_feature_n from cache pool
	features.clear();
	//loop through cache pool, selecting the top max_feature_n terms with most freqs, basically an insertion sort
	for (std::map<string, int>::iterator it = cache_pool.begin(); it != cache_pool.end(); ++it) {
		string feature = it->first;
		int freq = it->second;

		//if we are not full, simply add
		if (this->features.size() < this->max_feature_n) this->features[feature] = freq;
		//if we are full, replace based on condition
		else {
			for (std::map<string, int>::iterator it1 = features.begin(); it1 != features.end(); ++it1) {
				string old_fea = it1->first;
				int old_freq = it1->second;
				//replace if greater than the old element
				if (freq > old_freq) {
					features.erase(old_fea);
					features[feature] = freq;
					break; //short jump since we are done
				}
			}
		}
	}
}
