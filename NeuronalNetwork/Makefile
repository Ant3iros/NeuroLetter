GCC=g++

TARGETS = main

all: $(TARGETS)

%: %.cpp Makefile
	$(GCC) main.cpp -o OCR -lfann -lm

clean:
	rm -f OCR 