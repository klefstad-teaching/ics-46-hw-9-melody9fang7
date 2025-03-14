#include "ladder.h"
#include <unordered_set>

using namespace std;

void error(string word1, string word2, string msg){
    cout << word1 << word2 << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size(), len2 = str2.size();
    
    if (abs(len1 - len2) > d) return false; 

    if (len1 == len2) {
        int diff = 0;
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) diff++;
            if (diff > d) return false;
        }
        return diff <= d;
    }

    if (len1 > len2) return is_adjacent(str2, str1); 

    for (int i = 0; i < len2; i++) {
        if (str1 == str2.substr(0, i) + str2.substr(i + 1)) return true;
        if (i + 1 < len1 && str2 == str2.substr(0, i) + str1.substr(i + 1)) return true;
}

    return false;
}
bool is_adjacent(const string& word1, const string& word2){
    if(abs(int(word1.size() - word2.size())) > 1){
        return false;
    }else{
        return edit_distance_within(word1, word2, 1);
    }
    return false;
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) return {};
    if(begin_word == end_word) return {};
    set<string> visited;
    queue<vector<string>> ladder_queue;
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string& last_word = ladder.back();

        for(auto word: word_list){
            if(!is_adjacent(word, last_word) || word == last_word || visited.find(word) != visited.end()){
                continue;
            }else if (word == end_word){
                ladder.push_back(word);
                return ladder;
            }

            if (visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file){
        error("", "", "could not open file");
    }
    string word;
    while (file >> word){
        word_list.insert(word);
    }
    file.close();

}
void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }else{
        cout << "Word ladder found: ";
        for (auto s: ladder){
            cout << s << " ";
        }
        cout << endl;
    }
}
void verify_word_ladder(){
    string startword;
    cout << "enter your starting word" << endl;
    cin >> startword;
    cout << "enter your ending word" << endl;
    string endword;
    cin >> endword;
    vector<string> word_ladder;
    set<string> dict;
    load_words(dict, "src/words.txt");
    word_ladder = generate_word_ladder(startword, endword, dict);
    print_word_ladder(word_ladder);
    return;
}
