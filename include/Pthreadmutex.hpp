/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Pthreadmutex
*/

#ifndef PTHREADMUTEX_HPP_
    #define PTHREADMUTEX_HPP_
    #include "IMutex.hpp"
    #include <pthread.h>

class Pthreadmutex : public Imutex{
    public:
        Pthreadmutex();
        ~Pthreadmutex() override;
        void lock() override;
        void unlock() override;
        void trylock() override;

        pthread_mutex_t& getMtx();

    protected:
    private:
        pthread_mutex_t _mutex;
};

#endif /* !PTHREADMUTEX_HPP_ */
