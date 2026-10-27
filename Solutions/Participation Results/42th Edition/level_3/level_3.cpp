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
    config.example_input = "in_level-3_0-example.txt";
    config.expected_output = "out_level-3_0-example.txt";

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
    vector<vector<string>> maps;
};
struct Output {
    vector<vector<string>> maps;
};

Output solve(const Input& data) {
    Output result;
    result.maps = data.maps;
    
    for(auto &map : result.maps){
        int height = map.size();
        int width = map.back().size();
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                int y = i;
                int x = j;
                switch(map[i][j]){
                    case '1' :
                        while(x < width){
                            x++;
                            if(map[y][x] == 'O') map[y][x] = 'T'; else 
                            if(map[y][x] == 'T') map[y][x] = 'C'; else
                            if(map[y][x] == 'M') map[y][x] = 'H'; else
                            if(map[y][x] == 'H') map[y][x] = 'D'; else
                            if(map[y][x] == 'C' || map[y][x] == 'D') map[y][x] = 'X';
                        }
                        break;
                    case '2' :
                        while(x < width && y < height-1){
                            x++;
                            y++;
                            if(map[y][x] == 'O') map[y][x] = 'T'; else 
                            if(map[y][x] == 'T') map[y][x] = 'C'; else
                            if(map[y][x] == 'M') map[y][x] = 'H'; else
                            if(map[y][x] == 'H') map[y][x] = 'D'; else
                            if(map[y][x] == 'C' || map[y][x] == 'D') map[y][x] = 'X';
                        }
                        break;
                    case '3' :
                        while(x > 0 && y < height-1){
                            x--;
                            y++;
                            if(map[y][x] == 'O') map[y][x] = 'T'; else 
                            if(map[y][x] == 'T') map[y][x] = 'C'; else
                            if(map[y][x] == 'M') map[y][x] = 'H'; else
                            if(map[y][x] == 'H') map[y][x] = 'D'; else
                            if(map[y][x] == 'C' || map[y][x] == 'D') map[y][x] = 'X';
                        }
                        break;
                    case '4' :
                        while(x > 0){
                            x--;
                            if(map[y][x] == 'O') map[y][x] = 'T'; else 
                            if(map[y][x] == 'T') map[y][x] = 'C'; else
                            if(map[y][x] == 'M') map[y][x] = 'H'; else
                            if(map[y][x] == 'H') map[y][x] = 'D'; else
                            if(map[y][x] == 'C' || map[y][x] == 'D') map[y][x] = 'X';
                        }
                        break;
                    case '5' :
                        while(x > 0 && y > 0){
                            x--;
                            y--;
                            if(map[y][x] == 'O') map[y][x] = 'T'; else 
                            if(map[y][x] == 'T') map[y][x] = 'C'; else
                            if(map[y][x] == 'M') map[y][x] = 'H'; else
                            if(map[y][x] == 'H') map[y][x] = 'D'; else
                            if(map[y][x] == 'C' || map[y][x] == 'D') map[y][x] = 'X';
                        }
                        break;
                    case '6' :
                        while(x < width-1 && y > 0){
                            x++;
                            y--;
                            if(map[y][x] == 'O') map[y][x] = 'T'; else 
                            if(map[y][x] == 'T') map[y][x] = 'C'; else
                            if(map[y][x] == 'M') map[y][x] = 'H'; else
                            if(map[y][x] == 'H') map[y][x] = 'D'; else
                            if(map[y][x] == 'C' || map[y][x] == 'D') map[y][x] = 'X';
                        }
                        break;

                    
                }
            }
        }

        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                if(map[i][j] == 'H' || map[i][j] == 'D' || map[i][j] == 'C')
                    map[i][j] = 'M';
                else if(map[i][j] == 'T' || map[i][j] == 'X')
                    map[i][j] = 'O';
    

    }

    return result;
}

Input read(istream& in) {
    Input data;
    
    in >> data.n;

    for (int i = 0; i < data.n; i++) {
        int radius;
        int height;
        int width;

        in >> radius >> height >> width;

        data.maps_radius.push_back(radius);

        vector<string> map(height);
        for (string& row : map) {
            in >> row;
        }

        data.maps.push_back(move(map));
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