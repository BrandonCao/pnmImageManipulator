SRC=main.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o PNMreader

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o PNMreader
