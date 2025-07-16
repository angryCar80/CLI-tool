#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
      tasks.push_back(Task{name});
    } else if (command == "list") {
      int index = 1;
      for (const auto& task : tasks) {
        if (task.done) {
          std::cout << "[x]";
        } else {
          std::cout << "[ ]";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    } else {
      std::cout << "Invalid Command" << std::endl;
    }

    for (const auto& task : tasks) {
      int index = 1;
      std::cout << index++ << ". " << task.name << ": ";  // <- error is here
      if (task.done) {
        std::cout << "[x]";
      } else {
        std::cout << "[ ]";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;

}
