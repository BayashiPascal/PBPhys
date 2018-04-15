#directory
PBERRDIR=../PBErr
SHAPOIDDIR=../Shapoid
PBMATHDIR=../PBMath
GSETDIR=../GSet

# Build mode
# 0: development (max safety, no optimisation)
# 1: release (min safety, optimisation)
# 2: fast and furious (no safety, optimisation)
BUILDMODE=0

include $(PBERRDIR)/Makefile.inc

INCPATH=-I./ -I$(PBERRDIR)/ -I$(PBMATHDIR)/ -I$(GSETDIR)/ -I$(SHAPOIDDIR)/
BUILDOPTIONS=$(BUILDPARAM) $(INCPATH)

# compiler
COMPILER=gcc

#rules
all : main

main: main.o pberr.o pbphys.o shapoid.o pbmath.o gset.o Makefile 
	$(COMPILER) main.o pberr.o shapoid.o pbmath.o gset.o pbphys.o $(LINKOPTIONS) -o main

main.o : main.c $(PBERRDIR)/pberr.h pbphys.h pbphys-inline.c Makefile
	$(COMPILER) $(BUILDOPTIONS) -c main.c

pbphys.o : pbphys.c pbphys.h pbphys-inline.c Makefile $(SHAPOIDDIR)/shapoid.h $(SHAPOIDDIR)/shapoid-inline.c
	$(COMPILER) $(BUILDOPTIONS) -c pbphys.c

pberr.o : $(PBERRDIR)/pberr.c $(PBERRDIR)/pberr.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(PBERRDIR)/pberr.c

shapoid.o : $(SHAPOIDDIR)/shapoid.c $(SHAPOIDDIR)/shapoid.h $(SHAPOIDDIR)/shapoid-inline.c $(PBMATHDIR)/pbmath.h $(PBMATHDIR)/pbmath-inline.c $(GSETDIR)/gset.h $(GSETDIR)/gset-inline.c $(PBERRDIR)/pberr.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(SHAPOIDDIR)/shapoid.c

pbmath.o : $(PBMATHDIR)/pbmath.c $(PBMATHDIR)/pbmath-inline.c $(PBMATHDIR)/pbmath.h Makefile $(PBERRDIR)/pberr.h
	$(COMPILER) $(BUILDOPTIONS) -c $(PBMATHDIR)/pbmath.c

gset.o : $(GSETDIR)/gset.c $(GSETDIR)/gset-inline.c $(GSETDIR)/gset.h Makefile $(PBERRDIR)/pberr.h
	$(COMPILER) $(BUILDOPTIONS) -c $(GSETDIR)/gset.c

clean : 
	rm -rf *.o main

valgrind :
	valgrind -v --track-origins=yes --leak-check=full --gen-suppressions=yes --show-leak-kinds=all ./main
	
unitTest :
	main > unitTest.txt; diff unitTest.txt unitTestRef.txt
