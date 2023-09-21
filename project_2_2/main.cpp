#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>

using namespace std;

class Name {
public:
    Name(const std::string& first, const std::string& middle, const std::string& last) {
        setFirstName(first);
        setMiddleName(middle);
        setLastName(last);
    }

    void setFirstName(const std::string& first) {
        firstName = canonicalize(first);
    }

    void setMiddleName(const std::string& middle) {
        middleName = canonicalize(middle);
    }

    void setLastName(const std::string& last) {
        lastName = canonicalize(last);
    }

    std::string getFormattedName() const {
        return lastName + " " + middleName.substr(0, 1) + " " + firstName;
    }

private:
    std::string firstName;
    std::string middleName;
    std::string lastName;

    std::string canonicalize(const std::string& name) {
        std::string result = name;
        // Remove leading and trailing spaces
        while (!result.empty() && std::isspace(result.front())) {
            result.erase(result.begin());
        }
        while (!result.empty() && std::isspace(result.back())) {
            result.pop_back();
        }
        // Uppercase first character, lowercase the rest
        if (!result.empty()) {
            result[0] = std::toupper(result[0]);
            for (size_t i = 1; i < result.length(); ++i) {
                result[i] = std::tolower(result[i]);
            }
        }
        return result;
    }
};

class AreaCode {
public:
    AreaCode(const std::string& code) : code(code) {}

    std::string getCode() const {
        return code;
    }

private:
    std::string code;
};

class PhoneNumber {
public:
    PhoneNumber(const AreaCode& areaCode, const std::string& number) : areaCode(areaCode), number(number) {}

    std::string getFormattedNumber() const {
        return areaCode.getCode() + "-" + number;
    }

private:
    AreaCode areaCode;
    std::string number;
};

class PhoneEntry {
public:
    PhoneEntry(const Name& name, const std::string& address, const PhoneNumber& phoneNumber)
            : name(name), address(address), phoneNumber(phoneNumber) {}

    std::string getFormattedName() const {
        return name.getFormattedName();
    }

    std::string getPhoneNumber() const {
        return phoneNumber.getFormattedNumber();
    }

    std::string getDisplayString() const {
        return "Name: " + name.getFormattedName() + ", Address: " + address + ", Phone: " + phoneNumber.getFormattedNumber();
    }

private:
    Name name;
    std::string address;
    PhoneNumber phoneNumber;
};


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

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << "Key: " << current->data.first << std::endl;
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

    void deleteAll(const K& key) { // deletes all values associated with a key
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

    size_t hash(const std::string& key) const {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % N;
    }

public:
    Dictionary() {
        hashtable.resize(N);

        for (size_t i = 0; i < N; ++i) {
            hashtable[i] = LinkedList<K, V>();
        }
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

        size_t index = hash(keyTokens[0]); //select hash based on lastname

        auto& bucket = hashtable[index];
        bucket.insert(keyTokens[0], value);

        if (keyTokens.size() > 2) {
            index = hash(keyTokens[2]); //select hash based on firstname
            auto& bucket2 = hashtable[index];
            bucket2.insert(keyTokens[2], value);

            index = hash(keyTokens[0] +", "+ keyTokens[2]); //select hash based on "lastname, firstname"
            auto& bucket3 = hashtable[index];
            bucket3.insert(keyTokens[0] +", "+ keyTokens[2], value);
        }
    }


    void getDisplayString() {
        for (size_t i = 0; i < N; ++i) {
            auto& bucket = hashtable[i];
            auto current = bucket.begin();

            while (current != nullptr) {
                std::cout << "Key: " << current->data.first << ", Value: " << current->data.second.getDisplayString() << std::endl;
                current = current->next;
            }
        }
    }

    void deleteAll(const K& key) {
        keyTokens.clear();
        tokenize(key);

        if (!keyTokens.empty()) {
            size_t index = hash(keyTokens[0]); // select hash based on lastname
            auto& bucket = hashtable[index];
            bucket.deleteAll(keyTokens[0]);
        }

        if (keyTokens.size() > 2) {
            size_t index = hash(keyTokens[2]); // select hash based on firstname
            auto& bucket2 = hashtable[index];
            bucket2.deleteAll(keyTokens[2]);

            size_t index3 = hash(keyTokens[0] + ", " + keyTokens[2]); // select hash based on "lastname, firstname"
            auto& bucket3 = hashtable[index3];
            bucket3.deleteAll(keyTokens[0] + ", " + keyTokens[2]);
        }
    }

    vector<V> fetch(const K& key)  {
        vector<V> values;

        keyTokens.clear();
        tokenize(key);

        size_t index = hash(keyTokens[0]); //select hash based on lastname
        auto& bucket = hashtable[index];

        for (auto pair = bucket.begin(); pair != bucket.end(); pair = pair->next) {
            if (pair->data.first == keyTokens[0]) {
                values.push_back(pair->data.second);
            }
        }

        if (keyTokens.size() > 2) {
            index = hash(keyTokens[2]); //select hash based on lastname
            auto& bucket2 = hashtable[index];
            for (auto pair = bucket2.begin(); pair != bucket2.end(); pair = pair->next) {
                if (pair->data.first == keyTokens[2]) {
                    values.push_back(pair->data.second);
                }
            }

            index = hash(keyTokens[0] +", "+ keyTokens[2]); //select hash based on "lastname, firstname"
            auto& bucket3 = hashtable[index];
            for (auto pair = bucket3.begin(); pair != bucket3.end(); pair = pair->next) {
                if (pair->data.first == keyTokens[0] +", "+ keyTokens[2]) {
                    values.push_back(pair->data.second);
                }
            }
        }

        return values;
    }
};

int main() {

    Dictionary<string, PhoneEntry> dict;

    // Create instances of PhoneEntry and add them to the dictionary.
    AreaCode areaCode1("123");
    PhoneNumber phoneNumber1(areaCode1, "456-7890");
    Name name1("firstname", "middlename", "lastname");
    PhoneEntry entry1(name1, "123 Main St", phoneNumber1);

    dict.insert(entry1.getFormattedName(), entry1);

    AreaCode areaCode2("456");
    PhoneNumber phoneNumber2(areaCode2, "789-1234");
    Name name2("Alice", "Johnson", "lastname");
    PhoneEntry entry2(name2, "456 Elm St", phoneNumber2);
    dict.insert(entry2.getFormattedName(), entry2);

    cout<<endl<<endl<<endl;
    cout<<"Output of fetch method. Showing all output that matched lastname or firstname or lastname+firstname";
    cout<<endl<<endl;
    // Fetch and display PhoneEntry instances by matching lastname or firstname or lastname, firstname
    for (auto phoneEntry : dict.fetch(entry1.getFormattedName())) {
        cout << "Phone entry for \'"<< entry1.getFormattedName() <<"\' is: " << phoneEntry.getDisplayString() << endl;
    }

    cout<<endl<<endl<<endl;
    cout<<"Output for getDisplaystring";
    cout<<endl<<endl;
    // Display the contents of the dictionary.
    dict.getDisplayString();

    // Remove all phoneentries for a name
    cout<<endl<<endl<<endl;
    cout<<"Deletion performed for lastname M firstname";
    dict.deleteAll(entry1.getFormattedName());

    cout<<endl<<endl<<endl;
    cout<<"Output of fetch method";
    cout<<endl<<endl;
    // Fetch and display PhoneEntry instances by matching lastname or firstname or lastname, firstname, prints nothing
    for (auto phoneEntry : dict.fetch(entry1.getFormattedName())) {
        cout << "Phone entry for \'"<< entry1.getFormattedName() <<"\' is: " << phoneEntry.getDisplayString() << endl;
    }

    cout<<endl<<endl<<endl;
    cout<<"Output of fetch method";
    cout<<endl<<endl;
    // Fetch and display PhoneEntry instances by matching lastname or firstname or lastname, firstname
    for (auto phoneEntry : dict.fetch(entry2.getFormattedName())) {
        cout << "Phone entry for \'"<< entry2.getFormattedName() <<"\' is: " << phoneEntry.getDisplayString() << endl;
    }

    cout<<endl<<endl<<endl;
    cout<<"Output for getDisplaystring";
    cout<<endl<<endl;
    // Display the contents of the dictionary.
    dict.getDisplayString();

    return 0;
}
