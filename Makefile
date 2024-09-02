
CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c99 -g -pedantic -I$(SOURCE_PATH)


LDFLAGS = -pthread

RM = rm -f

SOURCE_PATH = sources
OBJECT_PATH = runFiles
INCLUDE_PATH = headers

SOURCES = $(wildcard $(SOURCE_PATH)/*.c)
HEADERS = $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS = $(subst sources/,runFiles/,$(subst .c,.o,$(SOURCES)))

OBJECTS_GEN = generator.o
OBJECTS_CNT = myPrimeCounter.o Queue.o
OBJECTS_CNT_ONLY_THREADS = my_prime_counter_without_improve_prime.o Queue.o
OBJECTS_CNT_SIMPLE = primeCounter.o
OBJ_FILES_GEN = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_GEN))
OBJ_FILES_CNT = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_CNT))
OBJ_FILES_CNT_SIMPLE = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_CNT_SIMPLE))
OBJ_FILES_CNT_ONLY_THREADS = $(addprefix $(OBJECT_PATH)/, $(OBJECTS_CNT_ONLY_THREADS))

EXECUTABLES = randomGenerator myPrimeCounter my_prime_counter_without_improve_prime primeCounter

.PHONY: all default clean

all: $(EXECUTABLES)

default: all

randomGenerator: $(OBJ_FILES_GEN)
	$(CC) $(CFLAGS) -o $@ $^

myPrimeCounter: $(OBJ_FILES_CNT) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lm

my_prime_counter_without_improve_prime: $(OBJ_FILES_CNT_ONLY_THREADS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

primeCounter: $(OBJ_FILES_CNT_SIMPLE)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(RM) $(OBJECT_PATH)/*.o *.so $(EXECUTABLES)