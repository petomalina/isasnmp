CXX = g++
CFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic-errors
SOURCES = SNMPObject.cpp SNMPPacket.cpp SNMPClient.cpp main.cpp
EXECUTABLE = isaSnmpIfLog
OBJECTS = $(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $@

