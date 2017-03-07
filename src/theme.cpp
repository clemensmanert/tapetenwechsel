#include "theme.h"

Theme::Theme() {}
  
Theme::Theme(string name) : _name(name) {}
  
Theme::Theme(string name, string generic) :
  _name(name), _generic(generic){ }

void Theme::activate() {
  for(auto & activation : _activations) {
    popen(activation.c_str(), "r");
  }
}
 
void Theme::add_command(string  name, string command) {
  _commands.insert(pair<string, string>(name, command));
}

void Theme::add_activaton(string command) {
  _activations.push_back(command);
}

void Theme::execute(string command) {
  string command_name, args;

  auto found = command.find(" ");
  
  if (found != string::npos) {
    command_name = command.substr(0,found);
    args = command.substr(found+1, string::npos);
  } else {
    command_name = command;
    args = "";
  }

  if(_commands.count(command_name) > 0) {
    command = _commands[command_name];
  } else {
    command = _generic + " " + command_name;
  }


  char buffer[128];

  std::shared_ptr<FILE> pipe(popen((command + " " + args).c_str(), "r"), pclose);
  if (!pipe) {
    std::cerr << "Can not open command " << command << " " << args;
  }
  while (!feof(pipe.get())) {
    if (fgets(buffer, 128, pipe.get()) != NULL)
      std::cout <<  buffer;
  }
}

void Theme::set_generic(string generic) {
  _generic = generic;
}

