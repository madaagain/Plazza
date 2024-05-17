/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** LoopParser
*/

#include "LoopParser.hpp"

LoopParser::LoopParser() : headOrder(nullptr)
{
}

LoopParser::~LoopParser()
{
    clearOrders();
}

/** @brief Basic commandline GUI */
void LoopParser::ArgCommandLine()
{
    std::string input;
    std::cout << "Enter command (or 'exit' to quit): ";
    std::getline(std::cin, input);
    if (input == "exit") {
        throw std::runtime_error("Exit command issued by user.");
    }

    OrdersToList("Margarita", "Large", 2);  // Luan ici je teste juste
    PrintDebug();
    std::cout << "Processing command: " << input << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Command processed." << std::endl;
}

void LoopParser::OrdersToList(const std::string& type, const std::string& size, int quantity)
{
    Order* newOrder = new Order(type, size, quantity);

    if(headOrder == nullptr) {
        headOrder = newOrder;
    } else {
        Order *current = headOrder;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newOrder;
    }
}

void LoopParser::PrintDebug() const
{
    Order *current = headOrder;

    while (current != nullptr) {
        std::cout << "Caca Order: " << current->type << ", Size: " << current->size << ", Quantity: " << current->quantity << std::endl;
        current = current->next;
    }
}

void LoopParser::clearOrders()
{
    Order* current = headOrder;

    while (current != nullptr) {
        Order* next = current->next;
        delete current;
        current = next;
    }
    headOrder = nullptr;
}