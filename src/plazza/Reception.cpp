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