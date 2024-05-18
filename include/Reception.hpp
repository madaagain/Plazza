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

    protected:
    private:
        int _numCooksPerKitchen;
        int _ingredientRegenerationTime;
        float _cookingTimeMultiplier;
        std::vector<pid_t> _pids;
};

#endif /* !RECEPTION_HPP_ */
