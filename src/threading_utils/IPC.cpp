/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** IPC
*/

#include "IPC.hpp"

IPC::IPC()
{
    key = ftok("kitchen_ipc", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
}

IPC::~IPC()
{
    msgctl(msgid, IPC_RMID, NULL);
}

void IPC::sendMessage(int kitchenId, const std::string& message) {
    struct msg_buffer {
        long msg_type;
        char msg_text[100];
    } messageBuffer;

    messageBuffer.msg_type = kitchenId;
    strncpy(messageBuffer.msg_text, message.c_str(), sizeof(messageBuffer.msg_text));
    msgsnd(msgid, &messageBuffer, sizeof(messageBuffer.msg_text), 0);
}

std::string IPC::receiveMessage(int kitchenId) {
    struct msg_buffer {
        long msg_type;
        char msg_text[100];
    } messageBuffer;

    msgrcv(msgid, &messageBuffer, sizeof(messageBuffer.msg_text), kitchenId, 0);
    return std::string(messageBuffer.msg_text);
}
