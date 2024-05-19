/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Cook
*/

#include "Cook.hpp"

Cook::Cook(int id) :
    PthreadThread(id), _busy(false)
{
}

Cook::~Cook()
{
}

void* Cook::cookRoutine(void* arg)
{
    (void) arg;
    return nullptr;
}
