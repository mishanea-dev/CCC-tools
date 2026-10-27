#include <bits/stdc++.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// ============================================================
// CONFIGURATION — CHANGE THESE FOR EACH LEVEL
// ============================================================

// false: run one example and print the answer in CodeRunner.
// true:  run every matching input file and create .out files.
const bool RUN_ALL_INPUTS = true;

// Example mode:
const string EXAMPLE_INPUT = "in_level-1_0-example.txt";
const string EXPECTED_OUTPUT = "out_level-1_0-example.txt";

// Batch mode:
const string INPUT_DIR = ".";
const string OUTPUT_DIR = "results";
const string INPUT_EXTENSION = ".txt";
const string INPUT_PREFIX = "in_level-1_";

// ============================================================
// LEVEL-SPECIFIC CODE — EDIT THESE FOR EACH LEVEL
// ============================================================

struct Input {
    int n;
    vector<string> paths;
};

struct Output {
    vector<array<int, 4>> answer;
};

// Read one problem instance.
Input read(istream& in) {
    Input data{};

    in >> data.n;
    data.paths.resize(data.n);

    for (string& x : data.paths) {
        in >> x;
    }

    return data;
}

// Solve one problem instance.
Output solve(const Input& data) {
    Output result{};

    for(const string& s : data.paths) {
        result.answer.push_back({0, 0, 0, 0});
        // cout << s << endl;
        for(char c : s) {
            if(c == 'W'){
                result.answer.back()[0]++;
            } else 
            if(c == 'D'){
                result.answer.back()[1]++;
            } else 
            if(c == 'S'){
                result.answer.back()[2]++;
            } else 
            if(c == 'A'){
                result.answer.back()[3]++;
            }
        }
    }

    return result;
}

// Format one result.
void write(ostream& out, const Output& result) {
    for(auto &x : result.answer) {
        out << x[0] << ' ' << x[1] << ' ' << x[2] << ' ' << x[3] << '\n';
    }
}

// ============================================================
// RUNNER — LEAVE THIS PART ALONE
// ============================================================

string run(istream& in) {
    Input data = read(in);
    Output result = solve(data);

    ostringstream out;
    write(out, result);

    return out.str();
}

string read_file(const string& filename) {
    ifstream file(filename);

    if (!file) {
        throw runtime_error("Cannot open: " + filename);
    }

    ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

string normalize(string s) {
    // Normalize Windows CRLF line endings.
    s.erase(remove(s.begin(), s.end(), '\r'), s.end());
    return s;
}

void run_example() {
    ifstream in(EXAMPLE_INPUT);

    if (!in) {
        throw runtime_error("Cannot open example: " + EXAMPLE_INPUT);
    }

    string actual = run(in);

    // CodeRunner displays the answer in its output panel.
    cout << actual;

    if (!EXPECTED_OUTPUT.empty() &&
        fs::exists(EXPECTED_OUTPUT)) {

        string expected = read_file(EXPECTED_OUTPUT);

        if (normalize(actual) == normalize(expected)) {
            cerr << "\n[PASS] Matches expected output.\n";
        } else {
            cerr << "\n[FAIL] Output differs from expected.\n";
        }
    }
}

void run_all_inputs() {
    fs::create_directories(OUTPUT_DIR);

    vector<fs::path> files;

    for (const auto& entry : fs::directory_iterator(INPUT_DIR)) {
        if (!entry.is_regular_file()) continue;

        fs::path p = entry.path();

        if (p.extension() != INPUT_EXTENSION) continue;

        string filename = p.filename().string();

        if (filename.rfind(INPUT_PREFIX, 0) != 0) continue;

        files.push_back(p);
    }

    sort(files.begin(), files.end());

    if (files.empty()) {
        cerr << "No matching input files found.\n";
        return;
    }

    for (const auto& input_path : files) {
        try {
            ifstream in(input_path);

            if (!in) {
                throw runtime_error("Cannot open input");
            }

            string answer = run(in);

            // Same base filename, with .out extension.
            fs::path output_path =
                fs::path(OUTPUT_DIR) / input_path.filename();

            output_path.replace_extension(".out");

            ofstream out(output_path);

            if (!out) {
                throw runtime_error("Cannot create output");
            }

            out << answer;

            if (!out) {
                throw runtime_error("Failed writing output");
            }

            cerr << "[OK] " << input_path.filename()
                 << " -> " << output_path.filename() << '\n';

        } catch (const exception& e) {
            cerr << "[ERROR] " << input_path.filename()
                 << ": " << e.what() << '\n';
        }
    }
}

int main() {
    try {
        if (RUN_ALL_INPUTS) {
            run_all_inputs();
        } else {
            run_example();
        }
    } catch (const exception& e) {
        cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}
