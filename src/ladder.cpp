#include "ladder.h"
void error(string word1, string word2, string msg){
    cout << word1 << word2 << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (abs(int(str1.size() - str2.size())) > 1) return false;
    if (abs(int(str1.size() - str2.size())) == 0) {
        int diff = 0;
        for (int i = 0; i < int(str1.size()); i++) {
            if (str1[i] != str2[i]) {
                diff++;
            }
        }
        return diff <= d;
    }
    if (abs(int(str1.size() - str2.size())) == 1) {
        if(str1.size() > str2.size()){
            for (int i = 0; i < int(str1.size()); i++) {
                string new_str = str1.substr(0, i) + str1.substr(i + 1);
                if (new_str == str2) {
                    return true;
                }
            }
        }else{
            for (int i = 0; i < int(str2.size()); i++) {
                string new_str = str2.substr(0, i) + str2.substr(i + 1);
                if (new_str == str1) {
                    return true;
                }
            }
        }

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
    if (begin_word == end_word) return {};
     if (word_list.find(end_word) == word_list.end()) return {}; // If end_word is not in dictionary, no ladder

    queue<vector<string>> ladder_queue; // BFS queue
    set<string> visited;      // Track visited words

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> level_visited; 

        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();

            for (const auto& word : word_list) {
                if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) return new_ladder;

                    ladder_queue.push(new_ladder);
                    level_visited.insert(word);
                    
                }
            }
        }

        for (const auto& w : level_visited) visited.insert(w);
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
    if(startword == endword){
        error("", "", "words are the same");
        return;
    }
    word_ladder = generate_word_ladder(startword, endword, dict);
    print_word_ladder(word_ladder);
}
