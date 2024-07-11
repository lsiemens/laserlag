# Laser Lag {#mainpage}
This is a proof of concept for a top down shooter that incorporates
special relativity. The main focus will be the apparent lag in objects
since it takes time for information to arrive. I think that this lag may
make it possible to practically experience the relativity of simultaneity.

The top down perspective means we can treat the world as a 2 + 1 dimensional
spacetime (this perspective will involve some faking).

This project is broken into three main parts:
 - [minkowski](minkowski/README.md): A math library for relativistic 3-vectors
 - [poincare](poincare/README.md): The 2D game engine based on a 2+1 spacetime
 - laserlag: The top down shooter using the poincare engine

# Theory
Any [documentation](theory/README.md) on the general theory behind this project should be
maintained in `theory/` while theory and discussion of specific implementation
should be in the respective directories

# Build
This project uses `cmake` to setup build scripts. To keep the directories
clean I would build in a separate directory with the following commands.

`mkdir ./build; cd ./build`
`cmake ..; make`

## Tests
Automated tests can be run with the command `ctest` after the project has
been built. In addition to tests using `gtest`, I have been using the
examples to act as larger multi component tests. There is an option to run
the examples as tests along with the other tests using `ctest`. If the
variable `BUILD_EXAMPLES_AS_TESTS` is set to true in the root `CMakeLists.txt`,
then the examples will be added as tests with the label `examples` otherwise
they will be compiled but not recognized as tests. If the examples are
included as tests they you can still run the basic tests with out the
examples with the command `ctest -LE examples`.

## Examples
From the build directory compiled examples are located at `./poincare/examples`.
The examples are setup to be ran manually from this directory, and already
have any necessary resources (shaders, sprite files) in the directory
`./poincare/examples/resources`. As noted if `BUILD_EXAMPLES_AS_TESTS` is
set to true then the examples can be run with the other tests using `ctest`.
If you want to run the examples without the other tests use the command
`ctests -L examples`.


# Notes
The original code for setting up OpenGL is based on the [tutorial](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/)
from https://github.com/opengl-tutorials/ogl.

