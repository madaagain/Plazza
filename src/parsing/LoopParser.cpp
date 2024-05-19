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

void LoopParser::setOrderInput(const std::string& input)
{
    this->_OrderInput = input;
}

/** @brief Basic commandline GUI */
void LoopParser::ArgCommandLine()
{
    if (_OrderInput.empty()) {
        std::cout << "No command entered." << std::endl;
        return;
    }

    OrderHandling(); // Parse et traite chaque commande

    PrintDebug(); // Affiche les commandes actuelles stockées
    std::cout << "Processing command: " << _OrderInput << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Command processed." << std::endl;
}

void LoopParser::OrderHandling()
{
    std::istringstream commandStream(_OrderInput);

    while (std::getline(commandStream, _tmpStrCommand, ';')) {
        trim(_tmpStrCommand);

        std::istringstream detailStream(_tmpStrCommand);
        std::string type, sizeQuantity;
        std::string size;
        int quantity;

        if (!(detailStream >> type >> sizeQuantity)) {
            std::cerr << "Failed to parse command: " << _tmpStrCommand << std::endl;
            continue;
        }

        size_t xPos = sizeQuantity.find('x');
        if (xPos == std::string::npos || xPos == 0 || xPos == sizeQuantity.size() - 1) {
            std::cerr << "Invalid size and quantity format in command: " << _tmpStrCommand << std::endl;
            continue;
        }

        try {
            size = sizeQuantity.substr(0, xPos);
            quantity = std::stoi(sizeQuantity.substr(xPos + 1));
        } catch (const std::exception& e) {
            std::cerr << "Error parsing size or quantity from '" << sizeQuantity << "' in command: " << _tmpStrCommand << std::endl;
            continue;
        }

        OrdersToList(type, size, quantity);
    }
}


std::string& LoopParser::trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) return str;
    return str = str.substr(first, (last - first + 1));
}

/** @brief function still in developement*/
/*
void LoopParser::OrderHandling()
{
    Order *OrderTypes;
    std::istringstream commandStream(_OrderInput);

    while (std::getline(commandStream, _tmpStrCommand, ';')) { // Découpe chaque commande individuellement pour clean la str
        std::istringstream detailStream(_tmpStrCommand);
        OrderTypes->type;
        OrderTypes->size;
        OrderTypes->quantity;

        if (!(detailStream >> OrderTypes->type >> OrderTypes->size >> OrderTypes->quantity)) {
            std::cerr << "Failed to parse command: " << _tmpStrCommand << std::endl;
            continue;
        }

        OrderTypes->size.pop_back(); // Ici je Supp le dernier caractère qui est 'x'
        OrderTypes->quantity = std::stoi(OrderTypes->size.substr(OrderTypes->size.find('x') + 1));
        OrderTypes->size = OrderTypes->size.substr(0, OrderTypes->size.find('x')); //Sa nous permet de recup la taille sans la qt

        OrdersToList(OrderTypes->type, OrderTypes->size, OrderTypes->quantity);
    }
}
*/

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
        std::cout << "Order: " << current->type << ", Size: " << current->size << ", Quantity: " << current->quantity << std::endl;
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