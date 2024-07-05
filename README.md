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

# Notes
The original code for setting up OpenGL is based on the [tutorial](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/)
from https://github.com/opengl-tutorials/ogl.

