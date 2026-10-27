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
    config.example_input = "level-2/in_level-2_0-example.txt";
    config.expected_output = "level-2/out_level-2_0-example.txt";

    // Batch files:
    config.input_dir = "level-2";
    config.output_dir = "level-2/results";
    config.input_extension = ".txt";
    config.input_prefix = "in_level-2_";

    return config;
}();} 

// ============================================================
// PROBLEM IMPLEMENTATION - YOUR WORK AREA
// ============================================================

struct Input {
    int n;
    vector<string> paths;
};
struct Output {
    vector<array<int, 2>> answer; // width, height
};

Input read(istream& in) {
    Input data;
    
    in >> data.n;
    data.paths.resize(data.n);
    for (string& x : data.paths) {
        in >> x;
    }
    
    return data;
}
void write(ostream& out, const Output& result) {
    for (const auto& pos : result.answer) {
        out << pos[0] << ' ' << pos[1] << '\n';
    }
}

Output solve(const Input& data) {
    Output result;

    for(const string& s : data.paths) {
        result.answer.push_back({0,0});
        auto& width = result.answer.back()[0];
        auto& height = result.answer.back()[1];
        int xAxis = 0; 
        int yAxis = 0;
        int maxUp = 0, maxDown = 0, maxLeft = 0, maxRight = 0;

        DBG << xAxis << ' ' << yAxis << endl;
        DBG << maxLeft << ' ' << maxRight << ' ' << maxUp << ' ' << maxDown << endl;

        for(char c : s){
            if(c == 'W'){
                yAxis++;
                if(yAxis > maxUp) maxUp = yAxis;
            } else 
            if(c == 'S'){
                yAxis--;
                if(yAxis < maxDown) maxDown = yAxis;
            } else 
            if(c == 'A'){
                xAxis--;
                if(xAxis < maxLeft) maxLeft = xAxis;
            } else 
            if(c == 'D'){
                xAxis++;
                if(xAxis > maxRight) maxRight = xAxis;
            }
        }


        width = maxRight + (-1)*maxLeft + 1;
        height = maxUp + (-1)*maxDown + 1;
    }

    

    return result;
}



// ============================================================
// ENTRY POINT - DO NOT EDIT
// ============================================================
#include "runner_main.h"