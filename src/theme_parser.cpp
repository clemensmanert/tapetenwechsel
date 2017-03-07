#include "theme_parser.h"

ThemeParser::ThemeParser() {}

ThemeParser::~ThemeParser() {}

void ThemeParser::OnDocumentStart(const Mark&) {
  _state = themes;
}
  
void ThemeParser::OnDocumentEnd() {
  _themes.insert(pair<string, Theme>(_current_theme._name, _current_theme));
}

void ThemeParser::OnNull(const Mark&, anchor_t) { }

void ThemeParser::OnAlias(const Mark&, anchor_t) { }

void ThemeParser::OnScalar(const Mark&, const std::string&,
			   anchor_t, const std::string& value) {
  switch(_state) {
  case none:
    _current_theme = Theme(value);
    _state = themes;
    break;

  case activations:
    _current_theme.add_activaton(value);
    break;
    
  case themes:
    if(value == "commands") {
      _state = command_name;
    } else if (value == "generic") {
      _state = generic;
    } else if (value == "activations") {
      _state = activations;
    } else {
      _themes.insert(pair<string,Theme>(_current_theme._name, _current_theme));

      _current_theme = Theme(value);
      _state = themes;
    }
    break;
    
  case generic:
    _current_theme.set_generic(value);
    _state = themes;
    break;

  case command_name:
    _current_command_name = value;
    _state = commands_command;
    break;

  case commands_command:
    _current_theme.add_command(_current_command_name,
		       value);
    _state = command_name;
    break;
      
  default:
    cout << " invalid state: " << _state << endl;
    //throw an exception here	
    break;
  }
}

void ThemeParser::OnSequenceStart(const Mark&, const std::string&,
				  anchor_t, EmitterStyle::value) { }
  
void ThemeParser::OnSequenceEnd() {
  _state = themes;
}

void ThemeParser::OnMapStart(const Mark&, const std::string&,
			     anchor_t, EmitterStyle::value) { }

void ThemeParser::OnMapEnd() {
  _state = themes;
}

