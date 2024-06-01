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

        // Create a rectangle to represent the region of interest (ROI)
        cv::Rect roiRect(progressBarX, progressBarY, progressBarWidth, 20); // Height is fixed to 20 pixels

        // Fill the ROI with a fluorescent green color
        cv::rectangle(frame, roiRect, cv::Scalar(0, 255, 0), -1);  // -1 for filled rectangle

        // Display the frame with the dynamically changing rectangle
        cv::imshow("Video with Dynamic Rectangle", frame);

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
