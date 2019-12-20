LIBS = -lm -lSDL2 -lSDL2_ttf
OUTPUT = "TimesTable.out"

all : build run

build :
	$(CC) *.c -o $(OUTPUT) $(LIBS)

run :
	./$(OUTPUT)