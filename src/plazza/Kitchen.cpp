/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen() :
    _pid(fork())
{
    if (_pid == -1)
    {
        throw KitchenException {"fork error."};
    }
}

Kitchen::~Kitchen()
{
    exit(_pid);
}
