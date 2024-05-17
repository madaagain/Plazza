/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_
    #include <exception>
    #include <iostream>
    #include <sstream>

class Parser {
    public:
        Parser(int ac, char **av);
        ~Parser();
        float getcookingtime();
        int getnbcooks();
        int getstocktimer();
        class ParserException : public std::exception
        {
            private:
                std::string _msg;
            public:
                ParserException(std::string msg): _msg(msg) {};
                const char *what() const noexcept override 
                {
                    return _msg.c_str();
                };
                ~ParserException() {};
        };
    protected:
    private:
        float _cookingtime;
        int _nbcooks;
        int _stocktimer;
};

#endif /* !PARSER_HPP_ */
