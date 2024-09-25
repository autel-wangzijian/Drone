#pragma once

#include "interfaces.hpp"
#include <string>
#include <vector>
#include <memory>

namespace drone_system {

class FlightPlan : public IFlightPlan {
public:
    explicit FlightPlan(std::string id) : id_(std::move(id)) {}

    void add_task(std::unique_ptr<ITask> task) override {
        tasks_.push_back(std::move(task));
    }

    void execute(IDrone& drone) override {
        for (const auto& task : tasks_) {
            task->execute(drone);
        }
    }

private:
    std::string id_;
    std::vector<std::unique_ptr<ITask>> tasks_;
};

} // namespace drone_system