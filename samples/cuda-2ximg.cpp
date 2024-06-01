#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/highgui.hpp>

void resizeWithAspectRatio(const cv::cuda::GpuMat& src, cv::cuda::GpuMat& dst, int height) {
    int originalHeight = src.rows;
    int originalWidth = src.cols;
    float aspectRatio = static_cast<float>(originalWidth) / originalHeight;
    int newWidth = static_cast<int>(height * aspectRatio);

    cv::cuda::resize(src, dst, cv::Size(newWidth, height));
}

int main() {
    // Read the two images
    cv::Mat img1 = cv::imread("windows.jpg");
    cv::Mat img2 = cv::imread("linux.jpg");

    // Check if images are loaded
    if (img1.empty() || img2.empty()) {
        std::cerr << "Could not read one of the images" << std::endl;
        return 1;
    }

    // Upload images to GPU
    cv::cuda::GpuMat d_img1, d_img2;
    d_img1.upload(img1);
    d_img2.upload(img2);

    // Set the target height (the minimum height of the two images)
    int targetHeight = std::min(d_img1.rows, d_img2.rows);

    // Resize the images to the target height while maintaining aspect ratio
    cv::cuda::GpuMat d_resized1, d_resized2;
    resizeWithAspectRatio(d_img1, d_resized1, targetHeight);
    resizeWithAspectRatio(d_img2, d_resized2, targetHeight);

    // Create a new image with the combined width and same height on GPU
    int combinedWidth = d_resized1.cols + d_resized2.cols;
    cv::cuda::GpuMat d_combinedImage(targetHeight, combinedWidth, d_resized1.type());

    // Copy the first image to the left half
    d_resized1.copyTo(d_combinedImage(cv::Rect(0, 0, d_resized1.cols, targetHeight)));

    // Copy the second image to the right half
    d_resized2.copyTo(d_combinedImage(cv::Rect(d_resized1.cols, 0, d_resized2.cols, targetHeight)));

    // Download the combined image back to CPU
    cv::Mat combinedImage;
    d_combinedImage.download(combinedImage);

    // Display the combined image
    //cv::namedWindow("Combined Image", cv::WINDOW_NORMAL);
    cv::imshow("Combined Image", combinedImage);
    cv::waitKey(0);

    return 0;
}
