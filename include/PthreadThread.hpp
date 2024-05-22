/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** PthreadThread
*/

#ifndef PTHREADTHREAD_HPP_
    #define PTHREADTHREAD_HPP_
    #include <pthread.h>
    #include <iostream>

class PthreadThread {
    public:
        PthreadThread(int id);
        ~PthreadThread();

        void start(void *(*routine)(void *));
        void join();
        int getId() const;
        pthread_t *getThread();

    protected:
    private:
        int _id;
        pthread_t _workerThread;
};

#endif /* !PTHREADTHREAD_HPP_ */
