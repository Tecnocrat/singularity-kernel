// Path: singularity-kernel/src/coherence.h
// coherence.h
#pragma once
#include <string>
#include <random>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>

struct DivergenceNode {
    std::string idea;
    double resonanceScore;
};

class CoherenceEngine {
public:
    std::vector<DivergenceNode> memory_lattice;

    void inject(std::string seedPhrase) {
        double score = mutate(seedPhrase);
        memory_lattice.push_back({seedPhrase, score});
    }

    void display() {
        for (auto& node : memory_lattice) {
            std::cout << "[COHERENCE] " << node.idea 
                      << " :: Resonance Score = " << node.resonanceScore << std::endl;
        }
    }

    // Move a file to a new location (creates target directory if needed)
    bool moveFile(const std::string& source, const std::string& destination) {
        try {
            std::filesystem::path destPath(destination);
            std::filesystem::create_directories(destPath.parent_path());
            std::filesystem::rename(source, destination);
            return true;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "[COHERENCE] File move failed: " << e.what() << std::endl;
            return false;
        }
    }

    // Signal VSCode to trigger a rebuild/run if kernel logic requests it
    void requestRebuild() {
        std::ofstream flag(".singularity-rebuild-request");
        flag << "rebuild requested" << std::endl;
        flag.close();
        std::cout << "[KERNEL] Rebuild request signal written to .singularity-rebuild-request" << std::endl;
    }

    // Generate a randomized fractal noise vector (for demonstration)
    std::vector<double> generateFractalNoise(int size, int octaves = 4) {
        std::vector<double> noise(size, 0.0);
        std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int o = 0; o < octaves; ++o) {
            double freq = std::pow(2.0, o);
            double amp = std::pow(0.5, o);
            for (int i = 0; i < size; ++i) {
                noise[i] += amp * dist(rng) * std::sin(freq * i * 0.1);
            }
        }
        return noise;
    }

private:
    double mutate(const std::string& phrase) {
        std::hash<std::string> hasher;
        return static_cast<double>(hasher(phrase) % 10000) / 100.0;
    }
};

namespace MarkdownManager {
    // Move all non-README .md files from project root to /md folder
    void organizeMarkdownFiles(const std::string& projectRoot) {
        namespace fs = std::filesystem;
        fs::path root(projectRoot);
        fs::path mdDir = root / "md";
        fs::create_directories(mdDir);
        for (const auto& entry : fs::directory_iterator(root)) {
            if (entry.is_regular_file()) {
                auto path = entry.path();
                if (path.extension() == ".md" && path.filename() != "README.md") {
                    fs::path dest = mdDir / path.filename();
                    try {
                        fs::rename(path, dest);
                        std::cout << "[MD] Moved: " << path << " -> " << dest << std::endl;
                    } catch (const fs::filesystem_error& e) {
                        std::cerr << "[MD] Move failed: " << e.what() << std::endl;
                    }
                }
            }
        }
    }
}