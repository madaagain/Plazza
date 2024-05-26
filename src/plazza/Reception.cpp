/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Reception
*/

#include "Reception.hpp"
#include "../include/LoopParser.hpp"

Reception::Reception(int numCooksPerKitchen, int ingredientRegenerationTime, float cookingTimeMultiplier) :
    _numCooksPerKitchen(numCooksPerKitchen), _ingredientRegenerationTime(ingredientRegenerationTime),
      _cookingTimeMultiplier(cookingTimeMultiplier), _nextKitchenId(0)
{
    std::cout << "Reception created." << std::endl;
}

Reception::~Reception()
{


}

void Reception::initValue()
{
    _ingredientRegenerationTime = 0;
    _numCooksPerKitchen = 0;
    _cookingTimeMultiplier = 0;
}
void Reception::createKitchen()
{
    Process process;

    try {
        process.forkProcess();

        if (process.isChild()) {
            Kitchen kitchen(_nextKitchenId, _numCooksPerKitchen, _ingredientRegenerationTime, _cookingTimeMultiplier);
            kitchen.processOrders();
            kitchen.receiveOrders();
            _exit(0);
        } else if (process.isParent()) {
            pid_t childPid = process.getPid();
            _pids.push_back(childPid);
        }
    } catch (const std::exception &e) {
        throw e;
    }
}

void Reception::printHelp()
{
    std::cout << "You can order pizzas here by stating: [type] [size] [number]" << std::endl;
    std::cout << "You have to separate each kind by a ';'" << std::endl;
    std::cout << "If you are done for the day, just say 'exit'" << std::endl;
}

/** @brief Main Loop of the programm get the orders, parse them and redistribute them*/
void Reception::start()
{
    std::cout << "Welcome to Plazza's Pizzas, may we have your order ?" << std::endl;
    createKitchen();

    while (true)
    {
        std::getline(std::cin, _inputLine);
        OrderParser.setOrderInput(_inputLine); //Ca nous permet de pouvoir ensuite de save l'input pour la str dans _OrderInput 

        if (_inputLine == "help")
        {
            printHelp();
            continue;
        }
        if (_inputLine == "exit")
        {
            break;
        }
        OrderParser.ArgCommandLine();
        allocateOrder(_inputLine);
    }
}

void Reception::allocateOrder(const std::string& order)
{
    for (int kitchenId : _pids) {
        std::cout << "Sending order to kitchen " << kitchenId << std::endl;
        _ipc.sendMessage(kitchenId, order);
        
        std::string response = _ipc.receiveMessage(kitchenId);
        std::cout << "Awaiting response from kitchen\n";
        std::cout << "Received response from kitchen " << kitchenId << ": " << response << std::endl;

        if (response == "KITCHEN_FULL") {
            continue;
        } else {
            return;
        }
        return;
    }
    createKitchen();
    allocateOrder(order);
}
