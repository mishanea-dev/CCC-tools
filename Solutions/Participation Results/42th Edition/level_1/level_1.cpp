#include <bits/stdc++.h>
#include "CCCrunner.h"
using namespace std;

// ============================================================
// CONFIGURATION - CHANGE THESE FOR THIS LEVEL
// ============================================================

namespace ccc {
Config CCC_CONFIG = [] {
    Config config;

    // false = one example; true = all matching inputs
    config.batch = true;

    // Debug usage: // DBG << "Value: " << x << '\n';
    config.debug = true;

    // Example files:
    config.example_input = "in_level-1_0-example.txt";
    config.expected_output = "out_level-1_0-example.txt";

    // Batch files:
    config.input_dir = ".";
    config.output_dir = "results";
    config.input_extension = ".txt";
    config.input_prefix = "in_level";

    return config;
}();} 

// ============================================================
// PROBLEM IMPLEMENTATION - YOUR WORK AREA
// ============================================================

struct Input {
    int n;
    vector<int> maps_radius;
};
struct Output {
    vector<vector<string>> maps;
};

vector<string> createMap(int r){
    vector<string> map; //(r*2+1, string(r*2+1, '-'));

    string row = string(r, '-');
    for(int i = 0; i < r+1; i++){
        row += "*-";
    }
    row += string(r-1, '-');
    map.push_back(row);


    for(int i = 0; i < r; i++){
        row = "";
        
        row += string(r-i-1, '-');
        row += "*-";
        for(int j = 0; j < r+i; j++){
            row += "O-";
        }   
        row += "*";
        row += string(r-i-1, '-');

        map.push_back(row);
    }

    for(int i = 1; i < r; i++){
        row = "";
        
        row += string(i, '-');
        row += "*-";
        for(int j = r*2-i-1; j > 0; j--){
            row += "O-";
        }   
        row += "*";
        row += string(i, '-');

        map.push_back(row);
    }

    row = string(r, '-');
    for(int i = 0; i < r+1; i++){
        row += "*-";
    }
    row += string(r-1, '-');
    map.push_back(row);

    return map;
}

Output solve(const Input& data) {
    Output result;

    for(int r : data.maps_radius){
        result.maps.push_back(createMap(r));
    }
    
    return result;
}

Input read(istream& in) {
    Input data;
    
    in >> data.n;
    int x;
    for(int i = 0; i < data.n; i++){
        in >> x;
        data.maps_radius.push_back(x); 
    }
    
    return data;
}

void write(ostream& out, const Output& result) {
    for(const auto& map : result.maps){
        for(const auto& row : map){
            out << row << endl;
        }
        out << endl;
    }
}

// ============================================================
// ENTRY POINT - DO NOT EDIT
// ============================================================

#include "runner_main.h"