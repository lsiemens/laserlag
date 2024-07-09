#ifndef UPDATE_LOGGER_HPP
#define UPDATE_LOGGER_HPP

#include <sstream>

namespace poincare {

/// A class for convenient logging in a render loop.
/// Text added to `instance.log` during the render loop will be printed
/// to the standard output device when `instance.flush()` is called. The
/// intention is that any functions called during the render loop can
/// log info in a live update instead of a stream of text flowing by.
/// UpdateLogger should only be flushed once per render iteration.
class UpdateLogger {
public:
    std::stringstream log;

    /// Gets and instance of the UpdateLogger singleton.
    /// @return Pointer to an instance of LoogLoop.
    static UpdateLogger* GetInstance();

    /// Writes the log buffer to the standard output. This function should
    /// only be called once in the render loop.
    void Flush();
private:
    static UpdateLogger* instance;

    UpdateLogger();

    /// Returns the cursor to where it was before the buffer was flushed
    /// to the standard output.
    void ResetCursor();

    UpdateLogger(const UpdateLogger&) = delete;
    UpdateLogger& operator=(const UpdateLogger&) = delete;
};

} // namespace poincare

#endif
