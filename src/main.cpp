/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** main
*/

#include "Parser.hpp"
#include "Reception.hpp"
#include "LoopParser.hpp"

int main(int ac, char **av)
{
    try
    {
        Parser args(ac, av);
        Reception recep(args.getnbcooks(), args.getstocktimer(), args.getcookingtime());
        recep.start();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}