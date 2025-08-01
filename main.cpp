// adding color for to make the app look cool
#include <ostream>
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// for saving data we will use .jas*n
#include <fstream>
#include <nlohmann/json.hpp>
using jason = nlohmann::json;

struct Task {
  std::string name;
  bool done = false;
};

int main() {
  std::string input;
  std::vector<Task> tasks;

  while (true) {
    std::cout << "> ";
    std::getline(std::cin, input);  // reading user input

    std::stringstream ss(input);
    std::string command;
    ss >> command;

    // the exit command to exit the app
    if (command == "exit") {
      std::cout << "Exiting..." << std::endl;
      break;
    }
    // the add command to add tasks
    else if (command == "add") {
      std::string name;
      std::getline(ss, name);
      // Remove leading space from name if present
      if (!name.empty() && name[0] == ' ') name = name.substr(1);
      tasks.push_back(Task{name});
    }
    // the list command work like ls command in linux it list the task and if
    // they are done or not
    else if (command == "list") {
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
    }
    // to done the task by the index
    else if (command == "done") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].done = true;
        std::cout << GREEN << "Task Done" << RESET << std::endl;
      }
    }
    // to undone the task by the index
    else if (command == "undone") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].done = false;
      }
    }
    // to clear the screen (WORKS ONLY IN LINUX)
    else if (command == "clear") {
      system("clear");
    }
    // the help command the can help you
    else if (command == "help") {
      std::cout << "add {taskname}  to add tasks" << std::endl;
      std::cout << "done {tasknumber}  to done a task" << std::endl;
      std::cout << "undone {tasknumber}  to undone a task" << std::endl;
      std::cout << "delete {tasknumber}   to delete a task (coming soon)"
                << std::endl;
      std::cout << "save                  to save whatever you did"
                << std::endl;
    }
    // to save the tasks in a .jas*n file
    // this command need some more updates to make it work like it should
    else if (command == "save") {
      jason j;

      for (const auto& task : tasks) {
        j.push_back({{"name", task.name}, {"done", task.done}});
      }
      std::ofstream file("tasks-data.jason");
      file << j.dump();
      file.close();
      std::cout << GREEN << "Task Saved" << RESET << std::endl;
    }
    // checking if the command is not valid by an else statment
    else {
      std::cout << RED
                << "Invalid Command. Type help to see the available commands."
                << RESET << std::endl;
    }
  }

  return 0;
}
