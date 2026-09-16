# Process Synchronization in C++

An academic C++ project demonstrating process synchronization and concurrency using POSIX threads (Pthreads) and semaphores.

## Overview

This project implements the classic **Dining Philosophers Problem** to demonstrate how multiple threads can safely access shared resources using semaphores.

Five philosopher threads alternate between thinking and eating. Each philosopher must acquire two chopsticks before eating. Semaphores are used to control access to each chopstick and prevent multiple philosophers from using the same resource simultaneously.

## Technologies Used

- C++
- POSIX Threads (Pthreads)
- POSIX Semaphores
- Linux/Unix system calls
- `iostream`
- `unistd.h`

## Key Concepts Demonstrated

- Multithreading
- Process synchronization
- Mutual exclusion
- Semaphores
- Resource management
- Deadlock prevention
- Concurrent programming

## How It Works

The program creates five philosopher threads and five semaphores representing the chopsticks.

Each philosopher repeatedly:

1. Thinks for a random period of time.
2. Becomes hungry and attempts to acquire two chopsticks.
3. Eats after acquiring both chopsticks.
4. Releases both chopsticks.
5. Returns to thinking.

### Deadlock Prevention

To prevent deadlock, philosophers normally acquire their **left chopstick first and then their right chopstick**.

The last philosopher uses the opposite order, acquiring the **right chopstick first and then the left chopstick**.

This breaks the circular waiting condition that can otherwise cause all philosophers to become stuck waiting for one another.

## Example Output

```text
Philosopher 0 is thinking...
Philosopher 1 is thinking...
Philosopher 2 is thinking...
Philosopher 3 is thinking...
Philosopher 4 is thinking...

Philosopher 0 is hungry, trying to pick up chopsticks...
Philosopher 0 is trying to pick up left chopstick...
Philosopher 0 picked up left chopstick.
Philosopher 0 is trying to pick up right chopstick...
Philosopher 0 picked up right chopstick.
Philosopher 0 is eating...

Philosopher 0 finished eating and put down chopsticks.
