/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** LoopParser
*/

#ifndef LOOPPARSER_HPP_
#define LOOPPARSER_HPP_
#define buff_max 25
#define mod %

#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <sstream>
#include <cctype>
#include <mutex>
#include <vector>

class LoopParser {

    struct Order {
        std::string type;
        std::string size;
        int quantity;
        Order* next;
            Order(const std::string& t, const std::string& s, int q) : type(t), size(s), quantity(q), next(nullptr) {}
        };
        Order* buff[buff_max];
        Order* headOrder;
    public:

        LoopParser();
        virtual ~LoopParser();
        void ArgCommandLine();
        void addToBuffer(const std::string& orderDetails);
        //void addToBuffer();
        void OrdersToList(const std::string& type, const std::string& size, int quantity);
        Order *CreateOrderFromInput();
        bool OrderHandling();
        void setOrderInput(const std::string& input);
        void PrintDebug() const;
        std::string& trim(std::string& str);
        bool CheckValidSize(const char *str);
        bool isSizeValid(const std::string& command, const std::vector<std::string>& validSizes);
        //std::string removeSpacesAroundX(const std::string& input);
        void formatOrder(std::string& str);
        //void addToBuffer(const std::string& orderDetails);
        bool isSize(const char *str, int i);
        void clearOrders();


        /** @addtogroup Internal process communication*/
        void consumerProcess();
        void producerProcess();
    protected:
    std::string _OrderInput;
    std::string _tmpStrCommand;

    /** @addtogroup Internal process communication*/
    std::atomic<int> _free_index{0};
    std::atomic<int> _full_index{0};
    std::mutex mtx;

};

#endif /* !LOOPPARSER_HPP_ */
