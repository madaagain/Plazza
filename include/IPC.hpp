/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** IPC
*/

#ifndef IPC_HPP_
    #define IPC_HPP_
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include <string>
    #include <string.h>

class IPC {
    private:
        int msgid;
        key_t key;

    public:
        IPC();
        ~IPC();
        void sendMessage(int kitchenId, const std::string& message);
        std::string receiveMessage(int kitchenId);
};

#endif /* !IPC_HPP_ */
