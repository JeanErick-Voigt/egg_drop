# To make the executable TeamDriver type 
# 
#   make 
# 
# Refer to the object files as OBJECTS 
# 
OBJECTS = TeamDriver.o Team.o Person.o

# Compile the objects and store 
# the executable in TeamDriver
TeamDriver: $(OBJECTS)
	gcc $(OBJECTS) -o TeamDriver

TeamDriver.o: Person.h Team.h Person.c Team.c TeamDriver.c
	gcc -c TeamDriver.c

Team.o: Person.h Team.h Person.c Team.c
	gcc -c Team.c

Person.o: Person.h Person.c
	gcc -c Person.c

# Running the Makefile as 
#   make clean 
# removes the object files 
# and the executable. 
clean: 
	rm -f $(OBJECTS) TeamDriver 
