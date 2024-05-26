/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(int id, int numCooks, int ingredientRegenerationTime, float cookingTimeMultiplier, pid_t recep)
    : _kitchenId(id), _maxPizzas(2 * numCooks), _numCooks(numCooks), _pizzasInQueue(0),
    _ingredientRegenerationTime(ingredientRegenerationTime), _active(true),
    _cookingTimeMultiplier(cookingTimeMultiplier), _inactivitythread(0), _stockthread(1), _recep(recep)
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
    pthread_cond_init(&_cond, nullptr);
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

void Kitchen::addPizza(int pizzaType) {
    if (_pizzasInQueue < _maxPizzas) {
        _pizzaQueue.push(pizzaType);
        _pizzasInQueue++;
        std::cout << "Pizza added to the queue. Signaling condition variable." << std::endl;
        pthread_cond_signal(&_cond);
        _ipc.sendMessage(0, "OK");
    } else {
        _ipc.sendMessage(0, "KITCHEN_FULL");
    }
}

void Kitchen::receiveOrders()
{
    std::string order;
    while (isActive()) {
        _mtx.lock();
        std::cout << "Kitchen ready for orders\n";
        order = _ipc.receiveMessage(_kitchenId);
        std::cout << "Received order :" << order << std::endl;
        addPizza(1);
        _mtx.unlock();
    }
}