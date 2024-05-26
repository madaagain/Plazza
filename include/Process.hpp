/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Process
*/

#ifndef PROCESS_HPP_
    #define PROCESS_HPP_
    #include <iostream>
    #include <exception>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>

class Process {
    public:
        Process();
        ~Process();
        void forkProcess();
        void waitProcess();
        bool isChild() const;
        bool isParent() const;
        pid_t getPid() const;

    protected:
    private:
        pid_t pid;
};

#endif /* !PROCESS_HPP_ */
