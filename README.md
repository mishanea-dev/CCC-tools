# CCC-tools

A small collection of utilities I built while taking part in the [CloudFlight Coding Contest](https://codingcontest.org).

The goal is simple: remove the repetitive setup work so I can focus on reading the input, solving the problem, and writing the output. The tools currently focus on C++, but if it isn't your programming of choice, I still incurage you to checkuout the [python script](tools/watch_ccc_downloads.py). Over time I might update the tools to suport multiple programming languages. Any contributtions to suport this goal are welcome.

All the code in [`tools/`](tools/) is commented and intended to be easy to adjust. Have fun tinkering with it, and good luck with the contest!


## What is included?

- A C++ runner that:
  - Runs one example input and shows the result.
  - Compares the output with the expected answer.
  - Runs a solution against all test cases in batch mode.
  - Writes batch results into a separate `results` folder.
- A download watcher that automatically extracts newly downloaded CCC levels.
- C++ templates and previous contest/practice solutions.


## Repository structure

```text
CCC/
├── Solutions/
│   ├── Participation Results/   # My real time solutions during contests
│   └── Practice/                # Solutions for past CCC problems
├── tools/
│   ├── CCCrunner.h              # Test runner library
│   ├── runner_main.h            # Runner entry point
│   ├── template.cpp             # C++ starting template
│   └── watch_ccc_downloads.py   # Automatic level downloader
└── README.md
```


## Quick start

Firstly you need to download this repository. It can also act as your coding directory during the contest and the practice runs.

### 1. Automatic level downloads

Run [`tools/watch_ccc_downloads.py`](tools/watch_ccc_downloads.py) at the beginning of the contest/practice levels.

It watches your Downloads folder for new files named like `level-1.zip`, extracts them into the configured working folder, and it can automatically add a C++ source file for coding to each extracted level. Now after clicking the Download button, you don't have to bother with extracting each level, it will automaticaly be available in your working folder.

Before running it, check the settings at the top of the script:

```python
EDITION_DIR = Path(r"C:\Programming\CCC\Testing\Edition X")
insert_cpp_template = True
```

Feel free to adjust these values to match your setup.

### 2. Configure your setup

In my current setup, I use a custom VSCode profile that opens automatically when I am working inside the CCC folder. The profile has the [Code Runner](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner) extension to easily run the C++ soulution for each level. Also, it has the [PDF Viewer](https://marketplace.visualstudio.com/items?itemName=mathematic.vscode-pdf) extention to be able to read each level requiremnts directly inside VSCode. I recommend you use the same setup but none of these extentions are required.

#### Option 1: Code Runner
Install the extension and add the following configuration to the workspace file `.vscode/settings.json`:

```json
{
  "code-runner.executorMap": {
    "cpp": "cd /d $dir && g++ -std=c++17 -I\"${workspaceRoot}/tools\" \"$fileName\" -o \"$fileNameWithoutExt.exe\" && .\\$fileNameWithoutExt.exe"
  },
  "code-runner.fileDirectoryAsCwd": true,
  "code-runner.runInTerminal": true,
}
```

This is the minimum configuration required to make it work properly.

`code-runner.fileDirectoryAsCwd` will make sure that you can run your C++ programs from anywere, while also keeping a relative working path to enable interacting with files relative to your program.

`code-runner.runInTerminal` will move the CodeRunner execution inside an interactive terminal, rather than the default OUPUT terminal.

`code-runner.executorMap` tells CodeRunner how to run your code. I assume you are fammiliar with C++ compilers and you already have one available on your computer. Here you might need to make some changes based on the compiler you are using. I understand that CodeRunner can be confusing, but if you don't manage to make it work, ask your friend Copilot to help you configure it properly.

Note that he `-I"${workspaceRoot}/tools"` option tells the compiler where to find `runner_main.h` and `CCCrunner.h`. Changing to `$dir` before running the program is also important: the runner then finds the input and expected output files relative to the current level folder. Open a level's `.cpp` file and select **Run Code** (Located in the top right corner) to compile and run it.


#### Option 2: Only the C++ compiler
If you like the manual compiling/running of the C++ files, you can alternatively run this single build and run command from a level folder (replace the source filename as needed):

```powershell
g++ -std=c++17 -I"C:\Programming\CCC\tools" solution.cpp -o solution.exe; if ($LASTEXITCODE -eq 0) { .\solution.exe }
```

The `-I` argument includes the runner headers, but make sure you modify the `"C:\Programming\CCC\tools"` path to where you actually downloaded the repository. In my case it's located under `"C:\Programming\"`. The `-std=c++17` sets the minimum C++ standard to 17 as it is required the templates. Running the command from the level folder keeps the runner's relative file paths working.


## How to use the C++ Runner

### 1. Implement the solution

If you are using the [`watcher python script`](tools/watch_ccc_downloads.py), there will be already a source file named `level-X.cpp` inside the extracted level. You just need to open it and start coding. If that's not the case, just copy [`tools/template.cpp`](tools/template.cpp) into the folder for your level.

First thing first, make sure that the configurations at the top satisfy your requirements:
```cpp
config.example_input = "in_level-1_0-example.txt";
config.expected_output = "out_level-1_0-example.txt";
config.input_dir = ".";
config.output_dir = "results";
```

Then define the Input/Output structs. Here you declare what kind of data you need to read everything and write the Solution.
Here is an example:
```cpp
struct Input {
    int n;
    vector<int> maps_radius;
    vector<vector<string>> maps;
};
struct Output {
    vector<vector<string>> maps;
};
```

Then implement:

- `read()` - read the input.
- `solve()` - implement the solution.
- `write()` - format the answer.

The runner entry point is already included for you. Leave this part unchanged:

```cpp
#include "runner_main.h"
```

### 2. Run one test case

Keep this setting:

```cpp
config.batch = false;
```

Running the program will display the input, your output, debug messages, and whether the answer matches the expected result.

For debug output, use:
```cpp
DBG << "Value: " << value << '\n';
```
Normal `cout <<` is discarded and won't be visible in your output.

### 3. Run all test cases

When the solution is ready, change:

```cpp
config.batch = true;
```

The runner will process every matching input file and write the generated answers to the configured `results` folder.

Batch mode disables debug output and prints a short status for every test case.


## Troubleshooting

- **`Input directory not found`**  
  Make sure `config.input_dir` points to the folder containing your input files.

- **`No matching input files found`**  
  Check `config.input_extension` and `config.input_prefix`. The runner only processes files matching both settings.

- **`Cannot open` or missing example files**  
  Check the filenames in `config.example_input` and `config.expected_output`, and make sure the program is being run from the correct level folder.

- **The watcher cannot find Downloads**  
  Make sure your Windows user has a `Downloads` folder, or update `DOWNLOADS_DIR` in [`watch_ccc_downloads.py`](tools/watch_ccc_downloads.py).

- **The watcher cannot find the edition folder**  
  Update `EDITION_DIR`. The script can create the folder for you when it starts.

- **A file was not overwritten**  
  This is intentional. The tools avoid replacing existing files so that your work is not accidentally lost.