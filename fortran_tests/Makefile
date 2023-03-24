.POSIX:

FC      = gfortran
FFLAGS  = -std=f2018
LDFLAGS = -L/usr/local/lib/
LDLIBS  = -lblas

.PHONY: all clean sscal sger

all:	sscal sger ssymm

sscal:
	$(FC) $(FFLAGS) $(LDFLAGS) -o sscal test_sscal.f90 $(LDLIBS)

sger: 
	$(FC) $(FFLAGS) $(LDFLAGS) -o sger test_sger.f90 $(LDLIBS)

ssymm: 
	$(FC) $(FFLAGS) $(LDFLAGS) -o ssymm test_ssymm.f90 $(LDLIBS)
clean:
	rm -rf sger sscal ssymm
