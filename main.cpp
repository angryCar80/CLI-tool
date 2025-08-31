// adding colors for to make the app look cool and better maybe
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

using jason = nlohmann::json;

struct Task {
  std::string name;
  bool toggle = false;
};

void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }

int main() {
  std::string input;
  std::vector<Task> tasks;
  bool autosave = false;

  while (true) {
    std::cout << GREEN << "┌────────────────────────────\n";
    std::cout << "└─> " << RESET;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string command;
    ss >> command;

    // EXIT
    if (command == "exit") {
      std::cout << "Exiting ,";
      if (autosave) {
        jason j;
        for (const auto &task : tasks) {
          j.push_back({{"name", task.name}, {"toggled", task.toggle}});
        }
        if (j.empty()) {
          std::cout << RED << "Save file is empty" << RESET << "\n";
        } else {
          std::ofstream file("data.json");
          file << j.dump(4);
          file.close();
          std::cout << GREEN << "Saving ..." << RESET << "\n";
        }
      } else {
        std::cout << RED << "Without saving\n" << RESET;
      }
      break;
    }
    // ADD TASK
    else if (command == "add" || command == "a") {
      std::string name;
      std::getline(ss, name);
      if (!name.empty() && name[0] == ' ') {
        name = name.substr(1);
      }
      if (name.empty()) {
        std::cout << RED << "You can't add an empty task" << RESET << '\n';
        continue;
      }
      tasks.push_back({name, false});
      std::cout << GREEN << "Task added: " << name << RESET << '\n';
    }
    // LIST TASKS
    else if (command == "list" || command == "ls") {
      for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << (i + 1) << ". " << tasks[i].name;
        std::cout << (tasks[i].toggle ? " [X]" : " [ ]") << "\n";
      }
      std::cout << "\n";
    }
    // TOGGLE
    else if (command == "toggle" || command == "t") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].toggle = true;
        std::cout << GREEN << "Task Toggled" << RESET << "\n";
      }
    }
    // UNTOGGLE
    else if (command == "untoggle" || command == "unt") {
      int index;
      ss >> index;
      if (index > 0 && index <= (int)tasks.size()) {
        tasks[index - 1].toggle = false;
      }
    }
    // CLEAR SCREEN
    else if (command == "clear" || command == "cls") {
      ClearScreen();
    }
    // AUTOSAVE
    else if (command == "autosave") {
      std::string onoff;
      ss >> onoff;
      if (onoff == "on") {
        autosave = true;
        std::cout << GREEN << "Autosave is on" << RESET << '\n';
      } else if (onoff == "off") {
        autosave = false;
        std::cout << RED << "Autosave is off" << RESET << '\n';
      }
    }
    // HELP
    else if (command == "help" || command == "h") {
      std::cout << "add {taskname}   to add tasks (a for short)\n";
      std::cout << "toggle {num}     to toggle a task (t for short)\n";
      std::cout << "untoggle {num}   to untoggle a task (unt for short)\n";
      std::cout << "delete {num}     to delete a task (d for short)\n";
      std::cout << "save tasks       to save your tasks (st for short)\n";
      std::cout << "load             to load saved tasks (l for short)\n";
    }
    // SAVE
    else if (command == "save" || command == "s" || command == "save tasks" ||
             command == "st") {
      std::string settings;
      ss >> settings;
      if (settings == "settings") {
        std::ofstream file("settings.json");
        std::cout << "Saving settings\n";
      }

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
      std::cout << GREEN << "Tasks Saved" << RESET << "\n";
    }
    // LOAD
    else if (command == "load" || command == "l") {
      std::ifstream file("data.json");
      if (!file.is_open()) {
        std::cout << RED << "No save file found" << RESET << '\n';
        continue;
      } else if (command == "autoload") {
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
    // DELETE
    else if (command == "delete" || command == "d") {
      int index;
      ss >> index;
      if (index > 0 && index <= int(tasks.size())) {
        tasks.erase(tasks.begin() + (index - 1));
        std::cout << RED << "Task deleted" << RESET << "\n";
      } else {
        std::cout << RED << "Invalid Task number" << RESET << "\n";
      }
    }
    // INVALID COMMAND
    else {
      std::cout << "Invalid Command. Type " << GREEN << "help" << RESET
                << " to see available commands.\n";
    }
  }

  return 0;
}
