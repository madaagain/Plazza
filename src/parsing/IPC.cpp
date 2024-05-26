/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** LoopParser
*/

/** @brief: This file will store all the functions that will be used for the
 * inter communication between processes using shared memory
*/

#include "LoopParser.hpp"


/** @brief This version adds the full order and node each Order separated in nodes. [DO NOT DELETE, SAVE FILE]*/
/*
void LoopParser::addToBuffer(const std::string& orderDetails)
{
    LoopParser::Order* newOrder = CreateOrderFromInput();
    if (!newOrder) {
        std::cerr << "Failed to create order from input details." << std::endl;
        return;
    }

    int next_free = (_free_index.load(std::memory_order_acquire) + 1) % buff_max;
    //Debug: printf("Check1\n");
    while (next_free == _full_index.load(std::memory_order_acquire)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    //Debug: printf("Check2\n");
    std::lock_guard<std::mutex> lock(mtx);
    if (buff[_free_index.load(std::memory_order_relaxed)] != nullptr) {
        //Debug: printf("Check3\n");
        //delete buff[_free_index.load(std::memory_order_relaxed)];
    }

    buff[_free_index.load(std::memory_order_relaxed)] = newOrder;
    //Debug: printf("Order Check validity:%s\n", newOrder);
    _free_index.store(next_free, std::memory_order_release);
    // Debug: printf("Check4\n");

}
*/

void LoopParser::addToBuffer(const std::string& orderDetails)
{

    if (headOrder == nullptr) {
        std::cerr << "No orders to process." << std::endl;
        return;
    }

    Order* current = headOrder;
    while (current != nullptr) {
        int next_free = (_free_index.load(std::memory_order_acquire) + 1) % buff_max;
        while (next_free == _full_index.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "[ORDER]: " << "Type: " << current->type << ", Size: " << current->size << ", Quantity: " << current->quantity << std::endl;

        std::lock_guard<std::mutex> lock(mtx);
        if (buff[_free_index.load(std::memory_order_relaxed)] != nullptr) {
            //delete buff[_free_index.load(std::memory_order_relaxed)];
        }

        buff[_free_index.load(std::memory_order_relaxed)] = new Order(current->type, current->size, current->quantity);
        _free_index.store(next_free, std::memory_order_release);
        
        current = current->next;
    }
}


void LoopParser::producerProcess()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); /** @brief: Ici je mes le chrono a 100 miliseconde afin que le producer ne remplisse pas le buffer super rapidement*/
        /** @brief: calcule le prochain index dans le tampon qui devrait être écrit. 
         * Je le fait en incrémentant l'index libre actuel _free_index et en prenant le modulo de --> [buff_max] 
         * pour s'assurer qu'il boucle si il atteint la fin du tampon.*/
        int next_free = (_free_index.load(std::memory_order_acquire) + 1) % buff_max;
        
        /** @brief: vérifie si le prochain index libre est égal à l'index _full_index. 
         * S'ils sont égaux, cela signifie que le tampon est plein*/
        while (next_free == _full_index.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        /** @brief: verrouille un mutex je m'assure qu'aucun autre fil ne peut entrer
         * dans une section de code qui pourrait modifier des données partagées*/
        mtx.lock();

        /** @brief: Je vérifie s'il y a déjà un objet Order à l'index libre actuel
         * et le supprime s'il est présent pour éviter
         * les fuites de mémoire avant de placer d'accepter une nouvelle commandes */
        if (buff[_free_index.load(std::memory_order_relaxed)] != nullptr) {
            delete buff[_free_index.load(std::memory_order_relaxed)];
        }
        buff[_free_index.load(std::memory_order_relaxed)] = new Order("Type", "Size", 1); 
        _free_index.store(next_free, std::memory_order_release);

        /** @brief: Je déverrouille le mutex, permettant à d'autres fils
         * qui pourraient être bloqués en attendant ce mutex de procéder */
        mtx.unlock();
    }
}


void LoopParser::consumerProcess()
{
    while (true) {
        while (_free_index.load(std::memory_order_acquire) == _full_index.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::lock_guard<std::mutex> lock(mtx);
        int current_index = _full_index.load(std::memory_order_relaxed);
        Order* consumed_item = buff[current_index];

        std::cout << "Processing order: " << consumed_item->type << std::endl;
        delete consumed_item;

        buff[current_index] = nullptr;
        _full_index.store((current_index + 1) % buff_max, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}