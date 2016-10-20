#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <fstream>
#include <vector>
#include "dataStructs.h"
#include "helperFunctions.h"

using namespace std;

map<string, pair<string, string> > variableList;

definedVariables<int> intDefined;
definedVariables<char> charDefined;
definedVariables<string> stringDefined;
definedVariables<double> doubleDefined;

constVariables<int> intConst("int");
constVariables<char> charConst("char");
constVariables<double> doubleConst("double");

rangeVariables<int> intRange("int");
rangeVariables<char> charRange("char");
rangeVariables<double> doubleRange("double");

structVariables structVar;


/* Get number of horizontal loops */

int getNumLoops(string &s) {
    
    int num_size = 0;
    while(s[num_size] != '}')
        ++num_size;
    --num_size;
    
    return atoi(s.substr(1,num_size).c_str());
}

/* Initialize variables (if any) */

void startGen(istream &fin) {
    
    string input;
    string varName, varType, varGenType, values;
    string dataString;
    vector<string> definedListString;
    vector<int> definedListInt;
    vector<double> definedListDouble;
    vector<char> definedListChar;
    int lower_int, upper_int;
    double lower_double, upper_double;
    char lower_char, upper_char;
    
    srand( int(time(NULL)) );
    
    while(getline(fin, input)) {
        
        definedListString.clear();
        definedListInt.clear();
        definedListDouble.clear();
        definedListChar.clear();
        
        stringstream ss(input);
        ss >> varName;
        
        if(varName == "end"){
            return;
        }
        ss >> varType >> varGenType;
        
        variableList[varName] = make_pair(varType, varGenType);
        
        if(varGenType == "def") {
            
            if(varType == "string") {
                while(ss >> values)
                    definedListString.push_back(values);
                stringDefined.insert(varName, definedListString);
            }
            
            else if(varType == "int") {
                while(ss >> values)
                    definedListInt.push_back(atoi(values.c_str()));
                intDefined.insert(varName, definedListInt);
            }
            
            else if(varType == "double") {
                while(ss >> values)
                    definedListDouble.push_back(strtod(values.c_str(), NULL));
                doubleDefined.insert(varName, definedListDouble);
            }
            
            else if(varType == "char") {
                ss >> values;
                for(size_t i = 0; i < values.size(); ++i)
                    definedListChar.push_back(values[i]);
                charDefined.insert(varName, definedListChar);
            }
            
        }
        
        else if(varGenType == "const" || varGenType == "range") {
            
            if(varType == "int") {
                ss >> lower_int >> upper_int;
                
                if(varGenType == "const")
                    intConst.insert(varName, lower_int, upper_int);
                else
                    intRange.insert(varName, lower_int, upper_int);
            }
            
            else if(varType == "double") {
                ss >> lower_double >> upper_double;
                
                if(varGenType == "const")
                    doubleConst.insert(varName, lower_double, upper_double);
                else
                    doubleRange.insert(varName, lower_double, upper_double);
            }
            
            else if(varType == "char") {
                ss >> lower_char >> upper_char;
                
                if(varGenType == "const")
                    charConst.insert(varName, lower_char, upper_char);
                else
                    charRange.insert(varName, lower_char, upper_char);
            }
        
        }
        
        else if(varType == "struct") {
            
            /* varGenType is the fileName for this case */
            
            structVar.getFromFile(varName, varGenType);
            
        }
        
        else
            assert(0);
        
        
    }
    
}


void generateOutput(istream &fin) {
    
    string input;
    string token;
    
    while(getline(fin, input)) {
        
        stringstream ss(input);
        vector<string> input_line;
        int num_loops = 1;
        
        ss >> token;
        
        if(token == "repeat") {
            
            ss >> token;
            assert(variableList.find(token) != variableList.end() || (token[0] > '0' && token[0] <= '9'));
            
            if(token[0] >= '1' && token[0] <= '9')
                num_loops = atoi(token.c_str());
            else if(variableList[token].second == "def")
                num_loops = intDefined.get_val(token);
            else if(variableList[token].second == "range")
                num_loops = intRange.get_val(token);
            else if(variableList[token].second == "const")
                num_loops = intConst.get_val(token);
            else
                assert(0);
            
            while(ss >> token)
                input_line.push_back(token);
            
        }

        else {
            
            input_line.push_back(token);
            while(ss >> token)
                input_line.push_back(token);
            
        }
        
        while(num_loops--) {
            
            map<int, int> struct_nums;
            
            for(size_t i = 0; i < input_line.size(); ++i) {
                
                string temp = input_line[i];
                bool separator_flag = true;
                char separator = ' ';
                bool modifier_flag = true;
                int num_variables = 1;
                bool struct_flag = false;
                bool whitespace_flag = false;
                int num_whitespace = 0;
                string categoryName, structName;
                int struct_count = 0;
                
                if(temp[0] == '{') {
                    num_variables = getNumLoops(temp);
                    ++i;
                }
                
                while(num_variables--) {
                    
                    separator_flag = true;
                    separator = ' ';
                    modifier_flag = true;
                    struct_count = 0;
                    struct_flag = false;
                    
                    temp = input_line[i];
                
                    while(modifier_flag == true) {
                        
                        modifier_flag = false;
                    
                        switch(temp[0]) {
                        
                            case '>':
                                separator_flag = false;
                                temp = temp.substr(1);
                                modifier_flag = true;
                            break;
                        
                            case ',':
                                separator = ',';
                                temp = temp.substr(1);
                                modifier_flag = true;
                            break;
                                
                            case '@':
                                struct_flag = true;
                                ++struct_count;
                                temp = temp.substr(1);
                                modifier_flag = true;
                            break;
                            
                            case '~':
                                modifier_flag = false;
                                temp = temp.substr(1);
                            
                            case '_':
                                whitespace_flag = true;
                                temp = temp.substr(1);
                                modifier_flag = true;
                                ++num_whitespace;
                            break;
                    
                        }
                    }
                    
                    if(whitespace_flag == true) {
                        
                        for(int i = 0; i < num_whitespace; ++i)
                            cout << " ";
                        
                    }
                
                    if(struct_flag) {
                        
                        struct_nums[1] = rand();
                            
                        structName = temp.substr(0, temp.find_first_of("."));
                        categoryName = temp.substr(temp.find_first_of(".") + 1);
                        
                        if(struct_count != 1 && struct_nums.find(struct_count) != struct_nums.end()) {
                            
                            cout << structVar.get_val(structName, categoryName, struct_nums[struct_count]);
                            
                        }
                        else if(struct_count == 1) {
                            
                            cout << structVar.get_val(structName, categoryName, struct_nums[1]);
                            
                        }
                        else {
                            
                            struct_nums[struct_count] = rand();
                            cout << structVar.get_val(structName, categoryName, struct_nums[struct_count]);
                            
                        }
                        
                    }
                
                    else if(variableList.find(temp) == variableList.end()) {
                    
                        cout << temp;
                    
                    }
            
                    else if(temp[0] >= '1' && temp[0] <= '9') {
                 
                        cout << temp;
                
                    }
            
                    else if(variableList[temp].first == "int") {
                    
                        if(variableList[temp].second == "def")
                            cout << intDefined.get_val(temp);
                        else if(variableList[temp].second == "range")
                            cout << intRange.get_val(temp);
                        else if(variableList[temp]. second == "const")
                            cout << intConst.get_val(temp);
                        else
                            assert(0);
                    
                    }
            
                    else if(variableList[temp].first == "string") {
                    
                        cout << stringDefined.get_val(temp);
                    
                    }
            
                    else if(variableList[temp].first == "double") {
                    
                        if(variableList[temp].second == "def")
                            cout << doubleDefined.get_val(temp);
                        else if(variableList[temp].second == "range")
                            cout << doubleRange.get_val(temp);
                        else if(variableList[temp]. second == "const")
                            cout << doubleConst.get_val(temp);
                        else
                            assert(0);
                    
                    }
            
                    else if(variableList[temp].first == "char") {
                    
                        if(variableList[temp].second == "def")
                            cout << charDefined.get_val(temp);
                        else if(variableList[temp].second == "range")
                            cout << charRange.get_val(temp);
                        else if(variableList[temp]. second == "const")
                            cout << charConst.get_val(temp);
                        else
                            assert(0);
                    
                    }
            
                    else
                        assert(0);
                
                    if(separator_flag == true)
                        cout << separator;
                    }
                
                }
     
            cout << "\n";
        
        }
    }
}