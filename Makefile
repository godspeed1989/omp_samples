CC=g++
LIBS=-fopenmp
CPPFLAGS=-fopenmp -Wall -O2
ARGS=
# target as the input
TARGET=

SOURCES+=$(TARGET).cpp

OBJS=${SOURCES:.cpp=.o}


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) ${OBJS} $(LDFLAGS) $(LIBS)

clean:
	rm -rf *.o

clean_all:
	@make clean
	rm -rf $(TARGET)

run:
	@make
	./$(TARGET) $(ARGS)

