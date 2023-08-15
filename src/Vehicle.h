#ifndef VEHICLE_H
#define VEHICLE_H

#include <memory>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Street;
class Intersection;

class Vehicle : public TrafficObject, public std::enable_shared_from_this<Vehicle> {
  public:
    Vehicle();

    void setCurrentDestination(std::shared_ptr<Intersection> destination);
    void setCurrentStreet(std::shared_ptr<Street> street) {
      _currStreet = street;
    };

    void simulate();

    std::shared_ptr<Vehicle> get_shared_this() {
      return shared_from_this();
    }

  private:
    void drive();

    std::shared_ptr<Street> _currStreet;
    std::shared_ptr<Intersection> _currDestination;
    double _posStreet;
    double _speed;  // ego speed in m/s
};

#endif