# producer-consumer-program-in-c++-
The producer-consumer problem is one of the classical examples of synchronization. The program has been developed in C++(most of the code is still in C).
A consumer can only consumer if there is some item in buffer and a producer can only produce if there is an empty slot in buffer.
The program is multi-threaded. There are a finite number of producers and finite number of consumers. 

To run the above program in terminal:
-g++ filename.cpp -pthread for compiling
-./a.out for execution of program
