// adding colors for to make the app look cool and better maybe
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

// for making the app work and they are from the std lib
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// for saving data we will use .jas*n its not from the std lib
#include <fstream>
#include <nlohmann/json.hpp>
using jason = nlohmann::json;

struct Task {
  std::string name;
  bool toggle = false;
};

void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }

int main() {
  std::string input;
  std::vector<Task> tasks; // creating a tasks vector
  bool autosave = false;
  // the main loop
  while (true) {
    // std::fstream::open("data.jason")
    std::cout << GREEN << "┌────────────────────────────\n";
    std::cout << "└─> " << RESET;
    std::getline(std::cin, input); // reading user input

    std::stringstream ss(input);
    std::string command;
    ss >> command;

    if (command == "exit") {
      std::cout << "Exiting..." << "\n";
      if (autosave == true) {
        jason j;
        for (const auto &task : tasks) {
          j.push_back({{"name", task.name}, {"toggled", task.toggle}});
        }
        if (j.empty()) {
          std::cout << RED << "Save file is empty" << RESET << "\n";
          continue;
        }

        std::ofstream file("data.json");
        file << j.dump(4);
        file.close();
        std::cout << GREEN << "Saving..." << RESET << "\n";
      } else if (autosave == false){
        std::cout << "NONO\n";
      }
      break;
    }
    // the add command to add tasks
    else if (command == "add" || command == "a") {
      std::string name;
      std::getline(ss, name);
      // Remove leading space from name if present
      if (!name.empty() && name[0] == ' ') {
        name = name.substr(1);
      }
      if (name.empty()) {
        std::cout << RED << "You cant add an empty task" << RESET << '\n';
      }
      tasks.push_back({name, false});
      std::cout << GREEN << "Task added: " << name << RESET << '\n';
    }
    // the list command work like ls command in linux it list the task and if
    // they are toggled or not
    else if (command == "list" || command == "ls") {
      for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << (i + 1) << ". " << tasks[i].name;
        if (tasks[i].toggle) {
          std::cout << " [X]";
        } else {
          std::cout << " [ ]";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }
    // to toggle the task by the index
    else if (command == "toggle" || command == "t") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].toggle = true;
        std::cout << GREEN << "Task Toggled" << RESET << "\n";
      }
    }
    // to untoggle the task by the index
    else if (command == "untoggle" || command == "unt") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].toggle = false;
      }
    }
    // to clear the screen (WORKS ONLY IN LINUX)
    else if (command == "clear" || command == "cls") {
      ClearScreen();
    } else if (command == "autosave") {
      std::string onoff;
      ss >> onoff;
      if (onoff == "on") {
        // make the autosaving on
        autosave = true;
        std::cout << GREEN << "Autosave is on" << RESET << '\n';
      } else if (onoff == "off") {
        autosave = false;
        std::cout << RED << "Autosave is off" << RESET << '\n';
      }
    }
    // the help command the can help you
    else if (command == "help" || command == "h") {
      std::cout << "add {taskname}  to add tasks (a for short hand)" << "\n";
      std::cout << "toggle {tasknumber}  to toggle a task (t for short hand)"
                << "\n";
      std::cout
          << "untoggle {tasknumber}  to untoggle a task (unt for short hand)"
          << "\n";
      std::cout << "delete {tasknumber}   to delete a task (d for short hand)"
                << "\n";
      std::cout
          << "save                  to save whatever you did (s for short hand)"
          << "\n";
      std::cout << "load            to load the file that have the data (l for "
                   "short hand)"
                << '\n';
    }
    // to save the tasks in a .jas*n file
    // this command need some more updates to make it work
    else if (command == "save" || command == "s") {
      jason j;
      for (const auto &task : tasks) {
        j.push_back({{"name", task.name}, {"toggled", task.toggle}});
      }
      if (j.empty()) {
        std::cout << RED << "Save file is empty" << RESET << "\n";
        continue;
      }

      std::ofstream file("data.json");
      file << j.dump(4);
      file.close();
      std::cout << GREEN << "Task Saved" << RESET << "\n";
    } else if (command == "load" || command == "l") {
      std::ifstream file("data.json");
      if (!file.is_open()) {
        std::cout << RED << "No save file found" << RESET << '\n';
        continue;
      }
      jason j;
      file >> j;
      file.close();
      tasks.clear();
      for (const auto &item : j) {
        Task t;
        t.name = item.at("name").get<std::string>();
        t.toggle = item.at("toggled").get<bool>();
        tasks.push_back(t);
      }
      std::cout << GREEN << "Loaded" << RESET << '\n';
    }
    // the delete command
    else if (command == "delete" || command == "d") {
      int index;
      ss >> index;
      if (index > 0 && index <= int(tasks.size())) {
        tasks.erase(tasks.begin() + (index - 1));
        std::cout << RED << "Task deleted" << RESET << "\n";
      } else {
        std::cout << RED << "Invalide Task number" << RESET << "\n";
      }
    }
    // checking if the command is not valid by the else statment
    else {
      std::cout << "Invalid Command. Type" << GREEN << " help " << RESET
                << "to see the available commands." << "\n";
    }
  }

  return 0;
}
