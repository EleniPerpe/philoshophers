philosophers is a simulation of the classic "Dining Philosophers" problem, where a set of philosophers sit around a table, each needing two forks to eat spaghetti. Philosophers take turns thinking, eating, and sleeping, while making sure not to starve. The simulation uses threads to represent the philosophers, and mutexes are used to ensure that forks are not duplicated between philosophers.

The goal is to simulate the philosophers' behavior with correct synchronization to prevent deadlock and starvation while adhering to a set of timing rules for eating, thinking, and sleeping.

