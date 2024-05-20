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

    if (!OrderHandling()) {
        std::cout << "Command processing aborted due to errors." << std::endl;
        return;
    }

    PrintDebug(); // Ici je Display les Order de pizza dans la liste
    std::cout << "Processing command: " << _OrderInput << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Command processed." << std::endl;
}

bool LoopParser::OrderHandling()
{
    std::istringstream commandStream(_OrderInput);
    std::string tmpStrCommand;
    bool allCommandsValid = true;

    /** @brief Not functionnal error condition checker
     * 
    if (!CheckValidSize(_OrderInput.c_str())) {
        std::cerr << "Order rejected due to invalid pizza size." << std::endl;
        return false;
    }
    */

    while (std::getline(commandStream, tmpStrCommand, ';')) {
        formatOrder(tmpStrCommand);

        std::istringstream detailStream(tmpStrCommand);
        std::string type, sizeQuantity;
        std::string size;
        int quantity;

        if (!(detailStream >> type >> sizeQuantity)) {
            std::cerr << "Failed to parse command: " << tmpStrCommand << std::endl;
            allCommandsValid = false;
            continue;
        }

        size_t xPos = sizeQuantity.find('x');
        if (xPos == std::string::npos || xPos == 0 || xPos == sizeQuantity.size() - 1) {
            std::cerr << "Invalid size and quantity format in command: " << tmpStrCommand << std::endl;
            allCommandsValid = false;
            continue;
        }

        try {
            size = sizeQuantity.substr(0, xPos);
            quantity = std::stoi(sizeQuantity.substr(xPos + 1));
        } catch (const std::exception& e) {
            std::cerr << "Error parsing size or quantity from '" << sizeQuantity << "' in command: " << tmpStrCommand << std::endl;
            allCommandsValid = false;
            continue;
        }

        OrdersToList(type, size, quantity);
    }

    return allCommandsValid;
}

void LoopParser::formatOrder(std::string& str)
{
    for (size_t i = 0; i < str.size(); ++i) {
        int sizeLength = isSize(str.c_str(), i);
        if (sizeLength > 0 && i + sizeLength < str.size() - 1 && str[i + sizeLength] == ' ' && str[i + sizeLength + 1] == 'x') {
            str.erase(i + sizeLength, 1);
        }
    }
}

bool LoopParser::isSizeValid(const char *sizeStr)
{
    if (std::strncmp(sizeStr, "XXL", 3) == 0) return true;
    if (std::strncmp(sizeStr, "XL", 2) == 0) return true;
    if (*sizeStr == 'L') return true;
    if (*sizeStr == 'M') return true;
    if (*sizeStr == 'S') return true;
    return false;
}

bool LoopParser::CheckValidSize(const char *str)
{
    const char *pForStr = str;
    while (*pForStr) {
        if (std::isalpha(*pForStr)) {
            if (!isSizeValid(pForStr)) {
                std::cerr << "Invalid pizza size found: Command cancelled." << std::endl;
                return false;
            }

            while (*pForStr && !std::isspace(*pForStr)) ++pForStr;
            ++pForStr;
        }
    }

    return true;
}
bool LoopParser::isSize(const char *str, int i)
{
    if (strncmp(&str[i], "XXL", 3) == 0 && (str[i+3] == ' ' || str[i+3] == '\0' || str[i+3] == 'x')) return true;

    if (strncmp(&str[i], "XL", 2) == 0 && (str[i+2] == ' ' || str[i+2] == '\0' || str[i+2] == 'x')) return true;

    if (str[i] == 'L' && (str[i+1] == ' ' || str[i+1] == '\0' || str[i+1] == 'x')) return true;

    if (str[i] == 'M' && (str[i+1] == ' ' || str[i+1] == '\0' || str[i+1] == 'x')) return true;

    if (str[i] == 'S' && (str[i+1] == ' ' || str[i+1] == '\0' || str[i+1] == 'x')) return true;

    return false;
}

std::string& LoopParser::trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) return str;
    return str = str.substr(first, (last - first + 1));
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