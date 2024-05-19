/*
** EPITECH PROJECT, 2024
** Plazza
** File description: While loop in commandLine
** programLoop
*/

#include "LoopClass.hpp"
#include "LoopParser.hpp"

/** @brief Main Loop of the programm get the orders, parse them and redistribute them*/
void LoopClass::Loop()
{
    while (true) {
        try {
            loopParser.ArgCommandLine();
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            break;
        } catch (const std::exception& e) {
            std::cout << "An error occurred: " << e.what() << std::endl;
        }
    }
}

