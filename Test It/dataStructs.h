//
//  dataStructs.h
//  Test It
//
//  Created by Shiv Ghai on 7/11/15.
//  Copyright (c) 2015 sghai. All rights reserved.
//

#ifndef Test_It_dataStructs_h
#define Test_It_dataStructs_h

#include <string>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include "helperFunctions.h"
using namespace std;



/* Defined map - for random predefined values */

template <typename T>
class definedVariables {
    map<string, vector<T> > myMap;
public:
    
    /* Creates a vector of strings for a variable name - if it already exists, appends more */
    void insert(string &s, vector<T> &vecList) {
        
        if(myMap.find(s) == myMap.end())
            myMap[s] = vecList;
        else {
            for(size_t i = 0; i < vecList.size(); ++i)
                myMap[s].push_back(vecList[i]);
        }
        
    }
    
    /* Generates a random string from variable name */
    T get_val(string &s) {
        
        assert(myMap.find(s) != myMap.end());
        return myMap[s][rand() % myMap[s].size()];
        
    }
    
};


/* Constant variables (int, double and char) */

template <typename T>
class constVariables {
    map<string, T> myMap;
    bool isDouble;
public:
    
    constVariables(string s) {
        
        if(s == "double")
            isDouble = true;
        else if(s == "int" || s == "char")
            isDouble = false;
        else
            assert(0);
        
    }
    
    double get_double(double l, double u) {
        
        double f = (double)rand() / RAND_MAX;
        return l + f * (u - l);
        
    }
    
    void insert(string &s, T l, T u) {
        
        assert(myMap.find(s) == myMap.end());
        
        if(isDouble == false)
            myMap[s] = T (rand()%int(u - l + 1) + l);
        else
            myMap[s] = get_double(l, u);
        
    }
    
    T get_val(string &s) {
        assert(myMap.find(s) != myMap.end());
        return myMap[s];
    }
};


/* Non constant variables (int, double and char) */

template <typename T>
class rangeVariables {
    bool isDouble;
    map<string, pair<T, T> > myMap;
public:
    
    
    rangeVariables(string s) {
        
        if(s == "double")
            isDouble = true;
        else if(s == "int" || s == "char")
            isDouble = false;
        else
            assert(0);
        
    }
    
    double get_double(double l, double u) {
        
        double f = (double)rand() / RAND_MAX;
        return l + f * (u - l);
        
    }
    
    void insert(string &s, T l, T u) {
        
        assert(myMap.find(s) == myMap.end());
        
        myMap[s].first = l;
        myMap[s].second = u;
        
    }
    
    T get_val(string &s) {
        
        assert(myMap.find(s) != myMap.end());
        
        if(isDouble == true)
            return get_double(myMap[s].first, myMap[s].second);
        
        return rand()%( int(myMap[s].second - myMap[s].first + 1) ) + myMap[s].first;
        
    }
    
   
};

/* Structures initialized from a file */


class structVariables {
    map<string, map<string, vector<string> > > myMap;
    map<string, vector<string> > categoryMap;
public:
    
    string get_val(string &s, string &column, int num_struct = rand()) {
        
        assert(myMap.find(s) != myMap.end());
        assert(myMap[s].find(column) != myMap[s].end());
        
        return myMap[s][column][num_struct % myMap[s][column].size()];
        
    }
     
    void getFromFile(string &s, string &fileName) {
        
        fstream fin;
        string input;
        char delimiter = ' ';
        int counter = 0;
        size_t lastpos = 0;
        int category_num = 0;
         
        if(fileName[0] == ',') {
         
            delimiter = ',';
            fileName = fileName.substr(1);
         
        }
         
        fin.open(fileName.c_str());
        
        /* for first line - categories */
        getline(fin, input);
         
        for(size_t i = 0; i < input.size(); ++i) {
            
            if(input[i] == delimiter && i < input.size() - 1) {
                categoryMap[s].push_back(input.substr(lastpos, counter));
                counter = 0;
                lastpos = i + 1;
            }
            else if (i == input.size() - 1) {
                ++counter;
                categoryMap[s].push_back(input.substr(lastpos, counter));
            }
            else
                ++counter;
        }
        
        
        while(getline(fin, input)) {
            category_num = 0;
            lastpos = 0;
            counter = 0;
            for(size_t i = 0; i < input.size() && category_num < categoryMap[s].size(); ++i) {
                
                if(input[i] == delimiter && category_num < categoryMap[s].size() - 1) {
                    myMap[s][categoryMap[s][category_num]].push_back(input.substr(lastpos, counter));
                    counter = 0;
                    lastpos = i + 1;
                    ++category_num;
                }
                else if(i == input.size() - 1) {
                    ++counter;
                    myMap[s][categoryMap[s][category_num]].push_back(input.substr(lastpos, counter));
                }
                else
                    ++counter;
            }
            
        }
         
     
    }
    
    
    
 
 
};

#endif
