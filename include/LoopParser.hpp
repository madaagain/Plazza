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
#include <sstream>
#include <cctype>

class LoopParser {
    public:
        LoopParser();
        virtual ~LoopParser();
        void ArgCommandLine();
        void OrdersToList(const std::string& type, const std::string& size, int quantity);
        bool OrderHandling();
        void setOrderInput(const std::string& input);
        void PrintDebug() const;
        std::string& trim(std::string& str);
        bool CheckValidSize(const char *str);
        bool isSizeValid(const char *sizeStr);
        //std::string removeSpacesAroundX(const std::string& input);
        void formatOrder(std::string& str);
        bool isSize(const char *str, int i);
        void clearOrders();
    protected:
    std::string _OrderInput;
    std::string _tmpStrCommand;
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
