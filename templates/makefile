# Directories
bin = bin
source = src
headers = hdr

# Files
ofiles = $(bin)/$$PROJECT_ALIAS$$.o
executable = $$PROJECT_ALIAS$$.exe

# Linker Settings
includes =
libraries =
link = $(includes) $(libraries)

# Compiler Settings
cppVersion = -std=c++23
compSettings = -Wall $(cppVersion)

compTags = $(compSettings) $(link)

all: $(bin)/$(exe) | $(bin)

$(bin)/$(exe): $(ofiles) | $(bin)
	g++ $(ofiles) -o $(bin)/$(exe)

$(bin)/$$PROJECT_ALIAS$$.o: $$PROJECT_ALIAS$$.cpp | $(bin)
	g++ $(compTags) -c $$PROJECT_ALIAS$$.cpp -o $(bin)/$$PROJECT_ALIAS$$.o

clean:
	rm $(bin) -r
