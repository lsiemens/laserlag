#include "sprite.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "window_manager.hpp"

static const int kPositionSize = 2;
static const int kColorSize = 3;
static constexpr int kVertexSize = kPositionSize + kColorSize;

namespace poincare {

Sprite::Sprite(std::string vector_sprite_path) : vertex_buffer_id(0), element_buffer_id(0), vector_sprite_path(vector_sprite_path) {
    LoadSprite();
}

void Sprite::DrawSprite() {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);

    // Setup vertex position array
    glVertexAttribPointer(0, kPositionSize, GL_FLOAT, GL_FALSE, kVertexSize*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup vertex color array
    glVertexAttribPointer(1, kColorSize, GL_FLOAT, GL_FALSE, kVertexSize*sizeof(GLfloat), (void*)(kPositionSize*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}

void Sprite::LoadSprite() {
    WindowManager* window_manager = WindowManager::GetInstance();
    if (!window_manager->HasContext()) {
        std::cerr << "No OpenGL context found by WindowManager\n";
        throw std::runtime_error("Could not configure sprite.\n");
    }

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    LoadData(vertices, indices);
    num_indices = indices.size();

    // Load VBO
    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, (kVertexSize*sizeof(GLfloat))*num_vertices, &vertices[0], GL_STATIC_DRAW);

    // Load EBO
    glGenBuffers(1, &element_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, element_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint)*num_indices, &indices[0], GL_STATIC_DRAW);
    //glGenBuffers(1, &element_buffer_id);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*num_indices, &indices[0], GL_STATIC_DRAW);

    // Unbind Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::LoadData(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices) {
    std::ifstream file_data(vector_sprite_path, std::ios::in);
    if (file_data.is_open()) {
        std::string signature = ReadLine(file_data);
        if (signature != "VSPRITE") {
            std::cerr << "Failed to load. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
            throw std::runtime_error("Could not load non vsprite file.");
        }
        // Read vsprite meta data and data
        int num_triangles;
        ReadHeader(file_data, num_vertices, num_triangles);
        vertices = ReadVertices(file_data, num_vertices);
        indices = ReadTriangles(file_data, num_triangles);

        file_data.close();
    } else {
        std::cerr << "Failed to open '" << vector_sprite_path << "'.\n";
        throw std::runtime_error("Could not load vector sprite file.");
    }
}

void Sprite::ReadHeader(std::ifstream &file_data, int &num_vertices, int &num_triangles) {
    std::string header_signature = ReadLine(file_data);
    if (header_signature != "META DATA") {
        std::cerr << "Could not find meta data. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
        throw std::runtime_error("Could not load vsprite file.");
    }

    std::vector<int> values;
    ParseString(file_data, values);
    if (values.size() < 2) {
        std::cerr << "Could not parse header. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
        throw std::runtime_error("Could not load vsprite file.");
    } else if (values.size() > 2) {
        std::clog << "Warning expected 2 integers in header, found " << values.size() << ". The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
    }

    if ((values[0] < 0) || (values[1] < 0)) {
        std::cerr << "Invalid values in header. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
        throw std::runtime_error("Could not load vsprite file.");
    }
    num_vertices = values[0];
    num_triangles = values[1];
}

std::vector<GLfloat> Sprite::ReadVertices(std::ifstream &file_data, int num_vertices) {
    std::string vertices_signature = ReadLine(file_data);
    if (vertices_signature != "VERTEX DATA") {
        std::cerr << "Could not find vertex data. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
        throw std::runtime_error("Could not load vsprite file.");
    }

    std::vector<GLfloat> vertices;
    for (int i=0; i<num_vertices; i++) {
        std::vector<GLfloat> values;
        ParseString(file_data, values);
        if (values.size() < kVertexSize) {
            std::cerr << "Could not parse vertex. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
            throw std::runtime_error("Could not load vsprite file.");
        } else if (values.size() > kVertexSize) {
            std::clog << "Warning expected " << kVertexSize << " floats for vertex, found " << values.size() << ". The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
        }
        vertices.insert(vertices.end(), values.begin(), values.begin() + kVertexSize);
    }
    return vertices;
}

std::vector<GLuint> Sprite::ReadTriangles(std::ifstream &file_data, int num_triangles) {
    std::string triangles_signature = ReadLine(file_data);
    if (triangles_signature != "TRIANGLE DATA") {
        std::cerr << "Could not find triangle data. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
        throw std::runtime_error("Could not load vsprite file.");
    }

    std::vector<GLuint> triangles;
    for (int i=0; i<num_triangles; i++) {
        std::vector<int> values;
        ParseString(file_data, values);
        if (values.size() < 3) {
            std::cerr << "Could not parse triangle. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
            throw std::runtime_error("Could not load vsprite file.");
        } else if (values.size() > 3) {
            std::clog << "Warning expected 3 ints for triangle, found " << values.size() << ". The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
        }

        if ((values[0] < 0) || (values[1] < 0) || (values[2] < 0)) {
            std::cerr << "Invalid vertex index. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
            throw std::runtime_error("Could not load vsprite file.");
        }
        triangles.insert(triangles.end(), values.begin(), values.begin() + 3);
    }
    return triangles;
}

std::string Sprite::ReadLine(std::ifstream &file_data) {
    for (std::string next_line; std::getline(file_data, next_line);) {
        int index = next_line.find('#');
        next_line = next_line.substr(0, index);
        if (next_line == "") {
            continue;
        }

        index = next_line.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-.");
        if (index == -1) {
            continue;
        }
        return next_line;
    }
    return "";
}

void Sprite::ParseString(std::ifstream &file_data, std::vector<int> &values) {
    std::istringstream line_stream(ReadLine(file_data));
    std::string token;
    while (line_stream >> token) {
        int value;
        std::istringstream token_stream(token);
        if (token_stream >> value) {
            values.push_back(value);
        } else {
            std::cerr << "Could not parse line as integers. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
            values.clear();
            throw std::runtime_error("Could not load vsprite file.");
        }
    }
}

void Sprite::ParseString(std::ifstream &file_data, std::vector<float> &values) {
    std::istringstream line_stream(ReadLine(file_data));
    std::string token;
    while (line_stream >> token) {
        float value;
        std::istringstream token_stream(token);
        if (token_stream >> value) {
            values.push_back(value);
        } else {
            std::cerr << "Could not parse line as floats. The vsprite file at '" << vector_sprite_path << "' could be corrupted.\n";
            values.clear();
            throw std::runtime_error("Could not load vsprite file.");
        }
    }
}

} // namespace poincare
