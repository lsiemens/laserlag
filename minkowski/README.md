# Minkowski
This is a library to impliment types for a 2+1 dimensional minkowski
spacetime. They will have some compatibility with glm::vec3.

## Types
While it would be possible to simply use `glm::vec3` and `glm::mat3`
directly, I want to use the type system to distinguish spacetime points
and 3-vectors which would otherwise both be repersented as `glm::vec3`
since Lorentz transforms are linear. 

 - point : a point in 2+1 minkowski space
 - vector : a reletivistic 3 vector in minkowski space
 - worldline : a sequence of points and vectors forming a timelike path
   through the tangent manifold Mp x TpM

Note: the worldline does not have to include the tangent vectors, but
the 3-velocity will not need to be recostructed, introducting extra error,
when computing transforms for point on the world line and it will make it
easy to check if a new point added to the world line has the same velocity
as the previous point. If the velocities of two points is the same then
they can be merged with a larger time step.
