/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** main
*/
#include "Parser.hpp"
#include "Reception.hpp"

int main(int ac, char **av)
{
    try
    {
        Parser args(ac, av);
        Reception recep(args.getnbcooks(), args.getstocktimer(), args.getcookingtime());
        recep.createKitchen();
    } catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
