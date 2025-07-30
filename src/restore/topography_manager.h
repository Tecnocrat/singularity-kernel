// Path: singularity-kernel/src/restore/topography_manager.h
#pragma once
#include <opencv2/opencv.hpp>

namespace Singularity {
    cv::Mat generateTachyonicTopography(int w, int h, int seed, double density);
}
