#include "Sniffer.h"


//constructor
Sniffer::Sniffer(const SnifferMode mode, const int max_feature_n) {
	this->mode = mode;
	this->max_feature_n = max_feature_n;
	this->documents_n = 0;
}

//methods
void Sniffer::update_cache_pool(const vector<string>& tokens) { //take in a list of tokens and update cache pool accordingly
	//loop through the given tokens, update their freqs and IDFs (notice we only count IDF's divider here, aka document occurences)
	bool IDF_updated = false;
	for (string token : tokens) {
		if (this->cache_pool.find(token) == this->cache_pool.end()) {
			//not found, create new
			cache_pool[token] = 1;
			cache_IDFs[token] = 1; //initialize a new IDF for this token
			IDF_updated = true;
		}
		else {
			//found, update freq
			cache_pool.find(token)->second += 1;
			//update IDF only once
			if (!IDF_updated) {
				cache_IDFs.find(token)->second += 1;
				IDF_updated = true;
			}
		}
	}
	this->documents_n += 1; //update total document number
}

map<string, float> Sniffer::get_result(const vector<string>& tokens) { //get specific result of this list of tokens 
	//calculate result based on mode/algorithm selected
	this->result.clear();
	//create and default vector to zero
	for (std::map<string, int>::iterator it = features.begin(); it != features.end(); ++it) this->result[it->first] = 0;
	switch (this->mode)
	{
	case SnifferMode::BAG_OF_WORDS:
		for (std::map<string, float>::iterator it = result.begin(); it != result.end(); ++it) {
			string feature = it->first;
			//count features and update
			it->second = std::count(tokens.begin(), tokens.end(), feature);
		}
		break;
	case SnifferMode::TFIDF:
		for (std::map<string, float>::iterator it = result.begin(); it != result.end(); ++it) {
			//calculate TF
			string feature = it->first;
			float TF = 0.00f;
			int d_count = std::count(tokens.begin(), tokens.end(), feature);
			if (d_count != 0) TF = 1 + log2(1 + log2(d_count));
			//get respective IDF and return TFIDF
			float IDF = log2(((float)(1 + this->documents_n)) / this->cache_IDFs[feature]);
			it->second = TF * IDF;
		}
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
