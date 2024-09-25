#pragma once

#include "enums.hpp"
#include <string>
#include <random>
#include <iostream>

namespace drone_system {

class Sensor {
public:
    Sensor(std::string id, SensorType type) : id_(std::move(id)), sensor_type_(type) {}
    virtual ~Sensor() = default;

    [[nodiscard]] const std::string& id() const { return id_; }
    [[nodiscard]] SensorType sensor_type() const { return sensor_type_; }
    virtual void read_data() = 0;

protected:
    std::string id_;
    SensorType sensor_type_;
};

class GPSSensor : public Sensor {
public:
    GPSSensor(const std::string& id) : Sensor(id, SensorType::GPS) {}

    void read_data() override {
        // Simulate GPS reading
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> lat_dis(-90.0, 90.0);
        std::uniform_real_distribution<> lon_dis(-180.0, 180.0);

        double latitude = lat_dis(gen);
        double longitude = lon_dis(gen);

        std::cout << "GPS Sensor " << id_ << " reading: Lat " << latitude << ", Lon " << longitude << std::endl;
    }
};

class CameraSensor : public Sensor {
public:
    CameraSensor(const std::string& id) : Sensor(id, SensorType::CAMERA) {}

    void read_data() override {
        // Simulate camera capture
        std::cout << "Camera Sensor " << id_ << " capturing image..." << std::endl;
        std::cout << "Image captured and stored." << std::endl;
    }
};

class LidarSensor : public Sensor {
public:
    LidarSensor(const std::string& id) : Sensor(id, SensorType::LIDAR) {}

    void read_data() override {
        // Simulate LIDAR scanning
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 100.0);

        double distance = dis(gen);

        std::cout << "LIDAR Sensor " << id_ << " reading: Distance " << distance << " meters" << std::endl;
    }
};

// Factory function to create sensors
std::unique_ptr<Sensor> create_sensor(const std::string& id, SensorType type) {
    switch (type) {
        case SensorType::GPS:
            return std::make_unique<GPSSensor>(id);
        case SensorType::CAMERA:
            return std::make_unique<CameraSensor>(id);
        case SensorType::LIDAR:
            return std::make_unique<LidarSensor>(id);
        default:
            throw std::invalid_argument("Unknown sensor type");
    }
}

} // namespace drone_system