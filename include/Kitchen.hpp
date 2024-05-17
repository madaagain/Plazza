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
    protected:
    private:
        int _pid;
};

#endif /* !KITCHEN_HPP_ */
