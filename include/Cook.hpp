/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_
    #include <pthread.h>
    #include <iostream>

class Cook {
    public:
        Cook(int id);
        ~Cook();
        void start();
        void join();
        void setBusy(bool state);
        bool isBusy() const;
        int getId() const;

        static void* cookRoutine(void* arg);

    protected:
    private:
        int _id;
        bool _busy;
        pthread_t _workerThread;
};

#endif /* !COOK_HPP_ */
