/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Reception
*/

#include "Reception.hpp"

Reception::Reception(int numCooksPerKitchen, int ingredientRegenerationTime, float cookingTimeMultiplier) :
    _numCooksPerKitchen(numCooksPerKitchen), _ingredientRegenerationTime(ingredientRegenerationTime),
      _cookingTimeMultiplier(cookingTimeMultiplier)
{
    std::cout << "Reception created." << std::endl;
}

Reception::~Reception()
{
}

void Reception::createKitchen()
{
    pid_t pid = fork();

    if (pid == 0) {
        std::cout << "CREATED KITCHEN\n";
        exit(0);
    } else if (pid > 0) {
    } else {
        std::cerr << "Failed to fork a new kitchen process." << std::endl;
    }
}

void Reception::printHelp()
{
    std::cout << "You can order pizzas here by stating: [type] [size] [number]" << std::endl;
    std::cout << "You have to separate each kind by a ';'" << std::endl;
    std::cout << "If you are done for the day, just say 'exit'" << std::endl;
}

void Reception::start()
{
    std::string command;
    std::cout << "Welcome to Plazza's Pizzas, may we have your order ?" << std::endl;

    while (true)
    {
        std::getline(std::cin, command);
        if (command == "help")
        {
            printHelp();
        }
        if (command == "exit")
        {
            break;
        }
    }
}
