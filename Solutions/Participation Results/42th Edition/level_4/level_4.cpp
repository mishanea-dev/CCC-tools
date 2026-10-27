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
    config.example_input = "in_level-4_0-example.txt";
    config.expected_output = "out_level-4_0-example.txt";

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
    vector<int> instruction_lines;
    vector<vector<array<char, 6>>> instructions;
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

void moveClockwise(vector<int>& emitter, vector<string>& map, int r) {
    if (map.empty() || map[0].empty() || emitter.size() < 3) {
        return;
    }

    const int height = static_cast<int>(map.size());
    const int width = static_cast<int>(map[0].size());

    int& y = emitter[1];
    int& x = emitter[2];

    const int middleX = width / 2;
    const int topLeftX = r;
    const int topRightX = width - r - 1;

    // Top horizontal edge: left to right.
    if (y == 0) {
        if (x < topRightX) {
            x += 2;
        } else {
            // Top-right diagonal.
            ++y;
            ++x;
        }
        return;
    }

    // Upper-left or upper-right diagonal.
    if (y < r) {
        if (x < middleX) {
            --y;
            ++x;
        } else {
            ++y;
            ++x;
        }
        return;
    }

    // Leftmost and rightmost vertices.
    if (y == r) {
        if (x == 0) {
            --y;
            ++x;
        } else {
            ++y;
            --x;
        }
        return;
    }

    // Bottom-left or bottom-right diagonal.
    if (y < height - 1) {
        if (x < middleX) {
            --y;
            --x;
        } else {
            ++y;
            --x;
        }
        return;
    }

    // Bottom horizontal edge: right to left.
    if (x > topLeftX) {
        x -= 2;
    } else {
        // Bottom-left diagonal.
        --y;
        --x;
    }
}
void moveCounterClockwise(vector<int>& emitter, vector<string>& map, int r) {
    if (map.empty() || map[0].empty() || emitter.size() < 3) {
        return;
    }

    const int height = static_cast<int>(map.size());
    const int width = static_cast<int>(map[0].size());

    int& y = emitter[1];
    int& x = emitter[2];

    const int middleX = width / 2;
    const int topLeftX = r;
    const int topRightX = width - r - 1;

    // Top horizontal edge: right to left.
    if (y == 0) {
        if (x > topLeftX) {
            x -= 2;
        } else {
            // Top-left diagonal.
            ++y;
            --x;
        }
        return;
    }

    // Upper-left or upper-right diagonal.
    if (y < r) {
        if (x < middleX) {
            ++y;
            --x;
        } else {
            --y;
            --x;
        }
        return;
    }

    // Leftmost and rightmost vertices.
    if (y == r) {
        if (x == 0) {
            ++y;
            ++x;
        } else {
            --y;
            --x;
        }
        return;
    }

    // Bottom-left or bottom-right diagonal.
    if (y < height - 1) {
        if (x < middleX) {
            ++y;
            ++x;
        } else {
            --y;
            ++x;
        }
        return;
    }

    // Bottom horizontal edge: left to right.
    if (x < topRightX) {
        x += 2;
    } else {
        // Bottom-right diagonal.
        --y;
        ++x;
    }
}

Output solve(const Input& data) {
    Output result;
    // create empty map
    for(int r : data.maps_radius){
        result.maps.push_back(createMap(r));
    }
    
    // Each map loop
    for(size_t indx = 0; indx < data.n; indx++){
        auto &map = result.maps[indx];
        int r = data.maps_radius[indx];
        int width = (int)map.back().size();
        int height = (int)map.size();

        // initiate the emmiters [0] - is active, [1][2] - x, y pos
        vector<vector<int>> emitters = {
            {0, r, 0},
            {0, 0, r},
            {0, 0, width-r-1},
            {0, r, width-1},
            {0, height-1, width-r-1},
            {0, height-1, r}
        };

        // move through instructions
        for(auto instruction : data.instructions[indx]){
            for(int instruction_nr = 0; instruction_nr < 6; instruction_nr++){

                switch(instruction[instruction_nr]){
                    case 'F' :
                        moveClockwise(emitters[instruction_nr], map, r);
                        break;
                    case 'B' :
                        moveCounterClockwise(emitters[instruction_nr], map, r);
                        break;
                    case 'T' :
                        emitters[instruction_nr][0] = !emitters[instruction_nr][0];
                        break;
                }
                
            }

            for(auto emitter : emitters){
                int y = emitter[2];
                int x = emitter[1];
                
                while(x < width){
                    x++;
                    if(map[y][x] == 'O') map[y][x] = 'T'; else 
                    if(map[y][x] == 'T') map[y][x] = 'C'; else
                    if(map[y][x] == 'M') map[y][x] = 'H'; else
                    if(map[y][x] == 'H') map[y][x] = 'D'; else
                    if(map[y][x] == 'C' || map[y][x] == 'D') map[y][x] = 'X';
                }
            }

            for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
            if(map[i][j] == 'H' || map[i][j] == 'D' || map[i][j] == 'C')
            map[i][j] = 'M';
            else if(map[i][j] == 'T' || map[i][j] == 'X')
            map[i][j] = 'O';

        }

    }

    
    return result;
}

Input read(istream& in) {
    Input data;
    
    in >> data.n;

    for (int i = 0; i < data.n; i++) {
        int radius;
        int instructions_nr;

        in >> radius >> instructions_nr;

        data.maps_radius.push_back(radius);
        data.instruction_lines.push_back(instructions_nr);

        vector<array<char, 6>> map_instructions(instructions_nr);

        for (auto& instruction : map_instructions) {
            for (char& value : instruction) {
                in >> value;
            }
        }

        data.instructions.push_back(move(map_instructions));
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