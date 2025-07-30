// restore_coherence.cpp
#include "restore_coherence.h"
#include "topography_manager.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>    // for JSON output
#include <iostream>

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
    std::cout << "[RESTORE] ingestContext: begin" << std::endl;
    // 1. snapshot filenames
    for (auto& p : fs::recursive_directory_iterator(codeDir))
        if (p.path().extension() == ".cpp" || p.path().extension() == ".h")
            codeSnapshots_.push_back(p.path().string());

    // 2. load metadata (optional)
    // e.g., parse singularity.md, README.md

    // 3. store image
    lastContextImage_ = contextImage.clone();
    std::cout << "[RESTORE] ingestContext: end" << std::endl;
}

CoherenceDelta RestoreCoherence::computeDelta() {
    std::cout << "[RESTORE] computeDelta: begin" << std::endl;
    double codeE  = analyzeCodeEntropy();
    double imageE = analyzeImageEntropy(lastContextImage_);
    // simple weighted average
    lastDelta_.entropyScore = (codeE * 0.7) + (imageE * 0.3);
    lastDelta_.timestamp    = std::chrono::system_clock::now();
    std::cout << "[RESTORE] computeDelta: end" << std::endl;
    return lastDelta_;
}

bool RestoreCoherence::exportAICFrame(const std::string& outPath) {
    std::cout << "[RESTORE] exportAICFrame: begin" << std::endl;
    // 1. compute latest delta
    computeDelta();

    // 2. generate topographic/tachyonic layer
    topographicLayer_ = Singularity::generateTachyonicTopography(200, 200, topoSeed_, topoDensity_);
    std::string topoPngPath = outPath + "_topographic.png";
    cv::imwrite(topoPngPath, topographicLayer_);

    // 3. write JSON
    json j;
    j["timestamp"]     = makeTimestamp();
    j["entropyScore"]  = lastDelta_.entropyScore;
    j["codeSnapshots"] = codeSnapshots_;
    j["topographicLayer"] = {
        {"type", "tachyonic"},
        {"dimensions", {200, 200}},
        {"encoding", "fractal-noise"},
        {"seed", topoSeed_},
        {"density", topoDensity_},
        {"data", topoPngPath}
    };
    j["baselayer"] = {
        {"type", "high-density"},
        {"scaffold", "AINLP"},
        {"description", "Auto-coder stimulation layer for recursive context growth"}
    };
    j["hyperlayer"] = {
        {"abstract", "Synthetic tachyonic field mimicking bosonic substrate"},
        {"notes", "AINLP: This layer encodes digital context for future AI deep reading and codebase evolution."}
    };
    std::ofstream(outPath + ".json") << j.dump(4);

    // 4. save image snapshot
    bool result = cv::imwrite(outPath + ".png", lastContextImage_);
    std::cout << "[RESTORE] exportAICFrame: end" << std::endl;
    return result;
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
