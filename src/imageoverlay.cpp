
#include "imageoverlay.hpp"

void overlayImage(const cv::Mat &background, const cv::Mat &foreground,
                  cv::Mat &output, cv::Point2i location)
{
    background.copyTo(output);

    for (int y = std::max(location.y, 0); y < background.rows; ++y)
    {
        int fY = y - location.y;

        if (fY >= foreground.rows)
        {
            break;
        }

        for (int x = std::max(location.x, 0); x < background.cols; ++x)
        {
            int fX = x - location.x;

            if (fX >= foreground.cols)
            {
                break;
            }

            double opacity = ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3]) / 255.;

            for (int c = 0; opacity > 0 && c < output.channels(); ++c)
            {
                unsigned char foregroundPx =
                    foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx =
                    background.data[y * background.step + x * background.channels() + c];
                output.data[y * output.step + output.channels() * x + c] =
                    backgroundPx * (1. - opacity) + foregroundPx * opacity;
            }
        }
    }
}

int imageOverlay()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error opening video stream" << std::endl;
        return -1;
    }

    cv::Mat overlay = cv::imread("assets/opencv.png", cv::IMREAD_UNCHANGED);
    if (overlay.empty())
    {
        std::cerr << "Error loading overlay image" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::Mat result;

    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

        // Position to overlay the image (top-left corner)
        cv::Point location(10, 10);

        overlayImage(frame, overlay, result, location);

        cv::imshow("Camera Stream", result);

        if (cv::waitKey(1) == 'q')
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
