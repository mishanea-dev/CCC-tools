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
    config.batch = false;

    // Debug usage: // DBG << "Value: " << x << '\n';
    config.debug = true;

    // Example files:
    config.example_input = "in_level-1_0-example.txt";
    config.expected_output = "out_level-1_0-example.txt";

    // Batch files:
    config.input_dir = ".";
    config.output_dir = "results";
    config.input_extension = ".in";
    config.input_prefix = "";

    return config;
}();} 

// ============================================================
// PROBLEM IMPLEMENTATION - YOUR WORK AREA
// ============================================================

struct Input {
    // TODO: Declare the data parsed from the input.
};
struct Output {
    // TODO: Declare the data for the result.
};

Input read(istream& in) {
    Input data;
    
    // TODO: Read and return the problem input.
    
    return data;
}

void write(ostream& out, const Output& result) {
    // TODO: Format the answer for the official output.
    // Example:
    // out << result.answer << '\n';
}

Output solve(const Input& data) {
    Output result;

    // TODO: Implement the algorithm.
    
    return result;
}

// ============================================================
// ENTRY POINT - DO NOT EDIT
// ============================================================

#include "runner_main.h"