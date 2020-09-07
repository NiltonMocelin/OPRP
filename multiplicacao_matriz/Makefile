NVCC = nvcc
CCFLAGS=
LDFLAGS= -lm
TARGET= multiplicacao

all: $(TARGET)

multiplicacao: multiplicacao_cuda.cu toolsv3.cu
	$(NVCC) $(CCFLAGS) multiplicacao_cuda.cu toolsv3.cu -o $@ $(LDFLAGS)

clean:
	rm -f *.o *~ $(TARGET)
