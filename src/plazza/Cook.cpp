/*
** EPITECH PROJECT, 2024
** Plazza [WSL: Ubuntu]
** File description:
** Cook
*/

#include "Cook.hpp"
#include "Kitchen.hpp"
#include <mutex>

Cook::Cook(int id, Kitchen& kitchen) :
    PthreadThread(id), _kitchen(kitchen), _busy(false)
{
}

Cook::~Cook()
{
}

void* Cook::cookRoutine(void* arg)
{
    Cook* cook = static_cast<Cook*> (arg);
    Kitchen& kitchen = cook->_kitchen;

    while (kitchen.isActive()) {
        kitchen.getMtx().lock();
        while (kitchen.getQueue().empty() && kitchen.isActive()) {
            pthread_cond_wait(&(kitchen.getCond()), &(kitchen.getMtx().getMtx()));
        }

        if (!kitchen.getQueue().empty())
        {
            int pizza = kitchen.getQueue().front();
            kitchen.getQueue().pop();
            kitchen.setPizzasinQueue();
            cook->setBusy(true);
            kitchen.getMtx().unlock();

            std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(3 * kitchen.getMultiplier())));
            cook->setBusy(false);
        } else
        {
            kitchen.getMtx().unlock();
        }
        pthread_cond_signal(&kitchen.getCond());
    }
    return nullptr;
}

void Cook::start()
{
    int ret = pthread_create(getThread(), nullptr, cookRoutine, this);
    if (ret < 0)
    {
        std::cerr << "Thread " << getId() << " could not be created.\n";
    }
}

void Cook::setBusy(bool state)
{
    _busy = state;
}

bool Cook::isBusy() const
{
    return _busy;
}
