#ifndef __THEME_H
#define __THEME_H

#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using std::map;
using std::pair;
using std::string;
using std::vector;

class Theme {
 public:
  string _name;
  string _generic;  

  map<string, string> _commands;
  vector<string> _activations;
  
  Theme(); 
  Theme(string name);  
  Theme(string name, string generic);

  void activate();
  void add_command(string  name, string command);
  void add_activaton(string command);
  
  void execute(string command);
  void set_generic(string generic);
};

#endif
