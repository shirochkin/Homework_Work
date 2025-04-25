#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <map>
#include <vector>
#include <windows.h>
#include <regex>
#include <typeinfo>
#include <exception>

//������ �������� ����� ����� �����:
std::array <std::string, 5> typeString = { "section", "variable", "comment", "space", "scum" };

class invalid_section_name : public std::exception {
public:
    const char* what() const override {
        return "Wrong name of section!";
    }
};

class invalid_variable_name : public std::exception {
public:
    const char* what() const override {
        return "Wrong name of variable!";
    }
};
//������� ����� �������� �����:
std::regex sectionPattern{ R"(\[.+\])" };
std::regex namePattern{ "[a-zA-Z�-��-�0-9_]+" };
std::regex varPattern{ "[a-zA-Z�-��-�0-9_]+\\s*=[^=^;]*;*.*" };
std::regex intPattern{ "[0-9]+" };
std::regex floatPattern{ "[0-9]+\.[0-9]+" };
std::regex stringPattern{ "[^=^;]*" };
std::regex commentPattern{ ";.*" };
std::regex spacePattern{ "\\s*" };

//����� ������
class Section {
public:
    std::string name;
    //���������� ��� �������� ��� ���-�������� ����� int, float � string
    std::map<std::string, int> int_variables;
    std::map<std::string, float> float_variables;
    std::map<std::string, std::string> string_variables;
    //�����������
    Section(std::string s) : name{ s } {};

    //������� ������ �������� Int
    void printInt() {
        std::cout << "Integer values:\n";
        for (std::pair<std::string, int> p : int_variables) {
            std::cout << "varName: " << p.first << "value: " << p.second;
        }
    }

    //������� ������ �������� Float
    void printFloat() {
        std::cout << "Float values:\n";
        for (std::pair<std::string, float> p : float_variables) {
            std::cout << "varName: " << p.first << "value: " << p.second;
        }
    }

    //������� ������ �������� String
    void printString() {
        std::cout << "String values:\n";
        for (std::pair<std::string, std::string> p : string_variables) {
            std::cout << "varName: " << p.first << "value: " << p.second;
        }
    }

    bool operator= (std::string& s) {
        return s == this->name;
    }

};


class parser {
public:
    //������ ������, ���������� �� �����
    std::vector<Section> sections;
    //������ �����, ���������� �� �����
    std::vector<std::string> strings;
    //������ ����� ����� �����
    std::vector<std::string> types;

    //������� ��������� ������ �� �����
    void receiveData(std::string name) {

        std::ifstream reader(name, std::ios::in);
        std::string str;

        //��������� ������ ������ � ��������� � ������ strings
        while (!reader.eof()) {
            std::getline(reader, str);
            strings.push_back(str);
        }

        //�������� ������ ������� types ��� ���������� �����
        types.resize(strings.size());

        //���������� ��� ������ ������
        for (int i = 0; i < types.size(); i++) {
            if (std::regex_match(strings[i], sectionPattern)) {
                types[i] = typeString[0];
            }

            else if (std::regex_match(strings[i], varPattern)) {
                types[i] = typeString[1];
            }

            else if (std::regex_match(strings[i], commentPattern)) {
                types[i] = typeString[2];
            }

            else if (std::regex_match(strings[i], spacePattern)) {
                types[i] = typeString[3];
            }

            else {
                types[i] = typeString[4];
                //� ������ ������������ ������ �������� �� ���� ������������
                std::cout << "String number " << i+1 << " is incorrect." << std::endl;
            }
        }

        
        //��������� ������ � �������
        //���� ��������� ��������� ������, ��������� �� � ������ ������
        for (int i = 0; i < types.size();) {
             if (i < types.size() && types[i] == typeString[0]) {
                 //std::cout << "New section! " << strings[i] << std::endl;
                 //�������� ��������� � ������� ������ �� �����
                 std::string sectionName = strings[i];
                 int index = sectionName.find("[");
                 sectionName.erase(0, index + 1);
                 index = sectionName.find("]");
                 sectionName.erase(index);
                 Section section(sectionName);
                 bool containSection{ 0 };
                 //��������� �� ������� ������. ���� ��� ��� ������� � ������� ������, ��������� �� ��� ������. ���� ��� - ������� �����.
                 Section* currentSection{ nullptr };
                 for (int j = 0; j < sections.size(); j++) {
                     if (sections[j].name == sectionName) {
                         containSection = 1;
                         currentSection = &sections[j];
                         //std::cout << "Same sections: " << sections[j].name << " " << currentSection->name;
                     }
                 }

                 if (containSection == 0) {
                     Section s(sectionName);
                     sections.push_back(s);
                     currentSection = &sections[sections.size() - 1];
                 }

                 //std::cout << "Current section: " << currentSection->name << std::endl;
                 //std::cout << "sectionName: " << sectionName << std::endl;
                 ++i;

                 //���� � ��������� �� ������� ������� ������ � �����������, ���� �� ������ �� ��������� ������
                while (i < types.size() && types[i] != typeString[0]) {
                    if (types[i] == typeString[1]) {
                        //std::cout << "Variable is found! Section: " << currentSection->name << std::endl;
                        //std::cout << "string: " << strings[i] << std::endl;

                        //���� ����� ������ � ����������, ��������� �� �� ��� � �������� � ������� string
                        std::pair<std::string, std::string> p = extractValues(strings[i]);
                        //std::cout << "first: " << p.first << " second: " << p.second << std::endl;
                        bool containVariable{ 0 };

                        //��������� �������� ���������� �� ������������ �������� ����� � ��������� ���� � ��������������� ���������. ���� ���� � ����� ������ ��� �������, �������������� ��������.
                        if (std::regex_match(p.second, intPattern)) {
                            //std::cout << " Integer is found!. Section: " << currentSection->name << std::endl;
                            std::pair<std::string, int> p2 = get_int(p);
                            
                                for (std::pair<std::string, int> p1 : currentSection->int_variables) {
                                    if (p1.first == p.first) {
                                        containVariable = 1;
                                    }
                                }
                                if (containVariable == 0) {
                                    currentSection->int_variables.insert(p2);
                                }
                                else {
                                    currentSection->int_variables[p2.first] = p2.second;
                                }
                                
                            }
                        else if (std::regex_match(p.second, floatPattern)) {
                           // std::cout << " Float is found!. Section: " << currentSection->name<<  std::endl;
                            std::pair<std::string, float> p2 = get_float(p);

                                for (std::pair<std::string, float> p1 : currentSection->float_variables) {
                                    if (p1.first == p.first) {
                                        containVariable = 1;
                                    }
                                }
                            if (containVariable == 0) {
                                currentSection->float_variables.insert(p2);
                            }
                            else {
                                currentSection->float_variables[p2.first] = p2.second;
                            }
                        }

                        else if (std::regex_match(p.second, stringPattern)) {
                            //std::cout << " String is found! Section: " << currentSection->name<< std::endl;
                            for (std::pair<std::string, std::string> p1 : currentSection->string_variables) {
                                if (p1.first == p.first) {
                                    containVariable = 1;
                                }
                            }
                            if (containVariable == 0) {
                                currentSection->string_variables.insert(p);
                            }
                            else {
                                currentSection->string_variables[p.first] = p.second;
                            }
                        }
                        ++i;
                    }
                    else {
                        ++i;
                    }
                }
  
                    }
             else {
                 ++i;
             }
                
         }
    }

    //������� ��������� ������ �� ��������� � ������ � ��������� ����������
    std::pair<std::string, std::string> extractValues(std::string s) {
        int i{ 0 };

        //���� ���� = � �������� ����� �����, ������� ������� �� �����
        int index = s.find("=");
        std::string left = s.substr(0, index);
        //std::cout << "Initial left: " << left << std::endl;
        while (left[i] == ' ' || left[i] == '\t') {
            ++i;
        }
        left.erase(0, i);

        i = 0;
        while (left[left.size() - 1 - i] == ' ' || left[left.size() - 1 - i] == '\t') {
            ++i;
        }
        left.erase(left.size() - i, i);
        //std::cout << "Left after erase: " << left << std::endl;

        //�������� ������ �����, ������� ����������� ��� �������, ������� ������� �� �����
        std::string right{};
        if (s.size() > index + 1) {
            right = s.substr(index + 1, s.size() - 1);
            //std::cout << "Initial right: " << right << std::endl;
            for (int k = 0; k < right.size(); k++) {
                if (right[k] == ';') {
                    //std::wcout << "Comment is found!" << std::endl;
                    right.erase(k);
                }
            }
            i = 0;
            while (right[i] == ' ' || right[i] == '\t') {
                ++i;
            }
            right.erase(0, i);



            i = 0;
            while (right[right.size() - 1 - i] == ' ' || right[right.size() - 1 - i] == '\t') {
                ++i;
            }
            right.erase(right.size() - i, i);
        }        

        //std::cout << "left: " << left << " right: " << right << std::endl;

       // std::cout << "Right after erase: " << right << std::endl;
        std::pair<std::string, std::string> p{ left, right };
        
        return p;
    }

    //������� �������������� ���� �� ��������� string � ���� �� ��������� int
    std::pair<std::string, int> get_int(std::pair<std::string, std::string>& p) {
            int a = stoi(p.second);
            return std::make_pair(p.first, a);
    }

    //������� �������������� ���� �� ��������� string � ���� �� ��������� float
    std::pair<std::string, float> get_float(std::pair<std::string, std::string>& p) {
        float a = stof(p.second);
        return std::make_pair(p.first, a);
    }


//������ ������� ��������� �������� ��������� ���������� � ��������� ������
    template<typename T>
    T get_value(std::string sectionName, std::string varName) {
        int index{};
        bool contains{};
        try {
            for (int i = 0; i < sections.size(); i++) {
                if (sections[i].name == sectionName) {
                    index = i;
                    contains = 1;
                    break;
                }
            }
            if (contains == 0) {
                throw invalid_section_name();

            }

            if (typeid(T) == typeid(int&)) {
                if (sections[index].int_variables.find(varName) == sections[index].int_variables.end()) {
                    throw invalid_variable_name();

                }
                else {
                    return sections[index].int_variables[varName];
                }

            }

            else if (typeid(T) == typeid(float&)) {
                if (sections[index].float_variables.find(varName) == sections[index].float_variables.end()) {
                    throw invalid_variable_name();

                }
                else {
                    return sections[index].float_variables[varName];
                }
            }
            
            }

        //� ������ ����� ��������� ���� ������ ��� ���������� ���������� ������������ ��������� ��������
        catch (invalid_section_name& e) {
            std::cout << e.what() << std::endl;
            std::cout << "Possible names of sections: ";
            for (Section l : sections) {
                std::cout << l.name << " ";
            }
            std::cout << std::endl;
        }

        catch (invalid_variable_name& e) {
            std::cout << e.what() << std::endl;
            std::cout << "Possible names of variable: ";
            std::map<std::string, int>::iterator it1;
            std::map<std::string, float>::iterator it2;
            if (typeid(T) == typeid(int&)) {
                for (it1 = sections[index].int_variables.begin(); it1 != sections[index].int_variables.end(); it1++)
                {
                    std::cout << it1->first << " ";
                }
            }
            else if (typeid(T) == typeid(float&)) {
                for (it2 = sections[index].float_variables.begin(); it2 != sections[index].float_variables.end(); it2++)
                {
                    std::cout << it2->first << " ";
                }
            }
            
            std::cout << std::endl;
        }

        return 0;
    }

    //������������� ������� ��� ���� string
    template<>
    std::string get_value(std::string sectionName, std::string varName) {
        int index{};
        bool contains{};
        try {
            for (int i = 0; i < sections.size(); i++) {
                if (sections[i].name == sectionName) {
                    index = i;
                    contains = 1;
                    break;
                }
            }
            if (contains == 0) {
                throw invalid_section_name();
            }

                if (sections[index].string_variables.find(varName) == sections[index].string_variables.end()) {
                    throw invalid_variable_name();

                }
                else {
                    return sections[index].string_variables[varName];
                }


        }

//� ������ ����� ��������� ���� ������ ��� ���������� ���������� ������������ ��������� ��������
        catch (invalid_section_name& e) {
            std::cout << e.what() << std::endl;
            std::cout << "Possible names of sections: ";
            for (Section l : sections) {
                std::cout << l.name << " ";
            }
            std::cout << std::endl;
        }

        catch (invalid_variable_name& e) {
            std::cout << e.what() << std::endl;
            std::cout << "Possible names of variable: ";
            std::map<std::string, std::string>::iterator it;
            for (it = sections[index].string_variables.begin(); it != sections[index].string_variables.end(); it++)
            {
                std::cout << it->first << " ";
            }
            std::cout << std::endl;
        }

        return "";
    }

 //������� ������ ���� �������� ���� Int
    void printInt() {
        std::cout << "Integer values: " << std::endl;
        for (Section s : sections) {
            if (!s.int_variables.empty()) {
                std::cout << s.name << ": " << std::endl;
            }
       
            for (std::pair<std::string, int> p : s.int_variables) {
                std::cout << p.first << " = " << p.second << std::endl;
            }
        }
        std::cout << std::endl;
    }

    //������� ������ ���� �������� ���� Float
    void printFloat() {
        std::cout << "Float values: " << std::endl;
        for (Section s : sections) {
            if (!s.float_variables.empty()) {
                std::cout << s.name << ": " << std::endl;
            }
            
            for (std::pair<std::string, float> p : s.float_variables) {
                std::cout << p.first << " = " << p.second << std::endl;
            }
        }
        std::cout << std::endl;
    }

    //������� ������ ���� �������� ���� String
    void printString() {
        std::cout << "String values: " << std::endl;
        for (Section s : sections) {
            if (!s.string_variables.empty()) {
                std::cout << s.name << ": " << std::endl;
            }
        
            for (std::pair<std::string, std::string> p : s.string_variables) {
                std::cout << p.first << " = " << p.second << std::endl;
            }
        }
        std::cout << std::endl;
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::setlocale(LC_ALL, "Russian");

    parser parser;

    parser.receiveData("data.ini");

    parser.printInt();
    parser.printFloat();
    parser.printString();
    std::cout << "Variable var1 of section Section1: " << parser.get_value<float>("Section1", "var1") << std::endl;
    std::cout << "Variable var1 of section Section2: " << parser.get_value<int>("Section2", "var1") << std::endl;
    std::cout << "Variable var3 of section Section1: " << parser.get_value<std::string>("Section1", "var3") << std::endl;
    std::cout << "Wrong Variable var15 of section Section1: " << parser.get_value<float>("Section1", "var15") << std::endl;
    std::cout << "Variable var1 of wrong section Section7: " << parser.get_value<int>("Section7", "var1") << std::endl;


}