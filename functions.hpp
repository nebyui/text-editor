// To keep the program simpler to follow, all the functions are initialized here so they don't have to be declared before the main() function

#ifndef MAIN_FUNCTIONS_HPP
#define MAIN_FUNCTIONS_HPP

#include <fstream>
#include <vector>
#include <map>
#include <string>

void initializeData(std::map<std::string, int> &values, std::vector<std::string> &data);

void addXp(std::map<std::string, int> &values);

void displayRoom(std::map<std::string, int> &values);

void moveRoom(std::map<std::string, int> &values);

void takeDamage(std::map<std::string, int> &values);

void killEnemy(std::map<std::string, int> &values);

void saveFile(std::map<std::string, int> &values, std::vector<std::string> &data);

void loadFile(std::map<std::string, int> &values, std::vector<std::string> &data);

void clearConsole();

#endif