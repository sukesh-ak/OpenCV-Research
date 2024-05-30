/*
      OpenCV-Research
      By Sukesh Ashok Kumar

      Relevant OpenCV examples for Vision AI

      using https://github.com/jarro2783/cxxopts/ for command line parsing.
*/
#include <iostream>
#include <signal.h>
#include <cxxopts.hpp>
#include "version.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>

#include "textoverlay.hpp"
#include "drawoverlay.hpp"
#include "imageoverlay.hpp"
#include "facedetection.hpp"

using namespace std;

#define RESET "\033[0m"
#define BLACK "\033[30m"            /* Black */
#define RED "\033[31m"              /* Red */
#define GREEN "\033[32m"            /* Green */
#define YELLOW "\033[33m"           /* Yellow */
#define BLUE "\033[34m"             /* Blue */
#define MAGENTA "\033[35m"          /* Magenta */
#define CYAN "\033[36m"             /* Cyan */
#define WHITE "\033[37m"            /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */

bool signal_recieved = false;
void sig_handler(int signo)
{
      if (signo == SIGINT)
      {
            cout << "received SIGINT\n";
            signal_recieved = true;
      }
}

/*
 * Usage : ./opencvr -t "hello" -d true -n 10 -f hhh.txt -f aaa.txt
 * Usage : ./opencvr -h
 */
void parse(int argc, const char *argv[])
{
      try
      {
            cxxopts::Options options("opencvr"); //, "opencvr with arguments"

            options.add_options("Demo Group")
                ("v,verb", "Verb - textcam, shape, detect, imgcam", cxxopts::value<string>())
                ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))("h,help", "Print usage");

            // options.add_options("Group2")
            //       ("t,textvalue", "Param text value", cxxopts::value<string>())
            //       ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
            //       ("n,number", "Param number", cxxopts::value<int>()->default_value("11"))
            //       ("f,file", "File - comma separated", cxxopts::value<std::vector<std::string>>(), "FILE")
            // ;

            // Positional for verb to be first argument
            options.parse_positional({"verb"});
            options.custom_help("[textcam/shape/detect/imgcam]");
            // options.positional_help("<parameters>");
            // options.show_positional_help();
            // options.group_help("Overlay");

            auto result = options.parse(argc, argv);

            // Show help
            if (result.count("help"))
            {
                  cout << options.help() << endl;
                  exit(0);
            }

            // Enable debug output
            bool debug = false;
            if (result.count("debug"))
            {
                  debug = result["debug"].as<bool>();
                  cout << "debug: " << debug << endl;
            }

            string verbvalue;
            if (result.count("verb"))
            {
                  verbvalue = result["verb"].as<string>();
                  cout << "Verb: " << verbvalue << endl;

                  // Different options with VERBS
                  if (verbvalue == "textcam")
                  {
                        textOverlay();
                  } // Draw Text on Default Camera
                  else if (verbvalue == "shape")
                  {
                        drawOverlay();
                  } // Draw Shapes in a window
                  else if (verbvalue == "imgcam")
                  {
                        imageOverlay();
                  } // Draw Shapes in a window
                  else if (verbvalue == "detect")
                  {
                        faceDetect();
                  } // Detect face on camera
            }

            string textvalue;
            if (result.count("textvalue"))
            {
                  textvalue = result["textvalue"].as<string>();
                  cout << "textvalue: " << textvalue << endl;
            }

            int number = 0;
            if (result.count("number"))
            {
                  number = result["number"].as<int>();
                  cout << "number: " << number << endl;
            }

            if (result.count("f"))
            {
                  auto &ff = result["f"].as<std::vector<std::string>>();
                  std::cout << "Files" << std::endl;
                  for (const auto &f : ff)
                  {
                        std::cout << "\t" << f << std::endl;
                  }
            }

            std::cout << "Unmatched options: ";
            for (const auto &option : result.unmatched())
            {
                  std::cout << "'" << option << "' ";
            }
            std::cout << std::endl;
      }
      catch (const cxxopts::exceptions::exception &e)
      {
            std::cout << "error parsing options: " << e.what() << endl;
            exit(1);
      }
}

int main(int argc, const char *argv[])
{

#ifdef __linux__
      cout << GREEN;
      cout << "OpenCV Research" << endl;
      cout << "Built with OpenCV " << CV_VERSION << endl;
      cout << RESET;
#else
      cout << "OpenCV Research " << "(with OpenCV - " << CV_VERSION << ")" << endl;
#endif
      cout << "Version: " << OpencvRVersion << endl
           << endl;

      cout << cv::getBuildInformation() << endl;

      if (cv::cuda::getCudaEnabledDeviceCount() > 0) {
            std::cout << "CUDA is available on this system." << std::endl;
      } else {
            std::cout << "CUDA is not available on this system." << std::endl;
      }

      /*
       * attach signal handler
       */
      if (signal(SIGINT, sig_handler) == SIG_ERR)
            cout << "can't catch SIGINT\n";

      parse(argc, argv);

      return 0;
}