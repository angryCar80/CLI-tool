#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#include <cstdlib>
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
        std::cout << GREEN << "Task Done" << RESET << std::endl;
      }
    } else if (command == "undone") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].done = false;
      } else if (command == "delete") {
        if (!(ss >> index)) {
          std::cout << RED << "Error: Please provide a valid task number.\n" << RESET;
        }
        int index;
        ss >> index;
        if (index > 0 && index <= (int)tasks.size()) {
          tasks.erase(tasks.begin() + index - 1);
          std::cout << "Task Deleted.\n";
        }
      }
    } else if (command == "clear") {
      system("clear");
    } else if (command == "help") {
      std::cout << "this is the help manual \n" << std::endl;
      std::cout << "to add a task you need to type \n > add taskname"
                << std::endl;
      std::cout << "to mark the task done you need to type \n > done taskname"
                << std::endl;
      std::cout << "to mark down the task undone you need to type \n > undone "
                   "taskname"
                << std::endl;
      std::cout << "to list the todos you need to type \n > list " << std::endl;
      std::cout << "\n";
    } else {
      std::cout << RED
                << "Invalid Command. Type help to see the available commands."
                << RESET << std::endl;
    }
  }

  return 0;
}
