/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(int id, int numCooks, int ingredientRegenerationTime, float cookingTimeMultiplier)
    : _kitchenId(id), _maxPizzas(2 * numCooks), _numCooks(numCooks), _pizzasInQueue(0),
    _ingredientRegenerationTime(ingredientRegenerationTime), _active(true),
    _cookingTimeMultiplier(cookingTimeMultiplier), _inactivitythread(0), _stockthread(1)
{
    _ingredients = {{"dough", 5}, {"tomato", 5}, {"cheese", 5}, {"ham", 5}, {"mushrooms", 5}};
    createCooks();
    startThreads();
}

Kitchen::~Kitchen()
{
    stopThreads();
}

void Kitchen::createCooks() {
    for (int i = 0; i < _numCooks; ++i) {
        _cooks.emplace_back(i, *this);
    }
}

void Kitchen::processOrders() {
    for (auto& cook : _cooks) {
        cook.start();
    }
}

bool Kitchen::isFull() const {
    return _pizzasInQueue >= _maxPizzas;
}

bool Kitchen::isActive() const {
    return _active;
}

void Kitchen::stopThreads() {
    _stockthread.join();
    _inactivitythread.join();
    for (auto& cook : _cooks) {
        cook.join();
    }
}

void Kitchen::startThreads() {
    _stockthread.start(&Kitchen::stockRegeneration);
}

void* Kitchen::stockRegeneration(void* arg) {
    Kitchen* kitchen = static_cast<Kitchen*>(arg);
    while (kitchen->isActive()) {
        std::cout << "looping\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(kitchen->_ingredientRegenerationTime));
        for (auto& item : kitchen->_ingredients) {
            std::cout << item.first << std::endl;
            item.second += 1;
        }
        std::cout << "Kitchen " << kitchen->_kitchenId << " regenerated stock." << std::endl;
    }
    return nullptr;
}

Pthreadmutex& Kitchen::getMtx()
{
    return _mtx;
}

pthread_cond_t& Kitchen::getCond()
{
    return _cond;
}

std::queue<int>& Kitchen::getQueue()
{
    return _pizzaQueue;
}

void Kitchen::setPizzasinQueue()
{
    _pizzasInQueue--;
}

float Kitchen::getMultiplier() const
{
    return _cookingTimeMultiplier;
}

void Kitchen::closeKitchen()
{
    _active = false;
    pthread_cond_broadcast(&_cond);
    stopThreads();
}