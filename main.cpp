#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "csvstream.h"
#include <map>
#include <set>
#include <cmath>
using namespace std;
using std::cout;

class Classifier
{
private:
    int total_post;
    int number_of_unique_words;
    set<string> all_unique;
    string all_words;
    set<string> unique_tags;
    map<string, int> tagFreq;
    map<pair<string, string>, int> my_map; //drives our classifier
    set<string> unique_string;
    //vector<int> tag_occurances;
    // int hold;
    // vector<pair<string, int>> tagFreq;
    /*int number_of_labels;
    int unique_posts; // the number of posts with label C that contain word w
    //not all of these should be ints so make sure to change
*/
public:
    //REQUIRES: str is a valid string
    //MODIFIES: N/A
    //EFFECT: returns a set containing all unique words in the input string
    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

    //REQUIRES: str is a valid string, str is a unique post
    //MODIFIES: all_words, total_posts
    //EFFECT: adds to our string of all_words, increases our total posts
    void merge_strings(const string &str) {
        all_words = all_words + str + " ";
        ++total_post;
    }

    //REQUIRES: N/A
    //MODIFIES: N/A
    //EFFECT: Returns the number of posts the classifier was trained on
    int get_total_posts() {
        return total_post;
    }

    //REQUIRES: all_words contains all words in a csv input
    //MODIFIES: number_of_unique_words
    //EFFECT: sets number_of_unique_words equal the size of the set containing
        //the csv input line.
    void totalUnique() {
        all_unique = unique_words(all_words);
        number_of_unique_words = all_unique.size();
    }

    //REQUIRES: N/A
    //MODIFIES: N/A
    //EFFECT: Returns the value for the private variable
        //number of unique words
    int getUniqueWords() {
        return number_of_unique_words;
    }

    //REQUIRES: A string input
    //MODIFIES: Unique_tags set.
    //EFFECT: Adds str to the unique_tags str
    void uniqueTags(const string &str) {
        unique_tags.insert(str);
    }

    //REQUIRES: N/A
    //MODIFIES: cout
    //EFFECT: prints tags and information for the debug option
    void printTags() {
        for (auto i : unique_tags) {
            cout << "  ";
            cout << i << ", " << tagFreq[i] << " examples, log-prior = ";
            cout << lnPofC(i) << '\n';
        }
    }

    //REQUIRES: Unique tags have been found, a valid map is being traversed
    //MODIFIES: N/A
    //EFFECT: Returns the number of occurances of a word in all posts by
        //searching each tag for the str input
    int wordPostOccurance(const string str/*, const map<pair<string, string>, int> &mp*/)
    {
        int w = 0; // occurances
        for (auto i : unique_tags)
        {
            auto key = make_pair(i, str); //SWITCHED...Check
            auto j = my_map.find(key);
            if (j != my_map.end()) {
            //TODO: What does find return if nothing is found?
                w += j->second;
            }
        }
        return w;
    }

    //REQUIRES: str is a valid string
    //MODIFIES: tagFreq
    //EFFECT: adds a tag to our map, if already found the frequency is increased
    void addOccurance(string str) {
        ++tagFreq[str];
    }
    
    //REQUIRES: N/A
    //MODIFIES: cout
    //EFFECT: outputs the tag frequency to the terminal
    void printTagFreq() {
        for (auto i : tagFreq) {
            cout << i.second << " ";
        }
    }
    
    //REQUIRES: Valid Map
    //MODIFIES: cout
    //Effect: prints data about map to the terminal
    void printMapData(/*const map<pair<string, string>, int> &mp*/) {
        //set<pair<string,string>> data;
        for (auto i : my_map) {
            cout << "  " << i.first.first << ":" << i.first.second;
            cout << ", count = " << i.second;
            cout << ", log-likelihood = ";
            cout << lnPofWgivenC(/*mp*/i.first.first, i.first.second) << '\n';
        }
        cout << '\n';
    }
    

    //REQUIRES: a valid map in the input
    //MODIFIES: string inputs into a pair
    //EFFECT: returns frequency for word for an inputted tag
    double posts_c_and_w(/*const map<pair<string, string>, int> &mp,*/ 
                       const string key1, const string key2) {
        auto i = my_map.find(make_pair(key2, key1)); //SWITCHED... CHECK
        if (i == my_map.end()) {return -1;}
        //cout << i->second;
        return i->second;
    }
    
    //REQUIRES: str is a valid key contained within tagFreq
    //MODIFIES: N/A
    //EFFECT: Returns the ln(P(C)) for a given key as an integer
    double lnPofC (string str) {
        if (tagFreq.find(str) == tagFreq.end()) {
            assert(false);
        }

        double total = 0;
        double Ctotal = tagFreq[str];

        for (auto i : tagFreq) {
            total += i.second;
        }
        double hold = Ctotal/total;
        hold = log(hold);
        //cout << "lnPofC: " << hold << endl;
        return hold;
    }
    
    //REQUIRES: a valid map is passed into the function
    //Modifies: n/a
    //EFFECT: Traverse the map, and the private map of tag freq
        //in order to find ln(P(w)/C)
    double lnPofWgivenC(/*const map<pair<string, string>, int> &mp,*/
                       const string key1, const string key2) {
        double Occurances = wordPostOccurance(key2); //FIX
        double candw = posts_c_and_w(key2, key1); //FIX
        if(candw == -1 && Occurances == 0){
            double hold = 1.0 / total_post;  
            hold = log(hold);
            //cout << "op1: " << hold << endl;
            return hold;
        }
        if(candw == -1 && Occurances != 0){ 
            double hold2 = Occurances / total_post;
            hold2 = log(hold2);
            //cout << "op2: " << hold2 << endl;
            return hold2;
        }
        double Ctotal = tagFreq[key1]; //FIX
        double hold3 = candw/Ctotal;
        hold3 = log(hold3);
        //cout << "op3: " << hold3 << endl;
        return hold3;
    }

    //REQUIRES: mp is a trained map, tagFreq is trained, a set of unique words
    //MODIFIES: N/A
    //EFFECT: Makes a prediction for each tag, returns a pair of the tag,
        //and its log-likelyhood
    pair<string, double> prediction(/*const map<pair<string, string>,
                                    int> &mp,*/ set<string> &test_words) {
        vector<double> loglike;
        vector<string> tags;
        for (auto i : unique_tags) {
            double total = 0.0;
            total += lnPofC(i);
            for (auto j : test_words) {
                total += lnPofWgivenC(i, j); 
            }
            loglike.push_back(total), tags.push_back(i);
        }
        size_t highest_index = 0;
        double highest = loglike[0];
        for (size_t i = 1; i < loglike.size(); i++) {
            if (loglike[i] > highest) {
                highest = loglike[i], highest_index = i;
            }
            if (loglike[i] == highest) {
                if (tags[highest_index].compare(tags[i]) > 0) {
                    highest = loglike[i], highest_index = i;
                }
            }
        }
        return make_pair(tags[highest_index], highest);
    }

    //REQUIRES: Debug = true
    //MODIFIES: N/A
    //EFFECT: Cout
    void debugPrint2() {
        cout << "vocabulary size = " << getUniqueWords() << '\n'
        << '\n' << "classes:" << '\n';
        printTags();
        cout << "classifier parameters:" << '\n';
    }

    void addUniqueWordsMap(/*const set<string> &w,*/ const string &lb) {
        for (auto i: unique_string) {
            ++my_map[{lb, i}];
        }
    }

    void setUnique_String(const string &content) {
        merge_strings(content);
        unique_string = unique_words(content);
    }
};

int main(int argc, char *argv[]) {
    cout.precision(3);
    bool debug = false;
    Classifier classifier = Classifier();
    string filename = string(argv[1]);
    csvstream csvin(filename);
    map<string, string> row;
    string errorMessage = "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]";
    if (argc != 3 && argc != 4) {
        cout << errorMessage << endl;
        return 1;
    }
    if (argc == 4) {
        if (string(argv[3]) == "--debug") { debug = true; }
        else { cout << errorMessage << endl; return 1; }
    }
    if (debug) { cout << "training data:" << '\n'; }
    while (csvin >> row) {
        string content, label;
        for (auto &col : row) {
            if (col.first == "content") {
                content = col.second, classifier.setUnique_String(content);
            }
            if (col.first == "tag") {
                    label = col.second;
                    classifier.uniqueTags(label), classifier.addOccurance(label);
                    classifier.addUniqueWordsMap(label);
                    if (debug) { cout << "  label = " << label
                        << ", content = " << content << '\n';
                    }
            }
        }
    }
    classifier.totalUnique();
    string testfile = string(argv[2]);
    csvstream csvout(testfile);
    map<string, string> row2;
    set<string> unique_string_output;
    cout << "trained on " << classifier.get_total_posts() << " examples" << '\n';
    if (!debug) { cout << '\n'; }
    if (debug) { classifier.debugPrint2(), classifier.printMapData(); }
    cout << "test data:" << '\n';
    int total = 0;
    int CorrectTotal = 0;
    while(csvout>>row2){
        string content, label;
         for (auto &col2 : row2) {
            if(col2.first == "content") {
                content = col2.second;
                unique_string_output = classifier.unique_words(content);
            }
            if(col2.first == "tag"){
                label = col2.second;
                auto predict = classifier.prediction(unique_string_output);
                cout << "  correct = " << label << ", predicted = " << predict.first
                << ", log-probability score = " << predict.second << '\n'
                << "  content = " << content << '\n' << '\n';
                if (label == predict.first) { CorrectTotal++; }
                total++;
            }
         }
    }
    cout << "performance: " << CorrectTotal << " / " << total <<
    " posts predicted correctly" << '\n';
}