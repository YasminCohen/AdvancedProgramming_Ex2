## Task 2 Advanced programming
## Description
In this task we had to train data structures and develop the threading skills.
The background for this task was:
You have an endless stream of data that needs to be processed quickly.
In our task we used a random number generator (provided) that simulates the infinite stream, and your task is to count the number of prime numbers in that stream.
The idea is to parallelize the process, so that the entire processor core is utilized.
It would also be possible to improve the isPrime function as well, if needed.
while maintaining low memory usage (2MB heap limit).
Our main goal was to compare the time it takes to run the program, with or without fuses.


### The generator program
The generator program is responsible for generating a large amount of numbers and printing them to the standard output. The program should be able to generate a large amount of numbers and should be able to generate the same list of numbers with the same key. The program should be able to run in a reasonable amount of time.

### Results
On my computer where I was able to improve the time it takes to run the program by 2x when using as many threads as the number of processors available instead of a single thread, without improving the isPrime function.
When we improved the isPrime function, we were able to improve the time it takes to run the program by 10 times..
Memory usage remains low, heap usage of about 140KB.

Below are the results of the program running with different configurations 
```
$ time ./randomGenerator 0 10000000 | ./primeCounter
491346 total primes.

real    1m11.028s
user    1m8.964s
sys     0m3.009s

$ time ./randomGenerator 0 10000000 | ./myPrimeCounter
491346 total primes.

real    0m8.845s
user    0m20.926s
sys     0m6.379s


## Requirements
* Linux machine (Ubuntu 22.04 LTS preferable)
* GNU C Compiler
* Make

## Building
```
make all
```

## Running
```
# Running the generator program.
./randomGenerator <seed> <num_of_numbers>

# Running the prime counter program with the generator.
./randomGenerator <seed> <num_of_numbers> | ./primeCounter

# Running the prime counter program in thread mod (isPrime improved) with the generator.
./randomGenerator <seed> <num_of_numbers> | ./myPrimeCounter 

# Running the prime counter program in thread mod (isPrime not improved) with the generator.
./randomGenerator <seed> <num_of_numbers> | ./my_prime_counter_without_improve_prime 
```


## Notes
* Use `time` command to measure the time it takes to run the program in different configurations (with/without threads).
* Use '/usr/bin/time -v' to check for memory leaks and to see the memory usage (/usr/bin/time -v ./randomGenerator 0 10000000 | ./myPrimeCounter).
