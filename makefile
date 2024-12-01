# general settings
bin = bin
ofiles = $(bin)/ppg.o

# linker settings
vers = -std=c++23
link = $(vers) -Wall -c

all: $(ofiles) | $(bin)
	g++ $(ofiles) -o $(bin)/ppg

$(bin)/ppg.o: ppg.cpp | $(bin)
	g++ $(link) ppg.cpp -o $(bin)/ppg.o

$(bin):
	mkdir $(bin)

clean:
	rm $(bin) -r
