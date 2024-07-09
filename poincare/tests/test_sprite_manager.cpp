#include <gtest/gtest.h>
#include <string>
#include <fstream>

#include "sprite_manager.hpp"
#include "sprite.hpp"
#include "window_manager.hpp"

namespace {

std::string vsprite_data = "VSPRITE\nMETA DATA\n4 2\nVERTEX DATA\n-0.5 -0.5 1 1 1\n-0.5 0.5 1 0 1\n0.5 -0.5 0 1 1\n0.5 0.5 0 0 1\nTRIANGLE DATA\n1 2 3\n1 2 4\n";

TEST(SpriteManagerTest, initialize) {
    std::string vsprite_path = "vsprite.dat";

    std::ofstream vsprite_file(vsprite_path, std::ios::out);
    if (vsprite_file.is_open()) {
        vsprite_file << vsprite_data;
        vsprite_file.close();
    } else {
        FAIL() << "Failed to write example vsprite file.";
    }

    poincare::WindowManager* window_manager = poincare::WindowManager::GetInstance();
    window_manager->OpenWindow(600, 600, "Sprite Manager Test");

    poincare::SpriteManager* sprite_manager = poincare::SpriteManager::GetInstance();
    std::shared_ptr<poincare::Sprite> test_sprite = sprite_manager->GetSprite(vsprite_path);
    std::shared_ptr<poincare::Sprite> test_sprite2 = sprite_manager->GetSprite(vsprite_path);

    EXPECT_NE(test_sprite->vertex_buffer_id, 0);
    EXPECT_NE(test_sprite->element_buffer_id, 0);
    EXPECT_EQ(test_sprite->vector_sprite_path, vsprite_path);

    EXPECT_EQ(test_sprite.use_count(), 3);
    EXPECT_EQ(test_sprite.get(), test_sprite2.get());
}

TEST(SpriteManagerTest, no_throw_on_draw) {
    std::string vsprite_path = "vsprite.dat";

    std::ofstream vsprite_file(vsprite_path, std::ios::out);
    if (vsprite_file.is_open()) {
        vsprite_file << vsprite_data;
        vsprite_file.close();
    } else {
        FAIL() << "Failed to write example vsprite file.";
    }

    poincare::WindowManager* window_manager = poincare::WindowManager::GetInstance();
    window_manager->OpenWindow(600, 600, "Sprite Manager Test");

    poincare::SpriteManager* sprite_manager = poincare::SpriteManager::GetInstance();
    std::shared_ptr<poincare::Sprite> test_sprite = sprite_manager->GetSprite(vsprite_path);

    EXPECT_NO_THROW(test_sprite->DrawSprite());
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
