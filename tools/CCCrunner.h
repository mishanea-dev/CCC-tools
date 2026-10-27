#pragma once

#include <bits/stdc++.h>
#include <filesystem>

namespace ccc {
namespace fs = std::filesystem;
using namespace std;

// ============================================================
// CONFIGURATION TYPE
// ============================================================

struct Config {
    bool batch = false;
    bool debug = true;

    string example_input;
    string expected_output;

    string input_dir = "inputs";
    string output_dir = "results";

    string input_extension = ".in";
    string input_prefix;
};

// Each level defines one Config instance.

// ============================================================
// DEBUGGING
// ============================================================

inline ostringstream debug_buffer;

class NullBuffer : public streambuf {
    int overflow(int c) override {
        return c;
    }
};

inline NullBuffer null_buffer;
inline ostream null_stream(&null_buffer);

inline bool debug_active = false;

inline ostream& debug() {
    return debug_active ? debug_buffer : null_stream;
}

// In level code, use:
// DBG << "Value: " << x << '\n';

#define DBG ::ccc::debug()

// ============================================================
// INTERNAL HELPERS
// ============================================================

inline string read_file(const string& filename) {
    ifstream file(filename);

    if (!file) {
        throw runtime_error("Cannot open: " + filename);
    }

    ostringstream content;
    content << file.rdbuf();
    return content.str();
}

inline string normalize(string s) {
    s.erase(remove(s.begin(), s.end(), '\r'), s.end());
    return s;
}

// Discard accidental cout statements while reading/solving.
class CoutSilencer {
    streambuf* original;

public:
    CoutSilencer() : original(cout.rdbuf(&null_buffer)) {}

    ~CoutSilencer() {
        cout.rdbuf(original);
        cout.clear();
    }
};

// Run one instance and return only the official answer.
template<class Read, class Solve, class Write>
string run_one(istream& in, Read read, Solve solve, Write write,
               bool debug_enabled) {
    debug_buffer.str("");
    debug_buffer.clear();

    debug_active = debug_enabled;

    string answer;

    {
        CoutSilencer silence;

        auto data = read(in);
        auto result = solve(data);

        ostringstream out;
        write(out, result);
        answer = out.str();
    }

    debug_active = false;

    return answer;
}

// ============================================================
// EXAMPLE MODE
// ============================================================

template<class Read, class Solve, class Write>
void run_example(const Config& config, Read read, Solve solve, Write write) {
    string input_text = read_file(config.example_input);
    istringstream in(input_text);

    string actual = run_one(in, read, solve, write, config.debug);

    string debug_text = debug_buffer.str();

    if (!debug_text.empty()) {
        cout << "===================== DEBUG =====================\n";
        cout << debug_text;
        if (debug_text.back() != '\n') {
            cout << '\n';
        }
    }

    cout << "===================== INPUT =====================\n";
    cout << input_text;
    if (input_text.empty() || input_text.back() != '\n') {
        cout << '\n';
    }

    cout << "===================== OUTPUT ====================\n";
    cout << actual;

    if (actual.empty() || actual.back() != '\n') {
        cout << '\n';
    }

    cout << "=================================================\n";

    if (config.expected_output.empty() ||
        !fs::exists(config.expected_output)) {
        return;
    }

    string expected = read_file(config.expected_output);

    if (normalize(actual) == normalize(expected)) {
        cout << "[PASS] Output matches expected answer.\n";
    } else {
        cout << "[FAIL] Output differs from expected answer.\n";
        
        cout << "================ EXPECTED OUTPUT ================\n";
        cout << expected;
        if (expected.empty() || expected.back() != '\n') {
            cout << '\n';
        }
        cout << "=================================================\n";
    }
}

// ============================================================
// BATCH MODE
// ============================================================

template<class Read, class Solve, class Write>
void run_batch(const Config& config, Read read, Solve solve, Write write) {
    if (!fs::exists(config.input_dir) ||
        !fs::is_directory(config.input_dir)) {
        throw runtime_error("Input directory not found: " +
                            config.input_dir);
    }

    fs::create_directories(config.output_dir);

    vector<fs::path> files;

    for (const auto& entry : fs::directory_iterator(config.input_dir)) {
        if (!entry.is_regular_file()) continue;

        auto path = entry.path();

        if (path.extension() != config.input_extension) continue;

        string filename = path.filename().string();

        if (!config.input_prefix.empty() &&
            filename.rfind(config.input_prefix, 0) != 0) {
            continue;
        }

        files.push_back(path);
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

            // Debugging is intentionally disabled for batch mode.
            string answer = run_one(in, read, solve, write, false);

            fs::path output_path =
                fs::path(config.output_dir) / input_path.filename();

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

extern Config CCC_CONFIG;

// ============================================================
// ENTRY POINT
// ============================================================

// The level file must define:
//   ccc::Config CCC_CONFIG;
//   Input read(istream&);
//   Output solve(const Input&);
//   void write(ostream&, const Output&);
//
// Include this header at the END of the level's .cpp file.

} // namespace ccc

// int main() {
//     try {
//         if (ccc::CCC_CONFIG.batch) {
//             ccc::run_batch(ccc::CCC_CONFIG, read, solve, write);
//         } else {
//             ccc::run_example(ccc::CCC_CONFIG, read, solve, write);
//         }
//     } catch (const exception& e) {
//         cerr << "[ERROR] " << e.what() << '\n';
//         return 1;
//     }

//     return 0;
// }
