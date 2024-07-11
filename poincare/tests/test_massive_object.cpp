#include <gtest/gtest.h>
#include <string>
#include <fstream>

#include "massive_object.hpp"
#include "minkowski.hpp"
#include "window_manager.hpp"

namespace {

std::string vsprite_data = "VSPRITE\nMETA DATA\n4 2\nVERTEX DATA\n-0.5 -0.5 1 1 1\n-0.5 0.5 1 0 1\n0.5 -0.5 0 1 1\n0.5 0.5 0 0 1\nTRIANGLE DATA\n1 2 3\n1 2 4\n";

TEST(MassiveObjectTest, initialize) {
    std::string vsprite_path = "vsprite.dat";

    std::ofstream vsprite_file(vsprite_path, std::ios::out);
    if (vsprite_file.is_open()) {
        vsprite_file << vsprite_data;
        vsprite_file.close();
    } else {
        FAIL() << "Failed to write example vsprite file.";
    }

    poincare::WindowManager* window_manager = poincare::WindowManager::GetInstance();
    window_manager->OpenWindow(600, 600, "Massive Object Test");

    minkowski::Point pos(0, 0, 0);
    minkowski::Vector vec(1.2, 0, 1);

    poincare::MassiveObject obj(pos, vec, "vsprite.dat");
    obj.UpdateObject(1.23);

    EXPECT_EQ(obj.proper_time, 1.23);
    EXPECT_EQ(obj.position, minkowski::Point(1.2*1.23, 0, 1.23));
    obj.UpdateObject(1.23);

    EXPECT_EQ(obj.proper_time, 2*1.23);
    EXPECT_EQ(obj.position, minkowski::Point(2*1.2*1.23, 0, 2*1.23));
}

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
