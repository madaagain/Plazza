/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_
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

    protected:
    private:
        int _numCooksPerKitchen;
        std::string _OrderInput;
        int _ingredientRegenerationTime;
        float _cookingTimeMultiplier;
        std::string _inputLine;
        std::vector<pid_t> _pids;
};

#endif /* !RECEPTION_HPP_ */
