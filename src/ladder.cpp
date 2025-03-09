#include "ladder.h"
void error(string word1, string word2, string msg){
    cout << word1 << word2 << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int diff = 0;
    for(int i = 0; i < min(str1.size(), str2.size()); i++){
        if (str1[i] != str2[i]){
            diff++;
        }
    }
    if(diff == 0){
        return true;
    }else if (diff == d && str1.size() == str2.size()){
        return true;
    }
}
bool is_adjacent(const string& word1, const string& word2){
    if(abs(word1.size() - word2.size()) > 1){
        return false;
    }else{
        return edit_distance_within(word1, word2, 1);
    }
    return false;
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push([begin_word]);
    set<string> visited;
    visited.insert(begin_word);
    while(!ladder_queue.empty()){
        ladder = ladder_queue.pop();
        last_word = ladder_queue.back();
        for(word in word_list):
        if(is_adjacent(last_word, word)){
            if (!visited.check(word)){
                visited.insert(word);
                queue<vector<string>> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word){
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    vector<string> empty;
    return empty;
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
    for (auto s: ladder){
        cout << s << " ";
    }
}
void verify_word_ladder(){
    string startword;
    string endword;
    vector<string> word_ladder;
    set<string> dict;
    load_words(dict, "words.txt");
    if(startword == endword){
        error("", "", "words are the same");
        return;
    }
    word_ladder = generate_word_ladder(startword, endword, dict);

}
