// test_coherence.cpp
#include "restore_coherence.h"
#include <opencv2/opencv.hpp>

int main() {
    // 1. simulate initial coherent state
    RestoreCoherence rc("C:/users/jesus/dev/cpp/singularity_kernel");
    cv::Mat initial = cv::imread("initial_context.png");
    rc.ingestContext("src/", "singularity.md", initial);
    auto delta1 = rc.computeDelta();
    std::cout << "Initial entropy: " << delta1.entropyScore << std::endl;

    // 2. simulate drift: modify code base or metadata
    // (in real test, rename/remove files, alter md, shift image)
    cv::Mat drifted = cv::imread("drifted_context.png");
    rc.ingestContext("src_modified/", "singularity_v2.md", drifted);
    auto delta2 = rc.computeDelta();
    std::cout << "After drift entropy: " << delta2.entropyScore << std::endl;

    // 3. export .aic for restoration
    if (rc.exportAICFrame("coherence_frame_20250729T200000Z")) {
        std::cout << "AIC frame exported successfully." << std::endl;
    }
    return 0;
}
