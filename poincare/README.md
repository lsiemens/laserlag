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

 - `poincare::FrameTimer`: Time frames to estimate `dt` and report various levels
   of statistics to the console.
 - `poincare::Window`: Setup and contain a GLFW window.
 - `poincare::Shader`: Contain and load OpenGL shader programs.
 - `poincare::Sprite`: Contain and load 2D sprite.
 - `poincare::Controls` : Provide user controls from in a given window.

The ordinary managers include,

 - `poincare::UpdateLogger`: Write text to the console that can be updated every frame.
 - `poincare::WindowManager`: Contain active windows and manage refrences to them.
 - `poincare::SpriteManager`: Contain loaded sprites and manage refrences to them.

The relativistic types include,

 - `poincare::Camera`: Common interface for Cameras.
 - `poincare::Camera2D`: Define the 2D topdown camera view.
 - `poincare::Camera3D`: Define the 3D camera for debugging and analysis of the 2+1
   dimensional spacetime.
 - `poincare::MassiveObject`: Contain object data and follows a timelike path in spacetime.
 - `poincare::MasslessObject`: Contain object data and follows a nullgeodesic in spacetime.
 - `poincare::SpacetimeEvent`: Cointain message originating at a spacetime point. Used to
   alert objects of events in spacetime, ex relativisticaly consistant score system.

The relativistic managers include,

 - `poincare::ObjectManager`: Setup and contain loaded objects in spacetime, defines the
   refrence frame for the system and manages the interactions of objects.
