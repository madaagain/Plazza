/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_
    #include "PthreadThread.hpp"

class Cook : public PthreadThread
{
    public:
        Cook(int id);
        ~Cook();
        void setBusy(bool state);
        bool isBusy() const;

        static void* cookRoutine(void* arg);

    protected:
    private:
        bool _busy;
};

#endif /* !COOK_HPP_ */
