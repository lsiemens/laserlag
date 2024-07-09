#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>
#include <vector>
#include <fstream>
// keep this before all other OpenGL libraries
#define GLEW_STATIC
#include <GL/glew.h>

namespace poincare {

/// The class Sprite loads a custom 2D sprite file format called vsprite.
/// This format defines vector graphic sprites. Each file contains one
/// sprite described in two parts. First, the vertices in the sprite are
/// defined along with the color at that point. Second, the triangles that
/// form the sprite itself are defined by referencing the vertices by their
/// indices. Lines may contain strings or numerical values separated by
/// spaces.
///
/// The first line of the file must be "VSPRITE" after this line any empty
/// lines are ignored. The character # comments out the remainder of the
/// line.
///
/// The header starts with the line "META DATA" and contains two integers
/// on the next line. In order, the integers are the number of vertices
/// and the number of triangles.
///
/// The next section must start with the line "VERTEX DATA". In this section
/// there should be lines containing 5 float values and consist of one
/// line for each vertex specified in the header. the values in each line
/// are two floats to define the x and y position and three floats for
/// the color at that point.
///
/// The next section must start with the line "TRIANGLE DATA". In this
/// section there should be lines containing 3 int values and consist of
/// one line for each triangle specified in the header. the values in each
/// line are three ints, the indices of the vertices in the vertex data,
/// which make up the triangle.
class Sprite {
public:
    GLuint vertex_buffer_id;
    GLuint element_buffer_id;
    std::string vector_sprite_path;

    Sprite(std::string vector_sprite_path);

    void DrawSprite();
private:
    int num_vertices;
    int num_indices;

    void LoadSprite();
    void LoadData(std::vector<GLfloat> &vertices, std::vector<GLuint> &indeces);
    void ReadHeader(std::ifstream &file_data, int &num_vertices, int &num_triangles);
    std::vector<GLfloat> ReadVertices(std::ifstream &file_data, int num_vertices);
    std::vector<GLuint> ReadTriangles(std::ifstream &file_data, int num_triangles);
    std::string ReadLine(std::ifstream &file_data);

    void ParseString(std::ifstream &file_data, std::vector<int> &values);
    void ParseString(std::ifstream &file_data, std::vector<float> &values);
};

} // namespace poincare

#endif
