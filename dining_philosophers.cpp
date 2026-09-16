#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *((int*)arg);
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    
    while(1) {
        // Thinking
        std::cout << "Philosopher " << id << " is thinking..." << std::endl;
        sleep(rand() % 3 + 1);
        
        // Hungry and trying to pick up chopsticks
        std::cout << "Philosopher " << id << " is hungry, trying to pick up chopsticks..." << std::endl;
        
        // Deadlock prevention: last philosopher picks up right chopstick first
        if (id == NUM_PHILOSOPHERS - 1) {
            std::cout << "Philosopher " << id << " is trying to pick up right chopstick..." << std::endl;
            sem_wait(&chopsticks[right]);
            std::cout << "Philosopher " << id << " picked up right chopstick." << std::endl;
            
            std::cout << "Philosopher " << id << " is trying to pick up left chopstick..." << std::endl;
            sem_wait(&chopsticks[left]);
            std::cout << "Philosopher " << id << " picked up left chopstick." << std::endl;
        } else {
            std::cout << "Philosopher " << id << " is trying to pick up left chopstick..." << std::endl;
            sem_wait(&chopsticks[left]);
            std::cout << "Philosopher " << id << " picked up left chopstick." << std::endl;
            
            std::cout << "Philosopher " << id << " is trying to pick up right chopstick..." << std::endl;
            sem_wait(&chopsticks[right]);
            std::cout << "Philosopher " << id << " picked up right chopstick." << std::endl;
        }
        
        // Eating
        std::cout << "Philosopher " << id << " is eating..." << std::endl;
        sleep(rand() % 3 + 1);
        
        // Finished eating, put down chopsticks
        sem_post(&chopsticks[left]);
        sem_post(&chopsticks[right]);
        std::cout << "Philosopher " << id << " finished eating and put down chopsticks." << std::endl;
        
        sleep(rand() % 2 + 1);
    }
    
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize semaphores for chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }
    
    // Keep main thread alive
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }
    
    return 0;
}