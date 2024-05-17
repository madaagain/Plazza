/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** IMutex
*/

#ifndef IMUTEX_HPP_
    #define IMUTEX_HPP_

class Imutex {
    public :
    virtual ~Imutex() = default ;
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual void trylock() = 0;
};

#endif /* !IMUTEX_HPP_ */
