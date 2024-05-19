/*
      OpenCV-Research
      By Sukesh Ashok Kumar

      Relevant OpenCV examples for Vision AI

      using https://github.com/jarro2783/cxxopts/ for command line parsing.
*/
#include <iostream>
#include <cxxopts.hpp>
#include "version.hpp"

#include "textoverlay.hpp"
#include "drawoverlay.hpp"
#include "imageoverlay.hpp"
#include "facedetection.hpp"

using namespace std;

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

/*
* Usage : ./opencvr -t "hello" -d true -n 10 -f hhh.txt -f aaa.txt
* Usage : ./opencvr -h
*/
void parse(int argc, const char* argv[])
{
   try
   {
      cxxopts::Options options("opencvr", "CLI with arguments");

      options.add_options("Demo Group")
            ("v,verb", "Verb - textcam, shape, detect, imgcam", cxxopts::value<string>())
            ("demotype", "Demo Type", cxxopts::value<string>())
            ("h,help", "Print usage")
      ;

      options.add_options("Group2")
            ("t,textvalue", "Param text value", cxxopts::value<string>())
            ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
            ("n,number", "Param number", cxxopts::value<int>()->default_value("11"))
            ("f,file", "File - comma separated", cxxopts::value<std::vector<std::string>>(), "FILE")
      ;

      // Positional for verb to be first argument
      options.parse_positional({"verb"});
      options.custom_help("<VERB>");
      options.positional_help("<parameters>");

      //options.group_help("Overlay");
      
      auto result = options.parse(argc, argv);

      // Show help
      if (result.count("help"))
      {
            cout << options.help() << endl;
            exit(0);
      }

      // Enable debug output
      bool debug = result["debug"].as<bool>();
      cout << "debug: " << debug << endl;

      string verbvalue;
      if (result.count("verb"))
      {
            verbvalue = result["verb"].as<string>();
            cout << "Verb: " << verbvalue << endl;

            // Different options with VERBS
            if      (verbvalue == "textcam")      { textOverlay(); }    // Draw Text on Default Camera
            else if (verbvalue == "shape")       { drawOverlay() ;}    // Draw Shapes in a window
            else if (verbvalue == "imgcam")       { imageOverlay() ;}    // Draw Shapes in a window
            else if (verbvalue == "detect")       { faceDetect() ;}     // Detect face on camera

            
      }

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
   catch (const cxxopts::exceptions::exception& e)
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

  return 0;
}