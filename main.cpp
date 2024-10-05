#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "functions.hpp"

using namespace std;
string input;
int choice;
const string filename = "save-data.txt";

int main()
{
    bool running = true;
    vector<string> data_vector;
    map<string, int> values_map;

    initializeData(values_map, data_vector);
    cout << "(Testing)\n\n";

    cout << "Welcome to the save file editor." << endl; // Welcome message
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
        clearConsole();

        try
        {
            choice = stoi(input);

            switch (choice)
            {
            case 1:
                addXp(values_map);
                break;
            case 2:
                moveRoom(values_map);
                break;
            case 3:
                takeDamage(values_map);
                break;
            case 4:
                killEnemy(values_map);
                break;
            case 5:
                saveFile(values_map, data_vector);
                break;
            case 6:
                loadFile(values_map, data_vector);
                break;
            case 7:
                cout << "Quit" << endl;
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

void initializeData(map<string, int> &values_map, vector<string> &data)
{
    data =
        {"xp_level: 0",
         "current_room: 1",
         "current_health: 10",
         "kill_count: 0"};

    for (size_t i = 0; i < data.size(); i++)
    {
        stringstream data_stream(data[i]);
        string key;
        int value;

        if (getline(data_stream, key, ':') && data_stream >> value)
        {
            values_map[key] = value;
        }
    }

    for (const auto &pair : values_map)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void addXp(map<string, int> &values_map)
{
    values_map["xp_level"] += 1;
    cout << "XP Level Increased!" << endl;
    cout << "Level " << values_map["xp_level"] << endl;
}

void displayRoom(map<string, int> &values_map)
{
    try
    {
        switch (values_map["current_room"])
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

void moveRoom(map<string, int> &values_map)
{

    cout << "Current Room: ";
    displayRoom(values_map);
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
    choice = stoi(input);
    values_map["current_room"] = choice;
    cout << "Moved to ";
    displayRoom(values_map);
    cout << endl;
}

void takeDamage(map<string, int> &values_map)
{
    if (values_map["current_health"] > 0)
    {
        cout << "You took damage!" << endl;
        cout << endl;
        cout << values_map["current_health"] << " HP --> ";
        values_map["current_health"] -= 1;
        cout << values_map["current_health"] << " HP" << endl;
    }
    else
    {
        cout << "0 HP - You are dead" << endl;
    }
}

void killEnemy(map<string, int> &values_map)
{
    values_map["kill_count"] += 1;
    cout << "Enemy Killed!" << endl;
    cout << "Kill Count: " << values_map["kill_count"] << endl;
}

void saveFile(map<string, int> &values_map, vector<string> &data_vector)
{
    ofstream saveFileOut(filename);

    for (const auto &data_line : data_vector)
    {
        stringstream data_stream(data_line);
        string key;
        int value;

        if (getline(data_stream, key, ':') && data_stream >> value)
        {
            if (values_map.find(key) != values_map.end())
            {
                saveFileOut << key << ": " << values_map[key] << endl;
            }
            else
            {
                saveFileOut << data_line << endl;
            }
        }
        else
        {
            saveFileOut << data_line << endl;
        }
    }
    saveFileOut.close();

    cout << "Data Saved." << endl;
}

void loadFile(map<string, int> &values_map, vector<string> &data_vector)
{
    ifstream saveFileIn(filename);
    string data_line;

    data_vector.clear();

    while (getline(saveFileIn, data_line))
    {
        stringstream data_stream(data_line);
        string key;
        int value;

        if (getline(data_stream, key, ':') && data_stream >> value)
        {
            values_map[key] = value;
        }
        data_vector.push_back(data_line);
    }
    saveFileIn.close();

    cout << "Save File Loaded." << endl;
}

void clearConsole()
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[3J";
    cout.flush();
}