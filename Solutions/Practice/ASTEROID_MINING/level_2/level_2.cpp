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
    config.example_input = "in_level-2_0-example.txt";
    config.expected_output = "out_level-2_0-example.txt";

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
    vector<array<int, 2>> sizes; // width, height
    vector<vector<string>> maps;
};
struct Output {
    vector<vector<string>> maps;
};

Output solve(const Input& data) {
    Output result;

    result.maps = data.maps;
    
    for (size_t map_indx = 0; map_indx < result.maps.size(); map_indx++) {
        auto& map = result.maps[map_indx];
        auto [width, height] = data.sizes[map_indx];

        for(int i = 1; i <= width; i++){
            if(map[0][i] == 'S'){
                // DBG << "Found the S in the position 0 " << i; 
                for(int j = 1; j <= height; j++){
                    map[j][i] = 'X';
                }
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
        data.maps.emplace_back(y + 2);
        for(int j = 0; j < y + 2; j++){
            in >> data.maps.back()[j];
        }
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