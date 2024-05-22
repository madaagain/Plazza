/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_
    #include "PthreadThread.hpp"

class Kitchen;
class Cook : public PthreadThread
{
    public:
        Cook(int id, Kitchen& kitchen);
        ~Cook();
        void setBusy(bool state);
        bool isBusy() const;
        void start();


    protected:
    private:
        Kitchen& _kitchen;
        bool _busy;
        static void* cookRoutine(void* arg);
};

#endif /* !COOK_HPP_ */
