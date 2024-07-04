# Theory
The core idea that I am trying to explore with laserlag is that the
geometry of minkowski spacetime in effect requires that the actions of
independent actors is buffered. I think this buffer can be exploited to
make a multiplayer game that demonstrates the relativity of simultaneity.

## Motivation
I was watching a video (dev log) where someone was talking about moving
the player character in a multiplayer game. While it makes sense that other
players would have lag when they move, the developer talked about why the
player would also have lag. If the client simply moved the character and
reported that to the surer it would be susceptible to hacking and cheating.
So usually the control inputs are sent to the server which then sends the
new player coordinates back to the client. However due to the time that
this would take the game would be very slow and unresponsive. Instead,
inputs are sent to the surer but also computed and drawn on the client
side this way the screen appears responsive, and when the surer returns
the authoritative determination of the players location if they match
things just continue, but if there is a sufficient discrepancy the client
will update to use the servers location. This prevents hacking while
keeping the game feeling responsive. There are many more details about
client side prediction but this is the general idea from what I recall.

While thinking about this difficulty and the lag in the many players, it
brought to mind special relativity. In that for special relativity everything
that can be observed is necessarily delayed due to the finite speed of
any information. So I began thinking what if you had a game where you
included relativistic effects, the result would look like some kind of
systematic lag.

## Basic Idea
Consider two observers as spatially separated points. Drawing their light
cones will reveal some regions of overlap in the past and future. The
overlap shows when the observers could last have been in contact and when
they could be in contact again. The space between them where there is no
overlap in some sense shows the extent too which they are out of causal
contact. What I mean is that if you draw the worldlines for the two
observers extending to the past and future, for massive observers with
nonconstant acceleration (speed much less than c), these worldlines
intersect with the light cones at four points, indicating when each observer
was last seen from the perspective of the other observer and the point
in the future when it can be next acted on by the other observer. The fact
that there is always some interval along the worldline that is outside
of the light cone of any spacelike separated observer means that there
is some ambiguity in the possible locations of objects. That is for objects
A and B if they are both independent agents that are space like separated,
then from A's perspective the present for B (focus of the light cones)
must be some point along the indeterminate region of the worldline but
the exact location is entirely observable from A's current perspective.
Two independent observers must mutually exist in the indeterminate region
of the other (ie independent actors must remain space like separated
otherwise the actions of the one will be in the past light cone of the other
and so know beforehand).

This in effect bakes in a buffer where A and B have a short history of
actions known to them (and a potential distant future observer) but not
the other. Since the precise locations of observers, along the worldline,
is not measurable by other observers as long as they remain space like
separated (in the in determinant region), the observers can travel down
their worldlines asynchronously while still having a coherent and smooth
perception of the other observers.

As the light cones for A and B evolve along the worldlines, provided
that they remain space like separated they are free to evolve completely
independently. So each player in their respective rest frame would be
evolving along their worldline, but due to time dilation. The relative
rates of motion along the worldlines for different players would not be
the same. This relative motion would cause one player add actions to the
buffer faster then they are recorded by other observers, while the other
player adds actions to the buffer at a rate slower then they are recorded.
So the effective clock of these players is speedup or slowed down as long
as there is room in the buffer.

# Design
laserlag will be a top down shooter taking place in a 2+1 dimensional
spacetime. The worldlines of actors will be recorded and used to display
the actions with correct relativistic effects. While theoretically the
spacetime manifold and valid geometric objects within it exist independent
of representations in any given coordinate system, a practical realization
of these ideas in the computer will require choosing a coordinate system.
Using this preferred coordinate system worldlines and any other geometric
objects can be represented in a straight forward way in the computer and
then transformed into arbitrary coordinate systems. This should not be
taken as a relativity breaking preferred reference frame, but as the frame
of a 3rd party observer recording event from which the underlying geometry
can be inferred. In this project I will attempt to maintain a physically
correct representation of relativity, but there will always be some
physical limitations of this.

## Camera and perspective
The camera perspective will be that of a top down shooter. Immediately this
is in tension with my earlier statement that the spacetime will be 2+1.
The top down perspective implies that the camera is floating above the
field of play requiring a 3rd dimension, while naturally observers in a
2+1 dimensional spacetime would perceive the world as 1 dimensional. However
I think that the 2d perspective can be reasonably justified using the
following argument, provided the occlusion of objects is ignored. Let's
suppose some being exists in this 2+1 dimensional world that can visualize
2D information. The past light cone for this observer can be parameterized
by a single angular variable, so as stated their vision would be 1D.
However, if the being can infer the true size of objects that it sees,
for example by prior knowledge or context, then the distance can be determined
from the actual size and angular size. Once the distance, angle and size
of objects in the visual field are determined, a 2D representation of the
world can be build up. This 2D representation is reasonably correct since,
in a flat non-expanding universe, or likewise at small scale, the angular
diameter distance is equivalent to the proper distance.

Note, in game play to aid in judging speed and changes in speed and to
allow for more of a sensation of motion, I will allow the camera to not
be entirely fixed on the player. Technically this would mean that they
are in different reference frames which would introduce a number of
confounding relativistic effects. These effects will all be ignored. The
camera will be treated as if it is exactly centred on the player in its
synthetic view.

## Rigidity and sprites
As a 2D game the most common way of rendering characters would be 2D raster
sprites. Relativistic effects could be applied by distorting the sprite.
This could work but would involve many interconnected systems each
approximating different effects within special relativity. I would prefer
a system where the relativistic effects arise naturally from the geometry.
It would involve its own complications and would likely be more computationally
intensive, but I could focus on a more straight forward implementation of
the geometry instead of approximating it with multiple different interconnected
system each prone to different errors and bugs.

The most accurate system would be to represent the full 3+1 geometry of
the object in the worldline, but how is this geometry calculated. It
can not be a simple rigid object as demonstrated by Ehrenfest's paradox.
The geometry could be computed by treating points in the object as coupled
points in some relativistic simulation so it will respond to strain
induced by changes in acceleration, but this would be overly complicated
and intensive. Any system of this sort using the full geometry requires 
tracking the independent transformation of each point of the object along
the effective worldline. Instead I will fake a nearly ridged object and
simplify the calculations by recording the geometry in two steps.

I will assume that the total geometry of the object is well approximated
by the worldline of its centre of mass. Then the geometry of the object
will be recorded in its rest frame as a series of points (defining triangles,
quads, etc) defined relative to its centre of mass. At the same time the
object records the worldline of its centre of mass as a 1D path in 2+1
dimensional space time while simultaneously recording other information
for each point along the path such as its orientation, changes in color
etc. When rendering the camera will be located at some spacetime point
with a predefined reference frame. The object would show up at the point
where its worldline intersects with the past light cone of the camera.
This point can be found in the reference frame of the system, so no transforms
will be necessary. Once this spacetime point is found, transform into
the reference frame of the object and place the geometry of the object at
that point and extrude it in both directions along the local time axis.
This creates the geometry of the object in its rest frame. Now take this
geometry and transform into the reference frame of the camera. For each
line of the mesh its intersections with the past light cone of the camera
is found. Unlike with the worldline which is nonlinear, this is a simple
linear equation and can be found directly. These space time coordinate
for each point in the object are then projected onto the xy plane of the
camera. The distance to these projected points is equal to the proper
distance between the camera and these points if the camera was traced back
until the camera and point where at equal time in the camera's frame.
Note that this ignores stress, vibrations and dynamics that would necessarily
exist due to changes in linear and rotational motion. This system would
render vector "sprites" with relativistic effects naturally included where
motion is always rendered as if it is constant.

# Issues
## Lag
As stated, these relativistic effects are essentially a builtin lag, so
by design the experience would have high lag. It is reasonable to expect
that this would be a terrible experience.

## Lag Isolation
To fully take advantage of this natural buffer each client should have
a buffer of the other players actions which would make it very susceptible
to cheating, as cheating players could in effect see the future. If the
buffers where only maintained by the server, then there would still be
some susceptibility to minor lag spikes ... but the server's records of
players should be relatively smooth. So if one player had a lag spike I
would expect that their view of the other players would be laggie, but
the players with a good connection to the server would be unaffected,
including their view of the player that is lagging.

## Fairness
Lets assume two players had lasers. If the player A shot a laser, for it
to render appropriately the lasers should shoot out at the speed of light
some part of it hits the ground and travels back for it to be rendered.
This would continue for further and further points each time it needs to
travel twice the distance it actually went for it to be observed by the
player that shot it. So the location of the laser would appear to move
at half of the speed of light. you would see your laser bolt appear to
move at half speed.

Now if a different player shots a laser at the player in question, as
before the laser shots out some distance, some portion reflects on the
ground to the player. However, this time the laser and the reflected
portion making it visible are both moving in the same direction at the
same speed and so will hit the player at the same time.

So any laser shot out by the player will appear to move at half the speed
of light, while any incoming shots will be invisible until they hit, 
appearing to travel instantaneously and any shots that are not directly
inward or outward moving will show up as apparently moving at some
intermediate speed between c/2 and infinity. Further for a missed shot the
speed will not be constant as the relative angle to the bolt changes, it
will start moving a high speed when it is pointed almost directly at the
player. It will slow down to c as it gets to the closest approach being
perpendicular to the player, and then asymptotically approach c/2 as it
gets further away.

While in truth this is fair since everyone is subject to the same rules,
to any player it would look like only their shots are being handicapped
by a slow travel time.
