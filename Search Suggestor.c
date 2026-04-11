#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    vector<string> sentences;
};

class AutocompleteSystem {
private:
    TrieNode* root;
    unordered_map<string, int> freq;
    string current;

public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new TrieNode();
        current = "";

        for (int i = 0; i < sentences.size(); i++) {
            freq[sentences[i]] = times[i];
            insert(sentences[i]);
        }
    }

    void insert(string sentence) {
        TrieNode* node = root;
        for (char c : sentence) {
            if (!node->children[c])
                node->children[c] = new TrieNode();
            node = node->children[c];
            node->sentences.push_back(sentence);
        }
    }

    vector<string> input(char c) {
        if (c == '#') {
            freq[current]++;
            insert(current);
            current = "";
            return {};
        }

        current += c;
        TrieNode* node = root;

        for (char ch : current) {
            if (!node->children[ch])
                return {};
            node = node->children[ch];
        }

        vector<string> results = node->sentences;

        sort(results.begin(), results.end(), [&](string &a, string &b) {
            if (freq[a] == freq[b])
                return a < b;
            return freq[a] > freq[b];
        });

        if (results.size() > 3)
            results.resize(3);

        return results;
    }
};

int main() {
    vector<string> sentences = {"i love you", "island", "i love coding"};
    vector<int> times = {5, 3, 2};

    AutocompleteSystem system(sentences, times);

    vector<string> res;

    res = system.input('i');
    for (auto &s : res) cout << s << " ";
    cout << endl;

    res = system.input(' ');
    for (auto &s : res) cout << s << " ";
    cout << endl;

    return 0;
}
