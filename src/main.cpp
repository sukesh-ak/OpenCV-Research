/*
      OpenCV-Research
      By Sukesh Ashok Kumar

      using https://github.com/jarro2783/cxxopts/ for command line parsing.
*/
#include <iostream>
#include <cxxopts.hpp>

#include "version.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
using std::cout;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta1;
Mat src1;
Mat src2;
Mat dst;

static void on_trackbar( int, void* )
{
 alpha = (double) alpha_slider/alpha_slider_max ;
 beta1 = ( 1.0 - alpha );
 addWeighted( src1, alpha, src2, beta1, 0.0, dst);
 imshow( "Linear Blend", dst );
}

/*
* Usage : ./opencvr -t "hello" -d true -n 10 -f hhh.txt -f aaa.txt
* Usage : ./opencvr -h
*/
void parse(int argc, const char* argv[])
{
   try
   {
      cxxopts::Options options("cmdargs", "CLI with arguments");

      options.add_options()
            ("t,textvalue", "Param text value", cxxopts::value<string>())
            ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
            ("n,number", "Param number", cxxopts::value<int>()->default_value("11"))
            ("f,file", "File", cxxopts::value<std::vector<std::string>>(), "FILE")
            ("h,help", "Print usage")
      ;

      auto result = options.parse(argc, argv);

      if (result.count("help"))
      {
            cout << options.help() << endl;
            exit(0);
      }

      bool debug = result["debug"].as<bool>();
      cout << "debug: " << debug << endl;

      string textvalue;
      if (result.count("textvalue"))
      {
            textvalue = result["textvalue"].as<string>();
            cout << "textvalue: " << textvalue << endl;
      }

      int number = result["number"].as<int>(); 
      cout << "number: " << number << endl;

      if (result.count("f"))
      {
      auto& ff = result["f"].as<std::vector<std::string>>();
      std::cout << "Files" << std::endl;
      for (const auto& f : ff)
      {
            std::cout << "\t" << f << std::endl;
      }
      }

   }
   catch (const cxxopts::OptionException& e)
   {
      std::cout << "error parsing options: " << e.what() << endl;
      exit(1);
   }
}

int main(int argc, const char* argv[])
{
      
#ifdef __linux__
      cout << GREEN ;
      cout << "OpenCV Research" << endl;
      cout << "Built with OpenCV " << CV_VERSION << endl;
      cout << RESET ;      
#else
      cout << "OpenCV Research" << endl;
      cout << "Built with OpenCV " << CV_VERSION << endl;
#endif      
      cout << "Version: " << OpencvRVersion << endl;

      
      parse(argc, argv);

      src1 = imread( samples::findFile("linux.jpg") );
      src2 = imread( samples::findFile("windows.jpg") );
      if( src1.empty() ) { cout << "Error loading src1 \n"; return -1; }
      if( src2.empty() ) { cout << "Error loading src2 \n"; return -1; }
      alpha_slider = 0;
      namedWindow("Linear Blend", WINDOW_AUTOSIZE); // Create Window
      char TrackbarName[50];
      sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
      createTrackbar( TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar );
      on_trackbar( alpha_slider, 0 );
      waitKey(0);

  return 0;
}