#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string.h>
#include <string>
#include <sstream>

#include <yaml-cpp/yaml.h>

#include "theme.h"

#include "theme_parser.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::map ;
using std::ofstream;
using std::string;
using std::stringstream;

using YAML::Parser;

string get_current_theme(string path) {

  string line;

  ifstream current_theme_file (path);
  getline (current_theme_file,line);

  current_theme_file.close();
  
  return line;
}

void set_current_theme(string path, string theme_name) {

  string line;

  ofstream current_theme_file (path);

  current_theme_file.write(theme_name.c_str(), theme_name.size());

  current_theme_file.flush();
  current_theme_file.close();
}

void print_themes(map<string, Theme> & themes) {
  for(auto & theme : themes) {
    cout << theme.first << " ";
  }
}

void print_commands(Theme & theme) {
  for(auto & command : theme._commands) {
    cout << command.first << endl;
  }
}

map<string, Theme> load_themes(string & themes_path) {
  std::ifstream fin(themes_path);
  Parser p;
  p.Load(fin);
  ThemeParser parser;
  p.HandleNextDocument(parser);
  return parser._themes;
}
  
int main(int argc, char *argv[]) {
  string current_theme_path = "/home/segfault/.tapetenwechsel/current_theme";
  string themes_path = "/home/segfault/.tapetenwechsel/themes.yaml";
  
  string current_theme = get_current_theme(current_theme_path);
 
  auto themes = load_themes(themes_path); 
  
  std::vector<std::string> arguments;

  if(argc < 2){
    string command;

    cin >> command;
    while (!cin.eof()) {
      cout << command << endl;

      if(!command.empty()){
	arguments.push_back(command);
      }
      cin >> command;
    } 
  } else {
    for(auto i=1; i<argc; ++i) {
      arguments.push_back(argv[i]);
    }
  }

  for (uint i = 0; i < arguments.size(); ++i) {
    string option = arguments[i];

    if(!option.compare("-h")) {
      std::cout << "Usage: tapetenwechsel [OPTION] ... [PROGRAMM] " << endl <<
	"Starts PROGRAMM with specific color themes, chanes running " <<
	"programms according to specified theme. " << endl <<
	"  Options: " << endl <<
	"     -h              Prints this help" << endl <<
	"     -s THEMENAME    Sets the given theme name" << endl <<
	"     -g              Prints current theme name" << endl <<
	"     -t              Prints all available themes" << endl <<
	"     -c              Lists available commands for current " << 
	"theme" << endl <<	
	"     -f PATH         Loads themes from given path" << endl;

    } else if(!option.compare("-s")) {
      auto theme_name = arguments[++i];

      if(themes.count(theme_name) < 1) {
	std::cerr << "No theme named \"" << theme_name
		  << "\" in \"" << themes_path << "\"" << endl;
	return EXIT_FAILURE;
      }
      
      set_current_theme(current_theme_path, theme_name);
      themes[theme_name].activate();      
    } else if(!option.compare("-g")) {
      cout << get_current_theme(current_theme_path) << endl;	
    } else if(!option.compare("-c")) {
      print_commands(themes[current_theme]);
    } else if(!option.compare("-t")) {
      print_themes(themes);
    } else if(!option.compare("-f")) {
      themes_path = arguments[++i];
      themes = load_themes(themes_path);   
    } else if(option[0] == '-') {
      std::cerr << "Unknown option: \"" << option << "\"" << endl;
      return EXIT_FAILURE;
    } else {
      themes[current_theme].execute(option);      
    }
  }

  return EXIT_SUCCESS;
}

