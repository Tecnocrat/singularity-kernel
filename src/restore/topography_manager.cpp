// Path: singularity-kernel/src/restore/topography_manager.cpp
#include "topography_manager.h"
#include <random>

namespace Singularity {
cv::Mat generateTachyonicTopography(int w, int h, int seed, double density) {
    cv::Mat topo(h, w, CV_8UC1);
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0, 1);
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            topo.at<uchar>(y, x) = (dis(gen) < density) ? static_cast<uchar>(255 * dis(gen)) : 0;
    return topo;
}
}
