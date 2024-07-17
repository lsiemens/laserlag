#ifndef MINKOWSKI_HPP
#define MINKOWSKI_HPP

#include <vector>
#include <glm/glm.hpp>

namespace minkowski {

class Point;
class Vector;
class WorldLine;

class Point {
public:
    Point();
    Point(double t, double x, double y);

    bool operator==(Point const& other) const;
    Vector operator-(Point const& other) const;
    Point operator+(Vector const& other) const;

    friend class Vector;
    friend class WorldLine;

    /// Convert to glm 3D vector where (t, x, y) maps to (x, y, z) with
    /// t going to z.
    glm::vec3 ToGLM();
private:
    double coordinates[3];
};

class Vector {
public:
    Vector();
    Vector(double t, double x, double y);

    bool operator==(Vector const& other) const;
    double operator*(Vector const& other) const;
    friend Vector operator*(double scalar, Vector const& self);
    Vector operator+(Vector const& other) const;
    Vector operator-(Vector const& other) const;

    friend class Point;
    friend class WorldLine;

    /// Convert to glm 3D vector where (t, x, y) maps to (x, y, z) with
    /// t going to z.
    glm::vec3 ToGLM();
private:
    double components[3];
};

/// WorldLine record the world line of a particle in space time. In stead
/// of simply recording the position, WorldLine contains the path of the
/// particle on the tangent manifold, that is the position and velocity
/// of the particle is recored for each point. WorldLine will have two
/// primary tasks that can be applied to its data. First, calculate
/// intersection points with light cones. The result of this calculation
/// will be used in rendering objects. Second, prepair the world line data
/// for rendering of the world line as a whole. This will involve resampling
/// the data and converting to a convienient format for OpenGL.
class WorldLine {
public:
    std::vector<double> path;

    WorldLine();

    void AddPoint(Point position, Vector velocity);
    int size() const;
    Point GetPosition(int index);
    Vector GetVelocity(int index);

    void GetLightConeIntersection(Point cone_position, Point &intersection_position, Vector &intersection_velocity);
    std::vector<float> Resample(double target_period, int max_size);
private:
};

} // namespace minkowski

#endif
