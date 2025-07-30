// Path: singularity-kernel/src/restore/restore_coherence.h
// restore_coherence.h
#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>   // for 2D image ingestion/export

namespace Singularity {

    struct CoherenceDelta {
        double entropyScore;
        std::chrono::system_clock::time_point timestamp;
    };

    class RestoreCoherence {
    public:
        RestoreCoherence(const std::string& projectRoot);
        ~RestoreCoherence();

        // 1️⃣ Ingest current context from code, metadata, and reference image
        void ingestContext(const std::string& codeDir,
                           const std::string& metadataFile,
                           const cv::Mat& contextImage);

        // 2️⃣ Measure “distance” from ideal coherence
        CoherenceDelta computeDelta();

        // 3️⃣ Export a .aic state frame (JSON + PNG snapshot)
        bool exportAICFrame(const std::string& outPath);

    private:
        std::string rootPath_;
        std::vector<std::string> codeSnapshots_;
        cv::Mat lastContextImage_;
        CoherenceDelta lastDelta_;
        // Topographic/tachyonic context
        cv::Mat topographicLayer_;
        int topoSeed_ = 42;
        double topoDensity_ = 0.97;

        // Helpers
        double analyzeCodeEntropy();
        double analyzeImageEntropy(const cv::Mat& img);
        std::string makeTimestamp();
    };
}
