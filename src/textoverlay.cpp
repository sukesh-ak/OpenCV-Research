/*
      Activate the default camera and draws a message on it.
*/

#include "textoverlay.hpp"

using namespace std;
using namespace cv;
using std::cout;

void drawText(Mat &image)
{
      putText(image, "Hello OpenCV",
              Point(20, 50),
              FONT_HERSHEY_COMPLEX, 1, // font face and scale
              Scalar(255, 255, 255),   // white
              1, LINE_AA);             // line thickness and type
}

void textOverlay()
{
      cout << "Built with OpenCV " << CV_VERSION << endl;
      Mat image;
      VideoCapture capture;
      capture.open(0); // capture.open(0,CAP_V4L2);

      if (capture.isOpened())
      {
            cout << "Capture is opened" << endl;
            for (;;)
            {
                  capture >> image;
                  if (image.empty())
                        break;
                  drawText(image);
                  imshow("Sample", image);
                  if (waitKey(10) >= 0)
                        break;
            }
      }
      else
      {
            cout << "No capture" << endl;
            image = Mat::zeros(480, 640, CV_8UC1);
            drawText(image);
            imshow("Sample", image);
            waitKey(0);
      }
}
