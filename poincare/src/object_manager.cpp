#include "object_manager.hpp"

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
    for (std::shared_ptr<MassiveObject> &object : massive_object_list) {
        object->UpdateObject(dtau);
    }
}

ObjectManager::ObjectManager() {
}

} // namespace poincare
