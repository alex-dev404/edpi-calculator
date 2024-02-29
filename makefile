CC = g++
CFLAGS = -std=c++11 -I/path/to/sfml/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -L/path/to/sfml/lib
SOURCE = /home/alex/Área de trabalho/app dpi/main.cpp
OBJECT = /home/alex/Área de trabalho/app dpi/main.o
EXECUTABLE = /home/alex/Área de trabalho/app dpi/EDPI_Calculator

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJECT): $(SOURCE)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECT) $(EXECUTABLE)
