#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>

using namespace std;


template <typename K, typename V>
class LinkedList {
private:
    struct Node {
        std::pair<K, V> data;
        Node* next;

        Node(const K& key, const V& value) : data(key, value), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(const K& key, const V& value) {
        Node* newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
    }

    bool contains(const K& key) const {
        Node* current = head;
        while (current) {
            if (current->data.first == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void print() const {
        Node* current = head;
        while (current) {
//            std::cout << "Key: " << current->data.first << ", Value: " << current->data.second << std::endl;
            current = current->next;
        }

        cout<<endl<<endl<<endl;
    }


    Node* begin() const {
        return head;
    }

    Node* end() const {
        return nullptr;
    }

    void removeAll(const K& key) { // deletes all values associated with a key
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data.first == key) {
                // Remove the node with the matching key
                if (previous) {
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                } else {
                    // If the node to be removed is the head
                    head = current->next;
                    delete current;
                    current = head;
                }
            } else {
                // Move to the next node
                previous = current;
                current = current->next;
            }
        }
    }


};


template<typename K, typename V, size_t N = 8>
class Dictionary {
private:
    vector<LinkedList<K, V>> hashtable;
    vector<string> keyTokens;

    size_t hash(const std::string& fullName) const {
        int sum = 0;
        for (char c : fullName) {
            sum += static_cast<int>(c);
        }
//        cout<<fullName<<"  "<<sum<<"  "<<sum%N<<endl;
        return sum % N;
    }

public:
    Dictionary() {
        hashtable.resize(N);
    }

    void tokenize(const K& fullName) {
        istringstream iss(fullName);

        std::string token;
        while (std::getline(iss, token, ' ')) {
            keyTokens.push_back(token);
        }
    }

    void insert(const K& key, const V& value) {

        keyTokens.clear();
        tokenize(key);

        size_t index = hash(keyTokens[0]); //select hash based on firstname
//        cout<< index<<endl;
        auto& bucket = hashtable[index];
        bucket.insert(key, value);

        bucket.print();

        if (keyTokens.size() > 2) {
            index = hash(keyTokens[2]); //select hash based on lastname
            bucket = hashtable[index];
            bucket.insert(key, value);

            index = hash(keyTokens[2] + keyTokens[0]); //select hash based on lastname + firstname
            bucket = hashtable[index];
            bucket.insert(key, value);
        }
    }

    void getDisplayString() {

        for (auto bucket : hashtable) {
            for (auto pair = bucket.begin(); pair != bucket.end(); ++pair) {
                std::cout << "Key: " << pair->data.first << ", Value: " << pair->data.second << std::endl;
            }
        }
    }

    void removeAll(const K& key){
        keyTokens.clear();
        tokenize(key);

        size_t index = hash(keyTokens[0]); //select hash based on firstname
        auto& bucket = hashtable[index];
        bucket.removeAll(key);
    }

//    void getDisplayString() const {
//
//        for (const auto& bucket : hashtable) {
//            for (const auto& pair : bucket) {
//                std::cout << "Key: " << pair.data.first << ", Value: " << pair.data.second << std::endl;
//            }
//        }
//    }


    vector<V> fetch(const K& key) const {
        vector<V> values;
        size_t index = hash(key);
        const auto& bucket = hashtable[index];

        for (auto pair = bucket.begin(); pair != bucket.end(); pair = pair->next) {
            if (pair->data.first == key) {
//                value = pair->data.second;
//                return true;
                cout<<"matched"<<endl;
                values.push_back(pair->data.second);
            }
        }

        return values;
    }

    [[deprecated]] void remove(const K& key) {
        //todo implement remove
    }
};

int main() {
    Dictionary<string, string> dict;
    dict.insert("one", "one");


    dict.insert("two", "two");
    dict.insert("two", "three");

    dict.insert("four", "three");

    dict.insert("five", "three");
    dict.insert("six", "three");
    dict.insert("ajfljhatoiuqewrhopwerhj", "three");
//    dict.insert("two", 4);
//    dict.insert("three", 3);



    for(auto value: dict.fetch("two")){
        cout << "Value for 'two' is: " << value << endl;
    }

    dict.removeAll("two");
    cout<<"deleted"<<endl;

    for(auto value: dict.fetch("two")){
        cout << "Value for 'two' is: " << value << endl;
    }

    cout<<endl<<endl;

    dict.getDisplayString();
//    vector<string> bucket = dict.fetch("two");
//
//    for (auto pair = bucket.begin(); pair != bucket.end(); pair = pair->next) {
//
//    }

//    for(auto& value: dict.fetch("one")){
//        cout << "Value for 'one' is: " << value << endl;
//    }


//    if (dict.contains("four")) {
//        cout << "'four' is in the dictionary." << endl;
//    } else {
//        cout << "'four' is not in the dictionary." << endl;
//    }

//    dict.getDisplayString();
//    dict.remove("two");

//    if (!dict.contains("two")) {
//        cout << "'two' has been removed from the dictionary." << endl;
//    }

    return 0;
}
