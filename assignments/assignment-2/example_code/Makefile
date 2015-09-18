TARGS = omp-hello


all: $(TARGS)

clean: 
	rm $(TARGS) 

% : %.c Makefile
	gcc -fopenmp -std=gnu99 -o $@ $<

