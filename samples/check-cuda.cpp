#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <iostream>

int main() {
    std::cout << cv::getBuildInformation() << std::endl;

    if (cv::cuda::getCudaEnabledDeviceCount() > 0) {
        std::cout << "CUDA is available on this system." << std::endl;
    } else {
        std::cout << "CUDA is not available on this system." << std::endl;
    }

    return 0;
}