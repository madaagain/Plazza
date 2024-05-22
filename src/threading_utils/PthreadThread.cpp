/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** PthreadThread
*/

#include "PthreadThread.hpp"

PthreadThread::PthreadThread(int id) :
    _id(id)
{
}

PthreadThread::~PthreadThread()
{
}


void PthreadThread::start(void *(*routine)(void *))
{
    int ret = pthread_create(&_workerThread, nullptr, routine, this);
    if (ret < 0)
    {
        std::cerr << "Thread " << _id << " could not be created.\n";
    }
}

void PthreadThread::join()
{
    pthread_join(_workerThread, nullptr);
}

int PthreadThread::getId() const
{
    return _id;
}

pthread_t* PthreadThread::getThread()
{
    return &_workerThread;
}