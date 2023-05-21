Prog: GenDict.o main.o Student.o
	gcc *.c -o prog
GenDict.o: GenDict.c GenDict.h
	gcc -c GenDict.c
main.o: main.c Student.h GenDict.h
	gcc -c main.c
Student.o: Student.c Student.h GenDict.h
	gcc -c Student.c
clean:
	rm -f *.o prog
