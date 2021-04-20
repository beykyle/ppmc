# ppmc
Toy code to calculate production cross sections in pp hard scattering collisions to leading order at tree level using Monte Carlo integration over the ELHQ parton distribution functions.

## to build, test and run
```
make
./ppmc_test
./ppmc
```

## to calculate a cross section
Create a file in `src./` with a main function. Using `mc::Integrate2D` and the parton distribution functions in `elhq::`, a variety of tree-level diagrams can be computed. See `src/ppmc.cpp` for an example; calculating the Drell-Yan pp -> μ+μ- cross section for multiple low-energy cutoffs. 

Add your file (lets call it `src/my_calculation.cpp`) as a target to the `Makefile`:

```
my_calculation: $(OBJ_FILES_NOPP)
  $(CC) $(LDFLAGS) -o $@ $^ 
```

And build and run:

```
make my_calculation
./my_calculation
```
