CXX      = g++ #the compiler
CXX_FILE = $(wildcard *.cpp) #make a list of any cpp files in the directory, should only be one right now
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE)) #pattern substitution, assign "TARGET" to be the name of the file without the extension
CXXFLAGS = -g -Wall -Werror -pedantic-errors -fmessage-length=0 #options passed to the compiler to build it a certain way
#-g include debugging info. After debugging you could do -o2 to do optimizations and make code more efficient
#-Wall, -Werror, -pedantic-error - nags you about little tiny errors
#-fmessage-length=0 - error msg formatting

all: #this is where dependencies would go, after the colon
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET) #must be a tab not spaces, then use the variables above to make the command
clean:
	rm -f $(TARGET) $(TARGET).exe #"make clean" to get rid of the compiled files
