# Philosophers

The **Philosophers** project is an implementation of the classic **Dining Philosophers Problem**. This problem is often used in computer science to illustrate synchronization issues and techniques for concurrent programming. The project is written in **C**.

## Project Overview

In this project, philosophers sit at a table, where each philosopher alternates between **thinking** and **eating**. However, the number of forks available is equal to the number of philosophers, but each philosopher needs two forks to eat. The challenge is to design a solution that allows the philosophers to eat **without causing a deadlock** and also **preventing starvation**.

## Features

- **Concurrency Handling** – Proper handling of multiple threads to ensure that the philosophers can think and eat concurrently without deadlock.
- **Synchronization** – Use of **mutexes** to manage access to shared resources.
- **Simulation** – Visualization of the philosophers’ states (**thinking, eating, waiting**) during the simulation.

## Implementation Details

The project follows the rules set by **42 School** and adheres to strict constraints regarding thread management and memory handling. Key implementation details include:

- 🧵 **Threads for Each Philosopher** – Each philosopher is represented by a separate thread, ensuring concurrent execution.
- 🔒 **Mutex for Forks** – Each fork is protected by a mutex to prevent race conditions.
- 🚫 **Avoiding Deadlocks** – Various strategies, such as controlling fork-picking order and introducing small delays, are implemented to prevent deadlock scenarios.

## Getting Started

To get started with the project, you will need to have a **C compiler** and **Make** installed on your system.

### Prerequisites

- **GCC** (or any C compiler)
- **Make**

### Compilation & Execution

To compile and run the project, use the following commands:

```sh
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
## License

This project is licensed under the **Creative Commons Attribution 4.0 International (CC BY 4.0)** License.  

🔗 **Full license text:** [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) 
