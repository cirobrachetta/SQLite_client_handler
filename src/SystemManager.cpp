#include "SystemManager.h"
#include "sqlite3.h"
#include "Database.h"
#include <iostream>

SystemManager::SystemManager(const std::string& dbName) 
        : db(dbName), userMapper(db), gameMapper(db), userGameAssociation(db) {
        DatabaseInitializer::initialize(db);
    }

void SystemManager::showMenu() {
        std::cout << "----- MENU -----" << std::endl;
        std::cout << "1. Add User" << std::endl;
        std::cout << "2. Remove User" << std::endl;
        std::cout << "3. Update User" << std::endl;
        std::cout << "4. List Users" << std::endl;
        std::cout << "5. Add Game" << std::endl;
        std::cout << "6. Remove Game" << std::endl;
        std::cout << "7. Update Game" << std::endl;
        std::cout << "8. List Games" << std::endl;
        std::cout << "9. Associate User with Game" << std::endl;
        std::cout << "10. List All Associations" << std::endl;
        std::cout << "11. Find Associations by User" << std::endl;
        std::cout << "12. Find Associations by Game" << std::endl;
        std::cout << "13. Show Inventory" << std::endl;
        std::cout << "14. Buy Game (data base act as a shop)" << std::endl;
        std::cout << "15. Sell Game (data base act as a shop)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter an option: ";
    }

void SystemManager::addUser() {
    std::string name, email;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);

    User user(0, name, email); // Crear un nuevo usuario con ID 0, que será asignado automáticamente en la base de datos
    try {
        if (userMapper.insert(user)) {
            std::cout << "User added successfully." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: Email already exists in the database." << std::endl;
    }
}

void SystemManager::removeUser() {
        int id;
        std::cout << "Enter user ID to remove: ";
        std::cin >> id;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        if (userMapper.remove(id)) {
            std::cout << "User removed successfully." << std::endl;
        }
    }

void SystemManager::updateUser() {
        int id;
        std::string name, email;
        std::cout << "Enter user ID to update: ";
        std::cin >> id;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        std::cout << "Enter new name: ";
        std::getline(std::cin, name);
        std::cout << "Enter new email: ";
        std::getline(std::cin, email);

        User user(id, name, email);
        if (userMapper.update(user)) {
            std::cout << "User updated successfully." << std::endl;
        }
    }

void SystemManager::listUsers() {
        std::vector<User> users = userMapper.findAll();
        for (const auto& user : users) {
            std::cout << "ID: " << user.id << ", Name: " << user.name << ", Email: " << user.email << std::endl;
        }
    }

void SystemManager::addGame() {
        std::string title, genre;
        int available;
        std::cout << "Enter title: ";
        std::getline(std::cin, title);
        std::cout << "Enter genre: ";
        std::getline(std::cin, genre);
        std::cout << "Enter availabilitie: ";
        std::cin >> available;

        Game game(0, title, genre, available); // Crear un nuevo juego con ID 0, que será asignado automáticamente en la base de datos
        if (gameMapper.insert(game)) {
            std::cout << "Game added successfully." << std::endl;
        }
    }

void SystemManager::removeGame() {
        int id;
        std::cout << "Enter game ID to remove: ";
        std::cin >> id;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        if (gameMapper.remove(id)) {
            std::cout << "Game removed successfully." << std::endl;
        }
    }

void SystemManager::updateGame() {
        int id;
        std::string title, genre;
        int available;
        std::cout << "Enter game ID to update: ";
        std::cin >> id;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        std::cout << "Enter new title: ";
        std::getline(std::cin, title);
        std::cout << "Enter new genre: ";
        std::getline(std::cin, genre);
        std::cout << "Enter Availability: ";
        std::cin >> available;

        Game game(id, title, genre, available);
        if (gameMapper.update(game)) {
            std::cout << "Game updated successfully." << std::endl;
        }
    }

void SystemManager::listGames() {
        std::vector<Game> games = gameMapper.findAll();
        for (const auto& game : games) {
            std::cout << "ID: " << game.id << ", Title: " << game.title << ", Genre: " << game.genre << std::endl;
        }
    }

void SystemManager::associateUserGame() {
        int userId, gameId;
        std::cout << "Enter user ID: ";
        std::cin >> userId;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        std::cout << "Enter game ID: ";
        std::cin >> gameId;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        if (userGameAssociation.associate(userId, gameId)) {
            std::cout << "Association created successfully." << std::endl;
        }
    }

 void SystemManager::listAllAssociations() {
        auto associations = userGameAssociation.findAllAssociations(userMapper, gameMapper);
        for (const auto& [user, game] : associations) {
            std::cout << "User: " << user.name << " (Email: " << user.email << "), Game: " << game.title << " (Genre: " << game.genre << ")" << std::endl;
        }
    }

void SystemManager::findAssociationsByUser() {
        std::string name;
        std::cout << "Enter user name to search: ";
        std::getline(std::cin, name);

        auto users = userMapper.findByName(name);
        for (const auto& user : users) {
            std::cout << "User: " << user.name << " (Email: " << user.email << ")" << std::endl;
            auto associations = userGameAssociation.findAllAssociations(userMapper, gameMapper);
            for (const auto& [associatedUser, game] : associations) {
                if (associatedUser.id == user.id) {
                    std::cout << "\tGame: " << game.title << " (Genre: " << game.genre << ")" << std::endl;
                }
            }
        }
    }

void SystemManager::findAssociationsByGame() {
        std::string title;
        std::cout << "Enter game title to search: ";
        std::getline(std::cin, title);

        auto games = gameMapper.findByTitle(title);
        for (const auto& game : games) {
            std::cout << "Game: " << game.title << " (Genre: " << game.genre << ")" << std::endl;
            auto associations = userGameAssociation.findAllAssociations(userMapper, gameMapper);
            for (const auto& [user, associatedGame] : associations) {
                if (associatedGame.id == game.id) {
                    std::cout << "\tUser: " << user.name << " (Email: " << user.email << ")" << std::endl;
                }
            }
        }
    }

void SystemManager::showInventory() {
        auto games = gameMapper.findAll();
        for (const auto& game : games) {
            std::cout << "ID: " << game.id << ", Titulo: " << game.title 
                      << ", Genero: " << game.genre << ", Disponibles: " 
                      << game.available << std::endl;
        }
    }

void SystemManager::buyGame() {
        int gameId;
        std::cout << "Ingrese el ID del juego a comprar: ";
        std::cin >> gameId;
        std::cin.ignore(); // Clear newline from the buffer

        if (gameMapper.updateAvailability(gameId, -1)) {
            std::cout << "Juego comprado exitosamente.\n";
        } else {
            std::cout << "Error al comprar el juego.\n";
        }
    }

void SystemManager::sellGame() {
        int gameId;
        std::cout << "Ingrese el ID del juego a vender: ";
        std::cin >> gameId;
        std::cin.ignore(); // Clear newline from the buffer

        if (gameMapper.updateAvailability(gameId, 1)) {
            std::cout << "Juego vendido exitosamente.\n";
        } else {
            std::cout << "Error al vender el juego.\n";
        }
    }

void SystemManager::run() {
        int option;
        do {
            showMenu();
            std::cin >> option;
            std::cin.ignore(); // Limpiar el buffer después de leer la opción
            switch (option) {
                case 1:
                    addUser();
                    break;
                case 2:
                    removeUser();
                    break;
                case 3:
                    updateUser();
                    break;
                case 4:
                    listUsers();
                    break;
                case 5:
                    addGame();
                    break;
                case 6:
                    removeGame();
                    break;
                case 7:
                    updateGame();
                    break;
                case 8:
                    listGames();
                    break;
                case 9:
                    associateUserGame();
                    break;
                case 10:
                    listAllAssociations();
                    break;
                case 11:
                    findAssociationsByUser();
                    break;
                case 12:
                    findAssociationsByGame();
                    break;
                case 13:
                    showInventory();
                    break;
                case 14:
                    buyGame();
                    break;
                case 15:
                    sellGame();
                    break;
                case 0:
                    std::cout << "Exiting..." << std::endl;
                    break;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }
        } while (option != 0);
    }