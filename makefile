all:
	cc -c -o ./obj/dataBase.o -I ./include ./src/dataBase.c
	cc -c -o ./obj/gplot.o -I ./include ./src/gplot.c
	cc -o gplotter -I ./include ./obj/dataBase.o ./obj/gplot.o main.c 

clean:
	rm -rf ./obj
	rm gplotter

