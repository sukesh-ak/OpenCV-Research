/*
    Not working yet
*/
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/opengl.hpp>
#include <GL/gl.h>  // Include OpenGL headers
#include <GL/glu.h>

cv::cuda::GpuMat d_frame, d_hsv, d_output;
std::vector<cv::cuda::GpuMat> hsv_channels;

int hue = 100;        // Initial hue value (100% means no change)
int saturation = 100; // Initial saturation value (100% means no change)
int brightness = 100; // Initial brightness value (100% means no change)

// Trackbar callback function
void onTrackbarChange(int, void* userdata) {
    // Get the trackbar values directly
    hue = cv::getTrackbarPos("Hue", "CUDA Video");
    saturation = cv::getTrackbarPos("Saturation", "CUDA Video");
    brightness = cv::getTrackbarPos("Brightness", "CUDA Video");
}

void onOpenGLDraw(void* userdata) {
    cv::Mat* frame = static_cast<cv::Mat*>(userdata);
    if (frame == nullptr) {
        return;
    }

    cv::cuda::GpuMat d_frame;
    d_frame.upload(*frame);

    // Convert the frame to HSV color space
    cv::cuda::cvtColor(d_frame, d_hsv, cv::COLOR_BGR2HSV);

    // Split the HSV channels
    cv::cuda::split(d_hsv, hsv_channels);

    // Adjust the hue, saturation, and brightness channels
    float hue_factor = hue / 100.0f;
    float sat_factor = saturation / 100.0f;
    float bright_factor = brightness / 100.0f;

    cv::cuda::addWeighted(hsv_channels[0], hue_factor, hsv_channels[0], 0, 0, hsv_channels[0]);
    cv::cuda::multiply(hsv_channels[1], sat_factor, hsv_channels[1]);
    cv::cuda::multiply(hsv_channels[2], bright_factor, hsv_channels[2]);

    // Merge the channels back
    cv::cuda::merge(hsv_channels, d_hsv);

    // Convert back to BGR color space
    cv::cuda::cvtColor(d_hsv, d_output, cv::COLOR_HSV2BGR);

    // Download the output frame back to CPU
    cv::Mat outputFrame;
    d_output.download(outputFrame);

    // Display the frame using OpenGL
    cv::ogl::Texture2D texture(outputFrame);
    texture.bind();
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

int main() {
    // Open the default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Create a window
    cv::namedWindow("CUDA Video", cv::WINDOW_OPENGL);

    // Create trackbars for hue, saturation, and brightness adjustment
    cv::createTrackbar("Hue", "CUDA Video", nullptr, 200, onTrackbarChange);
    cv::createTrackbar("Saturation", "CUDA Video", nullptr, 200, onTrackbarChange);
    cv::createTrackbar("Brightness", "CUDA Video", nullptr, 200, onTrackbarChange);

    // Set the OpenGL draw callback
    cv::setOpenGlDrawCallback("CUDA Video", onOpenGLDraw, nullptr);

    // Loop to capture video frames
    while (true) {
        // Capture frame-by-frame
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Could not grab a frame." << std::endl;
            break;
        }

        // Trigger the OpenGL callback to draw the frame
        cv::updateWindow("CUDA Video");

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
