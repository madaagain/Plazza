/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Pthreadmutex
*/

#include "Pthreadmutex.hpp"

Pthreadmutex::Pthreadmutex()
{
    pthread_mutex_init(&_mutex, nullptr);
}

Pthreadmutex::~Pthreadmutex()
{
    pthread_mutex_destroy(&_mutex);
}

void Pthreadmutex::lock()
{
    pthread_mutex_lock(&_mutex);
}

void Pthreadmutex::unlock()
{
    pthread_mutex_unlock(&_mutex);
}

void Pthreadmutex::trylock()
{
    pthread_mutex_trylock(&_mutex);
}
