/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** LoopParser
*/

#ifndef LOOPPARSER_HPP_
#define LOOPPARSER_HPP_

#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

class LoopParser {
    public:
        LoopParser();
        virtual ~LoopParser();
        void ArgCommandLine();
        void OrdersToList(const std::string& type, const std::string& size, int quantity);
        void PrintDebug() const;
        void clearOrders();
    protected:
    std::string OrderInput;
    private:
        struct Order {
            std::string type;
            std::string size;
            int quantity;
            Order* next;

            Order(const std::string& t, const std::string& s, int q) : type(t), size(s), quantity(q), next(nullptr) {}
        };

        Order* headOrder;
    };


#endif /* !LOOPPARSER_HPP_ */
