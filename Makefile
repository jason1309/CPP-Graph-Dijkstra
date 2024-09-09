OPTIONS = -O0 -Wall

all: TP3

TP3: TP3.cpp Graphe.h Point.h Chemin.h Traitement.h
	g++ $(OPTIONS) -o $@ TP3.cpp


clean :
	\rm -f *.o
	\rm -f $(NOM)

archive : clean
	\rm -f TP3.tar
	\rm -f TP3.tar.gz
	tar cvf TP3.tar *
	gzip TP3.tar