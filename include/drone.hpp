#pragma once

#include "interfaces.hpp"
#include "enums.hpp"
#include "location.hpp"
#include "battery.hpp"
#include "sensor.hpp"
#include <string>
#include <vector>
#include <memory>

namespace drone_system {

class Drone : public IDrone {
public:
    Drone(std::string id, DroneStatus status, Location location)
        : id_(std::move(id)), status_(status), current_location_(location) {}

    void execute_command(const ICommand& command) override {
        command.execute(*this);
    }

    // Getters and setters
    [[nodiscard]] const std::string& id() const { return id_; }
    [[nodiscard]] DroneStatus status() const { return status_; }
    void set_status(DroneStatus status) { status_ = status; }
    [[nodiscard]] const Location& current_location() const { return current_location_; }
    void set_current_location(const Location& location) { current_location_ = location; }

private:
    std::string id_;
    DroneStatus status_;
    Location current_location_;
    std::unique_ptr<Battery> battery_;
    std::vector<std::unique_ptr<Sensor>> sensors_;
};

} // namespace drone_system