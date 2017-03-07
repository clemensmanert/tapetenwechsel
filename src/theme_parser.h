#ifndef __THEME_PARSER_H
#define __THEME_PARSER_H

#include <iostream>

#include <yaml-cpp/anchor.h>
#include <yaml-cpp/dll.h>
#include <yaml-cpp/emitterstyle.h>
#include <yaml-cpp/eventhandler.h>
#include <yaml-cpp/yaml.h>

#include "theme.h"

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::pair;

using YAML::EmitterStyle;
using YAML::EventHandler;
using YAML::Mark;
using YAML::anchor_t;

class ThemeParser : public EventHandler {

  enum states { none, themes, command_name, commands_command, activations, generic };
  states _state;

  Theme _current_theme;

  string _current_command_name;
  
 public:
  map<string, Theme> _themes;

  ThemeParser();
  ~ThemeParser() override;

  void OnDocumentStart(const Mark&) override;
  
  void OnDocumentEnd() override;
  
  void OnNull(const Mark&, anchor_t) override;
  void OnAlias(const Mark&, anchor_t) override;
  void OnScalar(const Mark&, const std::string&,
		anchor_t, const std::string& value) override;

  void OnSequenceStart(const Mark&, const std::string&,
		       anchor_t, EmitterStyle::value) override;
  
  void OnSequenceEnd() override;

  void OnMapStart(const Mark&, const std::string&,
		anchor_t, EmitterStyle::value) override;
  void OnMapEnd() override;
};

#endif
