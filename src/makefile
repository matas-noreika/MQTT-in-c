#compiler configuration variables
# CXX : compiler to use
# CXXFLAGS : flags to pass into the compiler
CXX = gcc
CXXFLAGS = -iquote ../include

#local directory variables
LOCALBIN = ../bin
LOCALLIB = ../lib

#source file array (set as expanded value using := )
# $(wildcard x) is a function to retrieve all string matches and store in varaible (in this case it stores all source c files in SRCS variable)
SRCS = $(wildcard *.c)

#static libraries that are dependencies in other builds
LIBS = sockets

BINS = socketClient socketServer 

#set clean as a target that doesn't produce a file and doesn't care about modification timestamp 
.PHONY = all cleanall

#handle to remove all exported files
cleanall: cleanbin cleanlib

cleanbin: 
	@-rm $(LOCALBIN)/*.exe 2> /dev/null || true 
	
cleanlib:
	@-rm $(LOCALLIB)/*.o 2> /dev/null || true	

#all rule depends on static libraries to be compiled
all: $(LIBS) $(BINS)	

#this is a rule to compile every static library that is a dependency
$(LIBS): %:%.c
	@$(CXX) $(CXXFLAGS) -c $< -o $(LOCALLIB)/$@.o

#rule to compile the socketClient programme
socketClient: sockets socketClient.c
	@$(CXX) $(CXXFLAGS) $(LOCALLIB)/sockets.o $@.c -o $(LOCALBIN)/$@.exe
 
socketServer: sockets socketServer.c
	@$(CXX) $(CXXFLAGS) $(LOCALLIB)/sockets.o $@.c -o $(LOCALBIN)/$@.exe

