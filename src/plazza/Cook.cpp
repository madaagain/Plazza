/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Cook
*/

#include "Cook.hpp"

Cook::Cook(int id) :
    _id(id), _busy(false)
{
}

Cook::~Cook()
{
}

void Cook::start()
{
    int ret = pthread_create(&_workerThread, nullptr, &Cook::cookRoutine, this);
    if (ret < 0)
    {
        std::cerr << "Thread " << _id << " could not be created.\n";
    }
}

void Cook::join()
{
    pthread_join(_workerThread, nullptr);
}

void Cook::setBusy(bool state)
{
    _busy = state;
}

bool Cook::isBusy() const
{
    return _busy;
}

int Cook::getId() const {
    return _id;
}

void* Cook::cookRoutine(void* arg)
{
    (void) arg;
    return nullptr;
}
