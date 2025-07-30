// test_coherence.cpp
#include "restore/restore_coherence.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using Singularity::RestoreCoherence;

int main() {
    // 1. simulate initial coherent state
    std::cout << "[TEST] Initializing RestoreCoherence..." << std::endl;
    RestoreCoherence rc("tests/");
    std::cout << "[TEST] Reading initial image..." << std::endl;
    cv::Mat initial = cv::imread("tests/initial_context.png");
    if (initial.empty()) {
        std::cerr << "[ERROR] Could not load tests/initial_context.png" << std::endl;
        return 1;
    }
    std::cout << "[TEST] Ingesting initial context..." << std::endl;
    rc.ingestContext("src/", "singularity.md", initial);
    std::cout << "[TEST] Computing initial delta..." << std::endl;
    auto delta1 = rc.computeDelta();
    std::cout << "Initial entropy: " << delta1.entropyScore << std::endl;

    // 2. simulate drift: modify code base or metadata
    std::cout << "[TEST] Reading drifted image..." << std::endl;
    cv::Mat drifted = cv::imread("tests/drifted_context.png");
    if (drifted.empty()) {
        std::cerr << "[ERROR] Could not load tests/drifted_context.png" << std::endl;
        return 1;
    }
    std::cout << "[TEST] Ingesting drifted context..." << std::endl;
    rc.ingestContext("src/", "singularity_v2.md", drifted);
    std::cout << "[TEST] Computing drifted delta..." << std::endl;
    auto delta2 = rc.computeDelta();
    std::cout << "After drift entropy: " << delta2.entropyScore << std::endl;

    // 3. export .aic for restoration
    std::cout << "[TEST] Exporting AIC frame..." << std::endl;
    if (rc.exportAICFrame("schema/coherence_frame_20250729T200000Z")) {
        std::cout << "AIC frame exported successfully." << std::endl;
    } else {
        std::cerr << "[ERROR] Failed to export AIC frame." << std::endl;
        return 1;
    }
    std::cout << "[TEST] Done." << std::endl;
    return 0;
}
