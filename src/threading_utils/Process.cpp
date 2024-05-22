/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Process
*/

#include "Process.hpp"

Process::Process() :
    pid(-1)
{
}

Process::~Process()
{
}

void Process::forkProcess()
{
    pid = fork();
    if (pid < 0) {
        throw std::runtime_error("Fork failed");
    }
}

void Process::waitProcess()
{
    if (pid < 0) {
        throw std::runtime_error("No process to wait for");
    }

    int status;
    if (waitpid(pid, &status, 0) < 0) {
        throw std::runtime_error("Waitpid failed");
    }

    if (WIFEXITED(status)) {
        std::cout << "Child exited with status " << WEXITSTATUS(status) << std::endl;
    } else if (WIFSIGNALED(status)) {
        std::cout << "Child killed by signal " << WTERMSIG(status) << std::endl;
    } else if (WIFSTOPPED(status)) {
        std::cout << "Child stopped by signal " << WSTOPSIG(status) << std::endl;
    } else if (WIFCONTINUED(status)) {
        std::cout << "Child continued" << std::endl;
    }
}

bool Process::isChild() const {
    return pid == 0;
}

bool Process::isParent() const {
    return pid > 0;
}
