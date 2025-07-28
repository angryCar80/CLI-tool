#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

struct Task {
  std::string name;
  bool done = false;
};

int main() {
  std::string input;
  std::vector<Task> tasks;

  while (true) {
    std::cout << "> ";
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string command;
    ss >> command;

    if (command == "exit") {
      std::cout << "Exiting..." << std::endl;
      break;
    } else if (command == "add") {
      std::string name;
      std::getline(ss, name);
      // Remove leading space from name if present
      if (!name.empty() && name[0] == ' ') name = name.substr(1);
      tasks.push_back(Task{name});
    } else if (command == "list") {
      for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << (i + 1) << ". " << tasks[i].name;
        if (tasks[i].done) {
          std::cout << " [x]";
        } else {
          std::cout << " [ ]";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    } else if (command == "done") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].done = true;
      }
    } else if (command == "undone") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].done = false;
      }
    } else if (command == "clear") {
      system("clear");
    } else {
      std::cout << "Invalid Command. Type help to see the available commands." << std::endl;
    }
  }

  return 0;
}
