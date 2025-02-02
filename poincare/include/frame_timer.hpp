#ifndef FRAME_TIMER_HPP
#define FRAME_TIMER_HPP

namespace poincare {

class UpdateLogger;

/// An interface for timing the render loop. One of the implementations
/// of `FrameTimer` should be used to calculate time steps in the render
/// loop as well as report the current frame rate and other statistics.
/// In the render loop `timer()` should only be called once to get the
/// to get the current timestep `dt`.
class FrameTimer {
// Call timer() once in the render loop preferably at the beginning or end.
public:
    virtual ~FrameTimer() = default;
    /// Calculates the current time step and adds the frame rate to the
    /// `LoopLog` buffer.
    /// @return Time since the previous invocation of `timer()`.
    virtual double Timer() = 0;
    /// @return The time since the GLFW window was created.
    virtual double GetTime() const = 0;
};

/// This implementation of `FrameTimer` computes the times step and adds
/// only the frame rate to the `LoopLog` buffer.
class BasicTimer : public FrameTimer {
public:
    BasicTimer();
    double Timer() override;
    double GetTime() const override;
private:
    double time, previous_time, previous_update;
    unsigned int frame_count;
    UpdateLogger* logger;
};

/// This implementation of `FrameTimer` computes the times step and adds
/// the frame rate as well as some statistics about the time step to the
/// `LoopLog` buffer.
class AdvancedTimer : public FrameTimer {
public:
    AdvancedTimer();
    double Timer() override;
    double GetTime() const override;
private:
    double time, previous_time, previous_update;
    double min_dt, max_dt, mean_dt, previous_mean_dt;
    double current_M2, previous_M2;

    unsigned int frame_count;
    UpdateLogger* logger;

    /// Reset parameters used to compute Welford's online algorithm
    /// for the variance.
    void ResetWelford();
};

} // namespace poincare

#endif
