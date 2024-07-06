#include "update_logger.hpp"

#include <iostream>

namespace poincare {

UpdateLogger* UpdateLogger::instance = nullptr;

UpdateLogger::UpdateLogger() {
}

/// Moves the cursor back to where it was prior to flushing the log.
void UpdateLogger::ResetCursor() {
    std::string buffer = log.str();
    for (char &c : buffer) {
        if (c == '\n') {
            std::cout << "\033[A";
        }
    }
}

UpdateLogger* UpdateLogger::GetInstance() {
    if (instance == nullptr) {
        instance = new UpdateLogger();
    }
    return instance;
}

void UpdateLogger::Flush(){
    std::string buffer = log.str();
    if (buffer != "") {
        std::cout << buffer;
        ResetCursor();
        std::cout.flush();
    }
    log.str("");
    log.clear();
}

} // namespace poincare
