#pragma once

#include "interfaces.hpp"
#include "location.hpp"
#include "drone.hpp"
#include <iostream>

namespace drone_system {

class TakeOffCommand : public ICommand {
public:
    void execute(IDrone& drone) const override {
        auto* concrete_drone = dynamic_cast<Drone*>(&drone);
        if (concrete_drone) {
            concrete_drone->set_status(DroneStatus::IN_FLIGHT);
            std::cout << "Drone " << concrete_drone->id() << " is taking off." << std::endl;
        }
    }
};

class LandCommand : public ICommand {
public:
    void execute(IDrone& drone) const override {
        auto* concrete_drone = dynamic_cast<Drone*>(&drone);
        if (concrete_drone) {
            concrete_drone->set_status(DroneStatus::LANDING);
            std::cout << "Drone " << concrete_drone->id() << " is landing." << std::endl;
            // Simulate landing process
            concrete_drone->set_status(DroneStatus::IDLE);
            std::cout << "Drone " << concrete_drone->id() << " has landed." << std::endl;
        }
    }
};

class MoveToCommand : public ICommand {
public:
    explicit MoveToCommand(Location target_location) : target_location_(target_location) {}

    void execute(IDrone& drone) const override {
        auto* concrete_drone = dynamic_cast<Drone*>(&drone);
        if (concrete_drone) {
            std::cout << "Drone " << concrete_drone->id() << " is moving to location: "
                      << "(" << target_location_.latitude << ", "
                      << target_location_.longitude << ", "
                      << target_location_.altitude << ")" << std::endl;
            concrete_drone->set_current_location(target_location_);
            std::cout << "Drone " << concrete_drone->id() << " has reached the target location." << std::endl;
        }
    }

private:
    Location target_location_;
};

class HoverCommand : public ICommand {
public:
    void execute(IDrone& drone) const override {
        auto* concrete_drone = dynamic_cast<Drone*>(&drone);
        if (concrete_drone) {
            std::cout << "Drone " << concrete_drone->id() << " is hovering at its current location." << std::endl;
            // Simulate hovering for 5 seconds
            std::cout << "Hovering for 5 seconds..." << std::endl;
            // In a real implementation, you might use std::this_thread::sleep_for
            // but for this mock, we'll just print a message
            std::cout << "Drone " << concrete_drone->id() << " has finished hovering." << std::endl;
        }
    }
};

} // namespace drone_system