#include <gtest/gtest.h>
#include <string>
#include <fstream>

#include "window.hpp"
#include "sprite.hpp"

namespace {

// Example file with comments and odd white space in places
std::string vsprite_data = "VSPRITE\n#Comment\n\n  		  # Test with blank space\nMETA DATA\n4 2\nVERTEX DATA\n  -0.5 -0.5 1 1 1\n		-0.5 0.5 1 0 1\n0.5 -0.5 0 1 1\n0.5 0.5 0 0 1 # Inline comment\nTRIANGLE DATA\n1 2 3\n  1 2 4\n";

TEST(SpriteTest, initialize) {
    std::string vsprite_path = "vsprite.dat";

    std::ofstream vsprite_file(vsprite_path, std::ios::out);
    if (vsprite_file.is_open()) {
        vsprite_file << vsprite_data;
        vsprite_file.close();
    } else {
        FAIL() << "Failed to write example vsprite file.";
    }

    poincare::Window window(600, 600, "Sprite Test");
    poincare::Sprite test_sprite(vsprite_path);

    EXPECT_NE(test_sprite.vertex_buffer_id, 0);
    EXPECT_NE(test_sprite.element_buffer_id, 0);
    EXPECT_EQ(test_sprite.vector_sprite_path, vsprite_path);
}

TEST(SpriteTest, no_throw_on_draw) {
    std::string vsprite_path = "vsprite.dat";

    std::ofstream vsprite_file(vsprite_path, std::ios::out);
    if (vsprite_file.is_open()) {
        vsprite_file << vsprite_data;
        vsprite_file.close();
    } else {
        FAIL() << "Failed to write example vsprite file.";
    }

    poincare::Window window(600, 600, "Sprite Test");
    poincare::Sprite test_sprite(vsprite_path);

    EXPECT_NO_THROW(test_sprite.DrawSprite());
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
