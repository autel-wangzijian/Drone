#pragma once

#include "interfaces.hpp"
#include "drone.hpp"
#include "flight_plan.hpp"
#include "enums.hpp"
#include "location.hpp"
#include <string>
#include <vector>
#include <memory>

namespace drone_system {

class DroneFactory {
public:
    static std::unique_ptr<IDrone> create_drone(const std::string& id, DroneStatus status, const Location& location) {
        return std::make_unique<Drone>(id, status, location);
    }
};

class FlightPlanFactory {
public:
    static std::unique_ptr<IFlightPlan> create_flight_plan(const std::string& id, std::vector<std::unique_ptr<ITask>> tasks) {
        auto flight_plan = std::make_unique<FlightPlan>(id);
        for (auto& task : tasks) {
            flight_plan->add_task(std::move(task));
        }
        return flight_plan;
    }
};

} // namespace drone_system