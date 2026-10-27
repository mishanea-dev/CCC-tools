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
    config.input_prefix = "in_";

    return config;
}();} 

// ============================================================
// PROBLEM IMPLEMENTATION - YOUR WORK AREA
// ============================================================

struct Input {
    int n;
    vector<array<int, 2>> sizes;
};
struct Output {
    vector<vector<string>> maps;
};

Output solve(const Input& data) {
    Output result;

    for(auto [width, height] : data.sizes){
        result.maps.push_back({});
        
        
        for(int i = 0; i < height+2; i++){
            result.maps.back().push_back("");

            
            for(int j = 0; j < width+2; j++){
                if(i > 0 && i <= height && j > 0 && j <= width) 
                    result.maps.back().back() += ':';
                else 
                    result.maps.back().back() += '#';
            }
        }
    }
    
    return result;
}

Input read(istream& in) {
    Input data;
    
    int x, y;
    in >> data.n;
    for(int i = 0; i < data.n; i++){
        in >> x >> y;
        data.sizes.push_back({x, y});
    }
    
    return data;
}
void write(ostream& out, const Output& result) {
    for(const auto& map : result.maps){
        for(const auto& line : map){
            out << line << endl;
        }
        out << endl;
    }
}

// ============================================================
// ENTRY POINT - DO NOT EDIT
// ============================================================

#include "runner_main.h"