#pragma once

#include <memory>

namespace drone_system {

// Forward declarations
class IDrone;
class ICommand;
class ITask;
class IFlightPlan;

class IDrone {
public:
    virtual ~IDrone() = default;
    virtual void execute_command(const ICommand& command) = 0;
};

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute(IDrone& drone) const = 0;
};

class ITask {
public:
    virtual ~ITask() = default;
    virtual void execute(IDrone& drone) = 0;
};

class IFlightPlan {
public:
    virtual ~IFlightPlan() = default;
    virtual void add_task(std::unique_ptr<ITask> task) = 0;
    virtual void execute(IDrone& drone) = 0;
};

} // namespace drone_system