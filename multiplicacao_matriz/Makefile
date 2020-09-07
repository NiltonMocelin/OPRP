NVCC = nvcc
CCFLAGS=
LDFLAGS= -lm
TARGET= multiplicacao
export PATH=/usr/bin/:$PATH

all: $(TARGET)

multiplicacao: multiplicacao_cuda.cu toolsv3.cu
	$(NVCC) $(CCFLAGS) multiplicacao_cuda.cu toolsv3.cu -o $@ $(LDFLAGS)

clean:
	rm -f *.o *~ $(TARGET)
