#pragma once

namespace drone_system {

class Battery {
public:
    Battery(double capacity) : capacity_(capacity), remaining_power_(capacity) {}

    [[nodiscard]] double capacity() const { return capacity_; }
    [[nodiscard]] double remaining_power() const { return remaining_power_; }
    void recharge() { remaining_power_ = capacity_; }

private:
    double capacity_;
    double remaining_power_;
};

} // namespace drone_system