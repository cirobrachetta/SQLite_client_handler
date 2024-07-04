/**
* Copyright (c) 2020 Gabriel Nicolás González Ferreira. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <DatabaseHandler.h>
#include <SqliteDatabaseHandler.h>
#include <IniReader.h>
#include "./User_Game_Manager.h"

using namespace std;

void showMenu();

void showMenu() {
    cout << "1. Add User" << endl;
    cout << "2. Delete User" << endl;
    cout << "3. Modify User" << endl;
    cout << "4. List Users" << endl;
    cout << "5. Add Game" << endl;
    cout << "6. Delete Game" << endl;
    cout << "7. Modify Game" << endl;
    cout << "8. List Games" << endl;
    cout << "9. Associate Game to User" << endl;
    cout << "10. Search by User" << endl;
    cout << "11. Search by Game" << endl;
    cout << "12. list users whit games" << endl;
    cout << "0. Exit" << endl;
}

int main()
{
    //Database Handler:
    auto dbh = make_unique<SqliteDatabaseHandler>();
    dbh->setConfFile("configuration.ini");
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    dbh->execute();

    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Games (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT)");
    dbh->execute();

    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS User_Games (user_id INTEGER, game_id INTEGER, FOREIGN KEY(user_id) REFERENCES Users(id), FOREIGN KEY(game_id) REFERENCES Games(id))");
    dbh->execute();
    
    //ROW DATA:
    dbh->prepareQuery("SELECT * FROM Users WHERE id=?");
    dbh->addParameter(1, "1");
    Row row = dbh->fetch();

    cout << "ROW DATA 1" << endl;
    cout << "id: " << row["id"] << endl;
    cout << "name: " << row["name"] << endl << endl;

    dbh->prepareQuery("SELECT * FROM Users WHERE id=?");
    dbh->addParameter(1, "23");
    row = dbh->fetch();

    cout << "ROW DATA 2" << endl;
    cout << "id: " << row["id"] << endl;
    cout << "name: " << row["name"] << endl << endl;

    //TABLE DATA:
    dbh->prepareQuery("SELECT * FROM Users");
    Table table = dbh->fetchAll();

    cout << "Table DATA row 1:" << endl;
    cout << "id: " << table[0]["id"] << endl;
    cout << "name: " << table[0]["name"] << endl << endl;

    cout << "Table DATA row 2:" << endl;
    cout << "id: " << table[1]["id"] << endl;
    cout << "name: " << table[1]["name"] << endl;

    UserGameManager manager(dbh);

    int choice;

    bool iteration = true;

    while(iteration){
        showMenu();
        cout << "Enter Your Choice: " << endl;
        cin >> choice;

        if(choice == 0){
            break;
        }

        int id;
        string name, title;

        switch (choice) {
            case 1:
                cout << "Enter user name: ";
                cin >> ws; // to ignore leading whitespace
                getline(cin, name);
                manager.addUser(name);
                break;
            case 2:
                cout << "Enter user ID to delete: ";
                cin >> id;
                manager.deleteUser(id);
                break;
            case 3:
                cout << "Enter user ID to modify: ";
                cin >> id;
                cout << "Enter new user name: ";
                cin >> ws; 
                getline(cin, name);
                manager.modifyUser(id, name);
                break;
            case 4:
                manager.listUsers();
                break;
            case 5:
                cout << "Enter game title: ";
                cin >> ws; 
                getline(cin, title);
                manager.addGame(title);
                break;
            case 6:
                cout << "Enter game ID to delete: ";
                cin >> id;
                manager.deleteGame(id);
                break;
            case 7:
                cout << "Enter game ID to modify: ";
                cin >> id;
                cout << "Enter new game title: ";
                cin >> ws; 
                getline(cin, title);
                manager.modifyGame(id, title);
                break;
            case 8:
                manager.listGames();
                break;
            case 9:
                int userId, gameId;
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter game ID: ";
                cin >> gameId;
                manager.associateGameUser(userId, gameId);
                break;
            case 10:
                cout << "Enter user ID to search: ";
                cin >> id;
                manager.searchByUser(id);
                break;
            case 11:
                cout << "Enter game ID to search: ";
                cin >> id;
                manager.searchByGame(id);
                break;
            case 12:
                manager.listUsers_Games();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}