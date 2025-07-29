// restore_coherence.cpp
#include "restore_coherence.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>    // for JSON output

using namespace Singularity;
namespace fs = std::filesystem;
using json = nlohmann::json;

RestoreCoherence::RestoreCoherence(const std::string& projectRoot)
  : rootPath_(projectRoot) {}

RestoreCoherence::~RestoreCoherence() {}

void RestoreCoherence::ingestContext(const std::string& codeDir,
                                     const std::string& metadataFile,
                                     const cv::Mat& contextImage)
{
    // 1. snapshot filenames
    for (auto& p : fs::recursive_directory_iterator(codeDir))
        if (p.path().extension() == ".cpp" || p.path().extension() == ".h")
            codeSnapshots_.push_back(p.path().string());

    // 2. load metadata (optional)
    // e.g., parse singularity.md, README.md

    // 3. store image
    lastContextImage_ = contextImage.clone();
}

CoherenceDelta RestoreCoherence::computeDelta() {
    double codeE  = analyzeCodeEntropy();
    double imageE = analyzeImageEntropy(lastContextImage_);
    // simple weighted average
    lastDelta_.entropyScore = (codeE * 0.7) + (imageE * 0.3);
    lastDelta_.timestamp    = std::chrono::system_clock::now();
    return lastDelta_;
}

bool RestoreCoherence::exportAICFrame(const std::string& outPath) {
    // 1. compute latest delta
    computeDelta();

    // 2. write JSON
    json j;
    j["timestamp"]     = makeTimestamp();
    j["entropyScore"]  = lastDelta_.entropyScore;
    j["codeSnapshots"] = codeSnapshots_;
    std::ofstream(outPath + ".json") << j.dump(4);

    // 3. save image snapshot
    return cv::imwrite(outPath + ".png", lastContextImage_);
}

// — Helpers —
double RestoreCoherence::analyzeCodeEntropy() {
    // stub: hash file names count
    return static_cast<double>(codeSnapshots_.size());
}

double RestoreCoherence::analyzeImageEntropy(const cv::Mat& img) {
    // stub: use pixel variance
    cv::Mat gray, lap;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::Laplacian(gray, lap, CV_64F);
    cv::Scalar mu, sigma;
    cv::meanStdDev(lap, mu, sigma);
    return sigma[0];
}

std::string RestoreCoherence::makeTimestamp() {
    auto now = std::chrono::system_clock::to_time_t(lastDelta_.timestamp);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&now));
    return buf;
}
