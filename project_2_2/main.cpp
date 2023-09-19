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
        size_t index = hash(key); //select hash based on lastname
        cout<< index<<endl;
        auto& bucket = hashtable[index];
        bucket.insert(key, value);
        bucket.print();
    }

    void getDisplayString() {

        for (auto bucket : hashtable) {
            for (auto pair = bucket.begin(); pair != bucket.end(); ++pair) {
                std::cout << "Key: " << pair->data.first << ", Value: " << pair->data.second.getDisplayString() << std::endl;
            }
        }
    }

    void removeAll(const K& key){
        keyTokens.clear();
        tokenize(key);

        size_t index = hash(keyTokens[0]); //select hash based on lastname
        auto& bucket = hashtable[index];
        bucket.removeAll(key);
    }

    vector<V> fetch(const K& key)  {
        vector<V> values;

        size_t index = hash(key);
        cout<< index<<endl;
        auto& bucket = hashtable[index];

        for (auto pair = bucket.begin(); pair != bucket.end(); pair = pair->next) {
            cout<<pair->data.first<<endl;
            if (pair->data.first == key) {
                cout<<"matched "<<pair->data.first <<endl;
                values.push_back(pair->data.second);
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
    Name name2("Alice", "Johnson", "Brown");
    PhoneEntry entry2(name2, "456 Elm St", phoneNumber2);
    dict.insert(entry2.getFormattedName(), entry2);

    // Fetch and display PhoneEntry instances by key.
    for (auto phoneEntry : dict.fetch(entry2.getFormattedName())) {
        cout << "Phone entry for 'John Doe Smith' is: " << phoneEntry.getDisplayString() << endl;
    }

    // Remove a PhoneEntry by key.
//    dict.removeAll(entry1.getFormattedName());

    // Fetch the removed PhoneEntry (should be empty).
//    for (auto value : dict.fetch(entry1.getFormattedName())) {
//        cout << "Value for 'John Doe Smith' is: " << value.getDisplayString() << endl;
//    }

    // Display the contents of the dictionary.
//    dict.getDisplayString();

    return 0;
}
