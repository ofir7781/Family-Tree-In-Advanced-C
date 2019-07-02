project: projectMain.o tree.o list.o
	gcc projectMain.o tree.o list.o -o project
	
projectMain.o: projectMain.c tree.h list.h
	gcc -c projectMain.c
	
tree.o: tree.c tree.h list.h
	gcc -c tree.c
	
list.o: list.c list.h tree.h
	gcc -c list.c