philosophers is a simulation of the classic "Dining Philosophers" problem, where a set of philosophers sit around a table, each needing two forks to eat spaghetti. Philosophers take turns thinking, eating, and sleeping, while making sure not to starve. The simulation uses threads to represent the philosophers, and mutexes are used to ensure that forks are not duplicated between philosophers.

The goal is to simulate the philosophers' behavior with correct synchronization to prevent deadlock and starvation while adhering to a set of timing rules for eating, thinking, and sleeping.

Key Concepts:
Philosophers: Each philosopher is represented as a thread. A philosopher can either think, eat, or sleep.
Forks: Each philosopher has two forks, one on the left and one on the right. A philosopher can only eat if they have both forks. Forks are shared between adjacent philosophers.
Mutexes: Each fork is protected by a mutex to avoid data races and ensure that no two philosophers use the same fork simultaneously.
