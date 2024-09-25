#pragma once

namespace drone_system {

enum class DroneStatus {
    IDLE,
    IN_FLIGHT,
    LANDING,
    CHARGING
};

enum class SensorType {
    GPS,
    CAMERA,
    LIDAR
};

} // namespace drone_system