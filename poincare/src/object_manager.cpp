#include "object_manager.hpp"

#include <limits>

#include "massive_object.hpp"

namespace poincare {

ObjectManager* ObjectManager::instance = nullptr;

ObjectManager* ObjectManager::GetInstance() {
    if (instance == nullptr) {
        instance = new ObjectManager();
    }
    return instance;
}

void ObjectManager::UpdateObjects(double dtau) {
    int num_objects = massive_object_list.size();
    for (int i=0; i < num_objects; i++) {
        double t_past = -std::numeric_limits<double>::infinity();
        double t_future = std::numeric_limits<double>::infinity();

        for (int j=0; j < num_objects; j++) {
            if (i == j) {
                continue;
            }

            double past, future;
            minkowski::Point position_j = massive_object_list[j]->position;
            massive_object_list[i]->world_line.GetIntersectionEstimates(position_j, past, future);

            if (past > t_past) {
                t_past = past;
            }
            if (future < t_future) {
                t_future = future;
            }
        }
        massive_object_list[i]->ManageWorldLineBuffer(dtau, t_past, t_future);
    }

    for (std::shared_ptr<MassiveObject> &object : massive_object_list) {
        object->UpdateObject(dtau);
    }
}

ObjectManager::ObjectManager() {
}

} // namespace poincare
