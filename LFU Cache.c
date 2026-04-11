#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LFUCache {
    int capacity, minFreq;
    unordered_map<int, pair<int, int>> keyValFreq; // key -> {value, freq}
    unordered_map<int, list<int>> freqList;        // freq -> keys
    unordered_map<int, list<int>::iterator> pos;   // key -> position in list

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        if (keyValFreq.find(key) == keyValFreq.end())
            return -1;

        int val = keyValFreq[key].first;
        int freq = keyValFreq[key].second;

        // Remove from old freq list
        freqList[freq].erase(pos[key]);

        // If this was the only key with minFreq
        if (freqList[freq].empty() && freq == minFreq)
            minFreq++;

        // Add to new freq list
        freq++;
        keyValFreq[key].second = freq;
        freqList[freq].push_front(key);
        pos[key] = freqList[freq].begin();

        return val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyValFreq.find(key) != keyValFreq.end()) {
            keyValFreq[key].first = value;
            get(key); // update frequency
            return;
        }

        if (keyValFreq.size() == capacity) {
            int lfuKey = freqList[minFreq].back();
            freqList[minFreq].pop_back();
            keyValFreq.erase(lfuKey);
            pos.erase(lfuKey);
        }

        keyValFreq[key] = {value, 1};
        freqList[1].push_front(key);
        pos[key] = freqList[1].begin();
        minFreq = 1;
    }
};

int main() {
    LFUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // 1
    cache.put(3, 3);              // evicts key 2
    cout << cache.get(2) << endl; // -1
    cout << cache.get(3) << endl; // 3

    return 0;
}
