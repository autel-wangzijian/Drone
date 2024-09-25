#pragma once

#include "interfaces.hpp"
#include "commands.hpp"
#include "location.hpp"
#include "sensor.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>

namespace drone_system {

class Task : public ITask {
public:
    explicit Task(std::string id) : id_(std::move(id)) {}

    void execute(IDrone& drone) override {
        std::cout << "Executing task: " << id_ << std::endl;
        for (const auto& command : commands_) {
            command->execute(drone);
        }
    }

    void add_command(std::unique_ptr<ICommand> command) {
        commands_.push_back(std::move(command));
    }

    [[nodiscard]] const std::string& id() const { return id_; }

private:
    std::string id_;
    std::vector<std::unique_ptr<ICommand>> commands_;
};

// Add this new class for sensor reading command
class SensorReadingCommand : public ICommand {
public:
    SensorReadingCommand(SensorType sensor_type)
        : sensor_type_(sensor_type) {}

    void execute(IDrone& drone) const override {
        std::cout << "Reading data from " << static_cast<int>(sensor_type_) << " sensor" << std::endl;
        auto sensor = create_sensor("Sensor_" + std::to_string(static_cast<int>(sensor_type_)), sensor_type_);
        sensor->read_data();
    }

private:
    SensorType sensor_type_;
};

// Fake flight tasks

class TakeoffAndHoverTask : public Task {
public:
    TakeoffAndHoverTask() : Task("TakeoffAndHover") {
        add_command(std::make_unique<TakeOffCommand>());
        add_command(std::make_unique<HoverCommand>());
    }
};

class SurveyAreaTask : public Task {
public:
    SurveyAreaTask(const Location& start, const Location& end) : Task("SurveyArea") {
        add_command(std::make_unique<MoveToCommand>(start));
        add_command(std::make_unique<HoverCommand>());
        add_command(std::make_unique<MoveToCommand>(end));
        add_command(std::make_unique<HoverCommand>());
    }
};

class LandingTask : public Task {
public:
    explicit LandingTask(const Location& landing_location) : Task("Landing") {
        add_command(std::make_unique<MoveToCommand>(landing_location));
        add_command(std::make_unique<LandCommand>());
    }
};

class SensorReadingTask : public Task {
public:
    SensorReadingTask(const Location& reading_location, SensorType sensor_type)
        : Task("SensorReading_" + std::to_string(static_cast<int>(sensor_type))) {
        add_command(std::make_unique<MoveToCommand>(reading_location));
        add_command(std::make_unique<HoverCommand>());
        add_command(std::make_unique<SensorReadingCommand>(sensor_type));
    }
};

} // namespace drone_system