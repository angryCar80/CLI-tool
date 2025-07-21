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
  int index = 0;

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
        index++;
        std::string name;
      std::getline(ss, name);
      tasks.push_back(Task{name});
    } else if (command == "list") {
      for (const auto& task : tasks) {
        std::cout << index << ". " << task.name;
        if (task.done) {
          std::cout << "[x]";
        } else {
          std::cout << "[ ]";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    } else if (command == "done") {
      ss >> index;
      if (index > 0 && index < tasks.size()) {
        tasks[index - 1].done = true;
      }
    } else {
      std::cout << "Invalid Command type help to see the available commands"
                << std::endl;
    }

    for (const auto& task : tasks) {
      int index = 1;
    }
  }

  return 0;
}
