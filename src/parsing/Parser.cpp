/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(int ac, char **av)
{
    if (ac != 4)
    {
        throw ParserException{"Exactly 3 arguments are required."};
    }

    std::stringstream arg1(av[1]);
    arg1 >> _cookingtime;
    if (arg1.fail() || _cookingtime <= 0)
    {
        throw ParserException{"First argument must be a float > 0 for cooking time."};
    }

    std::stringstream arg2(av[2]);
    arg2 >> _nbcooks;
    if (arg2.fail() || _nbcooks <= 0)
    {
        throw ParserException{"Second argument must be an int > 0 for number of cooks."};
    }

    std::stringstream arg3(av[3]);
    arg3 >> _stocktimer;
    if (arg3.fail() || _stocktimer <= 0)
    {
        throw ParserException{"Third argument must be an int > 0 for restock timer."};
    }
}

Parser::~Parser()
{
}

float Parser::getcookingtime()
{
    return _cookingtime;
}

int Parser::getnbcooks()
{
    return _nbcooks;
}

int Parser::getstocktimer()
{
    return _stocktimer;
}
