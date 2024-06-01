#include <opencv2/opencv.hpp>
#include <cstdlib>

int main() {
    // Open the default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Define the starting X coordinate of the rectangle
    int progressBarX = 20;  // Fixed starting X coordinate

    // Define the Y coordinate of the rectangle
    int progressBarY = 20;  // Y coordinate

    // Loop to capture video frames
    while (true) {
        // Capture frame-by-frame
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Could not grab a frame." << std::endl;
            break;
        }

        // Generate a random width for the rectangle
        int progressBarWidth = std::rand() % 100 + 1;  // Random width from 1 to 100

        // Create a separate rectangle with transparency
        cv::Mat transparentRect(frame.size(), CV_8UC4, cv::Scalar(0, 0, 0, 0)); // Ensure the same size as the frame
        cv::rectangle(transparentRect, 
                        cv::Rect(progressBarX, progressBarY, progressBarWidth, 20), 
                        cv::Scalar(0, 255, 0, 150), -1); // 204 for 80% transparency

        // Blend the transparent rectangle with the frame
        cv::Mat blendedFrame;
        cv::addWeighted(frame, 1.0, transparentRect, 0.8, 0.0, blendedFrame);

        // Display the frame with the transparent rectangle
        cv::imshow("Video with Transparent Rectangle", blendedFrame);

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
