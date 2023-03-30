Project: main.o sdisk.o filesys.o block.o shell.o table.o
	c++ -o Project main.o sdisk.o filesys.o block.o shell.o table.o 

main.o: 
	c++ -c main.cpp

sdisk.o: 
	c++ -c sdisk.cpp

filesys.o: 
	c++ -c filesys.cpp

block.o: 
	c++ -c block.cpp

shell.o: 
	c++ -c shell.cpp

table.o: 
	c++ -c table.cpp

clean:
	rm *.o Project
