#pragma once

#include "CCCrunner.h"

int main() {
    try {
        if (ccc::CCC_CONFIG.batch) {
            ccc::run_batch(ccc::CCC_CONFIG, read, solve, write);
        } else {
            ccc::run_example(ccc::CCC_CONFIG, read, solve, write);
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}
