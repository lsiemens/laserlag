# Poincare
This is a library to implement a top down 2D game engine in 2+1 dimensional
minkowski spacetime. The library `minkowski` will be used to handle the
geometry before switching to `glm` when interfacing with `OpenGL`.

## Classes
The classes are categorized by if they are ordinary or "relativistic", as
well as by if they are a type (multiple instances expected) or a manager
(a singleton or single instance expected). The "relativistic" classes
that have contact with the relativistic nature of this engine.

The ordinary types include,

 - FrameTimer: Time frames to estimate `dt` and report various levels
   of statistics to the console.
 - Shader: Contain and load OpenGL shader programs.
 - Sprite: Contain and load 2D sprite.

The ordinary managers include,

 - UpdateLogger: Write text to the console that can be updated every frame.
 - ShaderManager: Contain loaded shaders and manage refrences to them.
 - SpriteManager: Contain loaded sprites and manage refrences to them.

The relativistic types include,

 - MassiveObject: Contain object data and follows a timelike path in spacetime.
 - MasslessObject: Contain object data and follows a nullgeodesic in spacetime.
 - SpacetimeEvent: Cointain message originating at a spacetime point. Used to
   alert objects of events in spacetime, ex relativisticaly consistant score system.

The relativistic managers include,

 - Camera2D: Define the 2D topdown camera view.
 - Camera3D: Define the 3D camera for debugging and analysis of the 2+1
   dimensional spacetime.
 - Spacetime: Setup and contain loaded objects in spacetime, defines the
   refrence frame for the system and manages the interactions of objects.
