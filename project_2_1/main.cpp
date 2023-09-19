#include <iostream>
#include <string>

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

int main() {
    AreaCode areaCode("123");
    PhoneNumber phoneNumber(areaCode, "456-7890");
    Name name("John", "Doe", "Smith");
    PhoneEntry entry(name, "123 Main St", phoneNumber);

    AreaCode areaCode2("1232");
    PhoneNumber phoneNumber2(areaCode, "426-7892");
    Name name2("Paul", "Graham", "Smith");
    PhoneEntry entry2(name2, "1232 Main St", phoneNumber2);

    std::cout << "Formatted Name: " << entry.getFormattedName() << std::endl;
    std::cout << "Phone Number: " << entry.getPhoneNumber() << std::endl;
    std::cout << "Display String: " << entry.getDisplayString() << std::endl;
    std::cout<<std::endl;

    std::cout << "Formatted Name: " << entry2.getFormattedName() << std::endl;
    std::cout << "Phone Number: " << entry2.getPhoneNumber() << std::endl;
    std::cout << "Display String: " << entry2.getDisplayString() << std::endl;
    return 0;
}


