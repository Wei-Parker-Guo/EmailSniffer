#include "Tokenizer.h"

#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <algorithm>
#include <boost/tokenizer.hpp>
#include "StringOp.h"

void Tokenizer::construct_stopwords() {
    // Create an input filestream
    ifstream myFile(this->stopword_selection);

    // Make sure the file is open
    if (!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line;
    string val;

    // Read data, line by line ignoring "#" comments, produce verbose results
    printf("Loading stopwords from %s ... ", this->stopword_selection.c_str());
    while (std::getline(myFile, line))
    {
        if (!line.empty() && !(line.at(0) == '#')) {
            this->stopwords.push_back(line);
        }
    }
    printf("done.\n");
}

//constructor specifying the stopwords we are using
Tokenizer::Tokenizer(const string stopword_selection) {
	this->stopword_selection = stopword_selection;
	this->construct_stopwords();
}

//method to return a text's tokenized list tl with stopwords removed
void Tokenizer::tokenize_with_stopwords_rm(const string txt, vector<string>& tl) {
    using namespace boost;
    tl.clear();
    //to lower case for all
    string p_txt = txt;
    std::transform(p_txt.begin(), p_txt.end(), p_txt.begin(),
        [](unsigned char c) { return std::tolower(c); });
    //get raw tokens
    tokenizer<> tok(p_txt);
    //remove stopwords and store to output on the run
    for (tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
        string s(*beg);
        s = trim(s, ",:;.\n"); //trim marks
        //check if in stopwords
        if (std::find(this->stopwords.begin(), this->stopwords.end(), s) != this->stopwords.end()) {
            continue;
        } //find
        else {
            tl.push_back(s);
        } //not find
    }
}
