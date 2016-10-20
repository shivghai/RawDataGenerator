//
//  main.cpp
//  Test It
//
//  Created by Shiv Ghai on 7/3/15.
//  Copyright (c) 2015 sghai. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <fstream>
#include <cassert>
#include "dataStructs.h"
#include "helperFunctions.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    string fileName;
    
    cout << "Enter filename or specify \"stdin\": ";
    cin >> fileName;
    
    if(fileName == "stdin") {
    
        startGen(cin);
        generateOutput(cin);
  
    }
    
    else {
        
        fin.open(fileName.c_str());
        assert(fin.is_open());
    
        startGen(fin);
        generateOutput(fin);
        
    }
    return 0;
}
