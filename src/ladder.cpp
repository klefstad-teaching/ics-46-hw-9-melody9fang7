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
    if (word_list.find(end_word) == word_list.end()) return {};

    set<string> dict(word_list.begin(), word_list.end());
    set<string> visited;
    queue<vector<string>> ladder_queue;
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> local_visited;

        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();

            for (int j = 0; j < int(last_word.size()); j++) {
                string temp_word = last_word;
                for (char c = 'a'; c <= 'z'; c++) {
                    temp_word[j] = c;
                    if (temp_word == last_word) continue;

                    if (temp_word == end_word) {
                        ladder.push_back(temp_word);
                        return ladder;
                    }

                    if (dict.find(temp_word) != dict.end() && visited.find(temp_word) == visited.end()) {
                        local_visited.insert(temp_word);
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(temp_word);
                        ladder_queue.push(new_ladder);
                    }
                }
            }
        }

        for (const auto& w : local_visited){
            visited.insert(w);
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
        error("", "", "No word ladder found.");
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
