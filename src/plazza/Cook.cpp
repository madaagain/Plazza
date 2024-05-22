/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Cook
*/

#include "Cook.hpp"

Cook::Cook(int id, Kitchen& kitchen) :
    PthreadThread(id), _kitchen(kitchen), _busy(false)
{
}

Cook::~Cook()
{
}

void* Cook::cookRoutine(void* arg)
{
    (void) arg;
    std::cout << "Cook awaiting order !" << std::endl;
    return nullptr;
}

void Cook::start()
{
    int ret = pthread_create(getThread(), nullptr, cookRoutine, this);
    if (ret < 0)
    {
        std::cerr << "Thread " << getId() << " could not be created.\n";
    }
}
