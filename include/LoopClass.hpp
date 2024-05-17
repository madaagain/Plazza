/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Loop
*/

#ifndef LOOP_HPP_
#define LOOP_HPP_

#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include "LoopParser.hpp"

class LoopClass {
    public:
        LoopClass() {};
        ~LoopClass() {};
        void Loop();
    protected:
    private:
        LoopParser loopParser;
};

#endif /* !LOOP_HPP_ */
