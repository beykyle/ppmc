# ppmc
Toy code to calculate production cross sections in pp hard scattering collisions to leading order at tree level using Monte Carlo integration over the ELHQ parton distribution functions.

## to build, test and run
```
make
./ppmc_test
./ppmc
```

## to calculate a cross section

Let's do our own calculation, in a new directory called `src/my_calc`. Create a file in `src/my_calc/` with a main function. Include any other files you need as normal, and place them in `src/my_calc/`. Using `mc::Integrate2D` and the parton distribution functions in `elhq::` a variety of tree-level hard scattering diagrams can be computed. See `src/ppmc.cpp` for an example; calculating the Drell-Yan pp -> μ+μ- cross section for multiple low-energy cutoffs. 

Add your file(s) (lets call it `src/my_calc/my_calculation.cpp`, which `#includes` `src/my_calc/support.hpp`, which is implemented in `src/my_calc/support.cpp`) as a target to the `Makefile` like so:

```
MYCALC_DIR         = ./my_calc
MYCALC_FILES       = $(wildcard $(MYCALC_DIR)/*.cpp)
MYCALC_OBJ_FILES   = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/my_calc/%.o,$(MYCALC_FILES))

my_calculation: $(OBJ_FILES_NOPP) $(MYCALC_FILES)
  $(CC) $(LDFLAGS) -o $@ $^ 
```

And build and run:

```
make my_calculation
./my_calculation
```
