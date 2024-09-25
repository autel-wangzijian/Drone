#pragma once

#include "interfaces.hpp"

namespace drone_system {

class DroneService {
public:
    void schedule_flight(IDrone& drone, IFlightPlan& flight_plan) {
        flight_plan.execute(drone);
    }

    void execute_command(IDrone& drone, const ICommand& command) {
        drone.execute_command(command);
    }
};

} // namespace drone_system