/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_
    #include "Process.hpp"
    #include "LoopParser.hpp"
    #include "IPC.hpp"
    #include <Kitchen.hpp>
    #include <vector>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <iostream>

class Reception {
    public:
        Reception(int numCooksPerKitchen, int ingredientRegenerationTime, float cookingTimeMultiplier);
        ~Reception();
        void createKitchen();
        void start();
        void printHelp();
        void allocateOrder(const std::string& order);

    protected:
    private:
        int _numCooksPerKitchen;
        std::string _OrderInput;
        int _ingredientRegenerationTime;
        float _cookingTimeMultiplier;
        int _nextKitchenId;
        void initValue();
        std::string _inputLine;
        std::vector<pid_t> _pids;
        LoopParser OrderParser;
        IPC _ipc;
};

#endif /* !RECEPTION_HPP_ */
