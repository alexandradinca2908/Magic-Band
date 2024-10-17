build: main.o create.o update.o query.o
	gcc main.o update.o create.o query.o -o tema1

run: build
	./tema1
	rm -r *.o

main.o: main.c
	gcc -c main.c

create.o: create.c
	gcc -c create.c

update.o: update.c
	gcc -c update.c

query.o: query.c
	gcc -c query.c

clean:
	rm -r tema1
	rm -r *.o