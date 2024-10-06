#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "functions.hpp"

using namespace std;
string input; // To store user's inputs, or to make getline() pause the program
int choice;   // For when 'input' needs to be converted into int
const string filename = "save-data.txt";

int main() // Main loop of the program
{
    bool running = true;
    vector<string> data_vector;  // Vector that contains all lines of text that go in/out of text file
    map<string, int> values_map; // Map that contains the key-value pairs representing game data

    initializeData(values_map, data_vector); // Loads default values into map and vector

    cout << "Welcome to the save file editor." << endl;
    cout << endl;
    while (running)
    {
        cout << "Pick an option:" << endl; // Displays menu options
        cout << endl;
        cout << "1 - Add XP" << endl;
        cout << "2 - Move to Room" << endl;
        cout << "3 - Take Damage" << endl;
        cout << "4 - Kill Enemy" << endl;
        cout << endl;
        cout << "5 - Save" << endl;
        cout << "6 - Load" << endl;
        cout << "7 - Quit" << endl;
        cout << endl;
        cout << ">> ";
        getline(cin, input);
        clearConsole(); // Clears console after each selection for console clarity

        try
        {
            choice = stoi(input);

            switch (choice) // Calls different functions for each option, depending on user's choice
            {
            case 1:
                addXp(values_map); // Adds XP
                break;
            case 2:
                moveRoom(values_map); // Moves player to different room
                break;
            case 3:
                takeDamage(values_map); // Loses health
                break;
            case 4:
                killEnemy(values_map); // Adds to kill count
                break;
            case 5:
                saveFile(values_map, data_vector); // Saves key-value pairs to text file
                break;
            case 6:
                loadFile(values_map, data_vector); // Loads from text file
                break;
            case 7:
                cout << "- Program quitted -" << endl; // Exit message
                exit(0);
                break;
            default:
                cout << "Invalid Option. Please try again" << endl;
                break;
            }
        }
        catch (const exception &e)
        {
            cout << "Invalid Option. Please try again" << endl;
        }
        cout << endl;
        cout << ">> ";
        getline(cin, input);
        clearConsole();
    }
    return 0;
}

void initializeData(map<string, int> &values_map, vector<string> &data) // Loads default values into map, in case user doesn't load file
{
    data = // Default values
        {"xp_level: 0",
         "current_room: 1",
         "current_health: 10",
         "kill_count: 0"};

    for (size_t i = 0; i < data.size(); i++)
    {
        stringstream data_stream(data[i]);
        string key;
        int value;

        if (getline(data_stream, key, ':') && data_stream >> value) // If the line contains a key-value pair, it is added to map
        {
            values_map[key] = value;
        }
    }
}

void addXp(map<string, int> &values_map) // Adds 1 to the xp_level value
{
    values_map["xp_level"] += 1;
    cout << "XP Level Increased!" << endl;
    cout << "Level " << values_map["xp_level"] << endl; // Shows curent level value
}

void displayRoom(map<string, int> &values_map) // Displays the name of the current room
{
    try
    {
        switch (values_map["current_room"]) // Retireves room value and prints corresponding room name
        {
        case 1:
            cout << "Main Entrance";
            break;
        case 2:
            cout << "Hallway";
            break;
        case 3:
            cout << "Storage";
            break;
        case 4:
            cout << "Dungeon";
            break;
        case 5:
            cout << "Armory";
            break;
        case 6:
            cout << "Kitchen";
            break;
        case 7:
            cout << "Bedroom";
            break;
        default:
            cout << "Invalid Option. Please try again" << endl;
            break;
        }
    }
    catch (const exception &e)
    {
        cout << "Invalid Option. Please try again" << endl;
    }
}

void moveRoom(map<string, int> &values_map) // Moves player to a different room
{

    cout << "Current Room: ";
    displayRoom(values_map); // Displays current room
    cout << endl;
    cout << "Select Room:" << endl;
    cout << endl;
    cout << "1 - Main Entrance" << endl;
    cout << "2 - Hallway" << endl;
    cout << "3 - Storage" << endl;
    cout << "4 - Dungeon" << endl;
    cout << "5 - Armory" << endl;
    cout << "6 - Kitchen" << endl;
    cout << "7 - Bedroom" << endl;
    cout << endl;
    cout << ">> ";
    getline(cin, input);
    clearConsole();
    choice = stoi(input);                // Converts input to integer
    values_map["current_room"] = choice; // The same number the user presses to move to a room is also stored into the save file
    cout << "Moved to ";
    displayRoom(values_map); // Displays new current room
    cout << endl;
}

void takeDamage(map<string, int> &values_map) // Subtracts 1 from health value
{
    if (values_map["current_health"] > 0) // Checks if health is not 0
    {
        cout << "You took damage!" << endl;
        cout << endl;
        cout << values_map["current_health"] << " HP --> ";
        values_map["current_health"] -= 1;
        cout << values_map["current_health"] << " HP" << endl;
    }
    else // If health reaches 0, it does not subtract health more
    {
        cout << values_map["current_health"] << " HP - You are dead" << endl;
    }
}

void killEnemy(map<string, int> &values_map) // Adds 1 to kill count value
{
    values_map["kill_count"] += 1;
    cout << "Enemy Killed!" << endl;
    cout << "Kill Count: " << values_map["kill_count"] << endl; // Displayes current kill count
}

void saveFile(map<string, int> &values_map, vector<string> &data_vector) // Saves current key-value data to file
{
    ofstream saveFileOut(filename); // Opens file to modify

    for (const auto &data_line : data_vector) // Iterates through each line in vector
    {
        stringstream data_stream(data_line);
        string key;
        int value;

        if (getline(data_stream, key, ':') && data_stream >> value) // Searches for value pairs in the vector
        {
            if (values_map.find(key) != values_map.end())
            {
                saveFileOut << key << ": " << values_map[key] << endl; // Replaces value in text file with the corresponding values in map
            }
            else
            {
                saveFileOut << data_line << endl; // If line is not a key-value pair, writes back into text file unchanged
            }
        }
        else
        {
            saveFileOut << data_line << endl;
        }
    }
    saveFileOut.close(); // Closes file

    cout << "Data Saved." << endl;
}

void loadFile(map<string, int> &values_map, vector<string> &data_vector) // Loads data from file
{
    ifstream saveFileIn(filename); // Opens file to read
    string data_line;

    data_vector.clear(); // Removes the default values since it is about to load them from the save file

    while (getline(saveFileIn, data_line)) // Iterates of all lines of text file
    {
        stringstream data_stream(data_line);
        string key;
        int value;

        if (getline(data_stream, key, ':') && data_stream >> value) // If it finds a line of text with a name, colon, and number, it is also added to map
        {
            values_map[key] = value;
        }
        data_vector.push_back(data_line); // Adds line of text to the vector
    }
    saveFileIn.close();

    cout << "Save File Loaded." << endl;
}

void clearConsole() // Clears the console when it is needed.
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[3J";
    cout.flush();
}