#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>

// Trackbar callback function
void onTrackbarChange(int, void*) {
    // Trackbar callback function, does nothing
    // The actual processing will use the trackbar values directly
}

int main() {
    // Open the default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Create a window
    cv::namedWindow("CUDA Video", cv::WINDOW_NORMAL);

    // Create trackbars for hue, saturation, and brightness adjustment
    int hue = 100; // initial hue value (100% means no change)
    int saturation = 100; // initial saturation value (100% means no change)
    int brightness = 100; // initial brightness value (100% means no change)
    cv::createTrackbar("Hue", "CUDA Video", &hue, 200, onTrackbarChange);
    cv::createTrackbar("Saturation", "CUDA Video", &saturation, 200, onTrackbarChange);
    cv::createTrackbar("Brightness", "CUDA Video", &brightness, 200, onTrackbarChange);

    // Loop to capture video frames
    while (true) {
        // Capture frame-by-frame
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Could not grab a frame." << std::endl;
            break;
        }

        // Upload the frame to GPU
        cv::cuda::GpuMat d_frame;
        d_frame.upload(frame);

        // Convert the frame to HSV color space
        cv::cuda::GpuMat d_hsv;
        cv::cuda::cvtColor(d_frame, d_hsv, cv::COLOR_BGR2HSV);

        // Split the HSV channels
        std::vector<cv::cuda::GpuMat> hsv_channels;
        cv::cuda::split(d_hsv, hsv_channels);

        // Adjust the hue, saturation, and brightness channels
        float hue_factor = hue / 100.0f;
        float sat_factor = saturation / 100.0f;
        float bright_factor = brightness / 100.0f;

        cv::cuda::GpuMat d_hue, d_sat, d_val;
        cv::cuda::addWeighted(hsv_channels[0], hue_factor, hsv_channels[0], 0, 0, hsv_channels[0]);
        cv::cuda::multiply(hsv_channels[1], sat_factor, hsv_channels[1]);
        cv::cuda::multiply(hsv_channels[2], bright_factor, hsv_channels[2]);

        // Merge the channels back
        cv::cuda::GpuMat d_adjusted_hsv;
        cv::cuda::merge(hsv_channels, d_adjusted_hsv);

        // Convert back to BGR color space
        cv::cuda::GpuMat d_output;
        cv::cuda::cvtColor(d_adjusted_hsv, d_output, cv::COLOR_HSV2BGR);

        // Download the output frame back to CPU
        cv::Mat outputFrame;
        d_output.download(outputFrame);

        // Show the frame with adjusted hue, saturation, and brightness
        cv::imshow("CUDA Video", outputFrame);

        // Break the loop on 'q' key press
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
