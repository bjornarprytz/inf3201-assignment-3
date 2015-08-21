TARGS = mpi-hello mpi-hello2


all: $(TARGS)

clean: 
	rm $(TARGS) 

% : %.c
	mpicc -o $@ $<

