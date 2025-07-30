// test_coherence.cpp
#include "restore/restore_coherence.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using Singularity::RestoreCoherence;

int main() {
    // 1. simulate initial coherent state
    RestoreCoherence rc("tests/");
    cv::Mat initial = cv::imread("tests/initial_context.png");
    if (initial.empty()) {
        std::cerr << "[ERROR] Could not load tests/initial_context.png" << std::endl;
        return 1;
    }
    rc.ingestContext("src/", "singularity.md", initial);
    auto delta1 = rc.computeDelta();
    std::cout << "Initial entropy: " << delta1.entropyScore << std::endl;

    // 2. simulate drift: modify code base or metadata
    cv::Mat drifted = cv::imread("tests/drifted_context.png");
    if (drifted.empty()) {
        std::cerr << "[ERROR] Could not load tests/drifted_context.png" << std::endl;
        return 1;
    }
    rc.ingestContext("src/", "singularity_v2.md", drifted);
    auto delta2 = rc.computeDelta();
    std::cout << "After drift entropy: " << delta2.entropyScore << std::endl;

    // 3. export .aic for restoration
    if (rc.exportAICFrame("schema/coherence_frame_20250729T200000Z")) {
        std::cout << "AIC frame exported successfully." << std::endl;
    } else {
        std::cerr << "[ERROR] Failed to export AIC frame." << std::endl;
        return 1;
    }
    return 0;
}
