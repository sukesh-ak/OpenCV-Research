/*
      SIMPLE CLI TEMPLATE
      By Sukesh Ashok Kumar

      using https://github.com/jarro2783/cxxopts/ for command line parsing.
*/
#include <iostream>
#include <cxxopts.hpp>

#include "version.hpp"

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
* Usage : ./cmdargs -t "hello" -d true -n 10 -f hhh.txt -f aaa.txt
* Usage : ./cmdargs -h
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
      cout << GREEN ;
      cout << "╔═╗╦╔╦╗╔═╗╦  ╔═╗  ╔═╗╦  ╦" << endl;
      cout << "╚═╗║║║║╠═╝║  ║╣   ║  ║  ║" << endl;
      cout << "╚═╝╩╩ ╩╩  ╩═╝╚═╝  ╚═╝╩═╝╩" << endl;
      cout << RED << "Version: " << CmdArgsVersion << endl;
      cout << RESET ;      
      
      parse(argc, argv);

  return 0;
}