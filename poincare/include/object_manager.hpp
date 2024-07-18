#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include <memory>
#include <vector>

namespace poincare {

class MassiveObject;

class ObjectManager {
public:
    static ObjectManager* GetInstance();

    std::vector<std::shared_ptr<MassiveObject>> massive_object_list;
//    std::vector<MasslessObject> massless_object_list;
//    std::vector<MasiveObject> static_object_list;

    /// Trigger Update in all objects, once triggerd the objects will
    /// determine the how they respond, including the possibility of not
    /// updating.
    void UpdateObjects(double dtau);

private:
    static ObjectManager* instance;

    ObjectManager();

    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
};

} // namespace poincare

#endif
