#include "drone.hpp"
#include "flight_plan.hpp"
#include "task.hpp"
#include "drone_service.hpp"
#include "factories.hpp"
#include <iostream>

using namespace drone_system;

int main() {
    // Create a drone
    auto drone = DroneFactory::create_drone("Drone1", DroneStatus::IDLE, Location{0, 0, 0});

    // Create a flight plan
    auto flight_plan = std::make_unique<FlightPlan>("TestFlightPlan");

    // Add tasks to the flight plan
    flight_plan->add_task(std::make_unique<TakeoffAndHoverTask>());

    flight_plan->add_task(std::make_unique<SurveyAreaTask>(
        Location{1.0, 1.0, 10.0},
        Location{2.0, 2.0, 10.0}
    ));

    flight_plan->add_task(std::make_unique<SensorReadingTask>(
        Location{1.5, 1.5, 15.0},
        SensorType::LIDAR
    ));

    flight_plan->add_task(std::make_unique<SensorReadingTask>(
        Location{1.8, 1.8, 15.0},
        SensorType::CAMERA
    ));

    flight_plan->add_task(std::make_unique<LandingTask>(Location{0, 0, 0}));

    // Create a drone service
    DroneService drone_service;

    // Execute the flight plan
    std::cout << "Executing flight plan...\n" << std::endl;
    drone_service.schedule_flight(*drone, *flight_plan);

    std::cout << "\nFlight plan execution completed." << std::endl;

    return 0;
}