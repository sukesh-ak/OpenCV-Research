#include <opencv2/opencv.hpp>

int main() {
    // Read the images
    cv::Mat src1 = cv::imread("assets/windows.jpg", cv::IMREAD_UNCHANGED);
    cv::Mat src2 = cv::imread("assets/linux.jpg", cv::IMREAD_UNCHANGED);

    // Check if the images are loaded successfully
    if (src1.empty() || src2.empty()) {
        std::cerr << "Error: Could not read the images." << std::endl;
        return -1;
    }

    // Resize images to the same size (optional)
    cv::resize(src2, src2, src1.size());

    // Set the alpha blending parameters
    double alpha = 0.5;  // Alpha blending factor (0.0 - fully transparent, 1.0 - fully opaque)
    double beta = 1.0 - alpha;

    // Perform alpha blending
    cv::Mat blendedImage;
    cv::addWeighted(src1, alpha, src2, beta, 0.0, blendedImage);

    // Concatenate images horizontally
    cv::Mat result;
    cv::hconcat(src1, src2, result); // Concatenate original images horizontally
    cv::hconcat(result, blendedImage, result); // Concatenate blended image horizontally

    // Display the concatenated image
    cv::imshow("Original and Blended Images", result);
    cv::waitKey(0);

    return 0;
}
