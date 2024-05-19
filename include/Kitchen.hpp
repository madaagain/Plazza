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

class Kitchen {
    public:
        Kitchen();
        ~Kitchen();

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
    class Stock
        {
            public:
                Stock() : 
                dough(5), gruyere(5), tomato(5), ham(5), mushroom(5), steak(5), eggplant(5), cheese(5)
                {};
                ~Stock() {};
                int dough;
                int gruyere;
                int tomato;
                int ham;
                int mushroom;
                int steak;
                int eggplant;
                int cheese;
        };
    protected:
    private:
        int _pid;
        Stock _stock;
};

#endif /* !KITCHEN_HPP_ */
