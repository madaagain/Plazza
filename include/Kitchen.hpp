/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_
    #include <sys/types.h>
    #include <unistd.h>
    #include <exception>
    #include <string>
    #include <map>
    #include <vector>
    #include <chrono>
    #include <thread>
    #include <queue>
    #include "Cook.hpp"
    #include "Pthreadmutex.hpp"
    #include "PthreadThread.hpp"

class Kitchen {
    public:
        Kitchen(int id, int numCooks, int ingredientRegenerationTime, float cookingTimeMultiplier);
        ~Kitchen();
        void createCooks();
        void addPizza(int pizzaType);
        void processOrders();
        bool isFull() const;
        bool isActive() const;
        void closeKitchen();
        void startThreads();
        void stopThreads();
        void displayStatus() const;

        Pthreadmutex& getMtx();
        pthread_cond_t& getCond();
        std::queue<int>& getQueue();
        float getMultiplier() const;

        void setPizzasinQueue();

        static void* stockRegeneration(void* arg);

    class KitchenException : public std::exception
        {
            private:
                std::string _msg;
            public:
                KitchenException(std::string msg): _msg(msg) {};
                const char *what() const noexcept override 
                {
                    return _msg.c_str();
                };
                ~KitchenException() {};
        };
    protected:
    private:
        std::map<std::string, int> _ingredients;
        int _kitchenId;
        int _maxPizzas;
        int _numCooks;
        int _pizzasInQueue;
        int _ingredientRegenerationTime;
        bool _active;
        float _cookingTimeMultiplier;
        std::vector<Cook> _cooks;
        Pthreadmutex _mtx;
        PthreadThread _inactivitythread;
        PthreadThread _stockthread;
        pthread_cond_t _cond;
        std::queue<int> _pizzaQueue;
};

#endif /* !KITCHEN_HPP_ */
