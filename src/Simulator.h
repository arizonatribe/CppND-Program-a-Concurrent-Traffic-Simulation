#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Intersection.h"
#include "Street.h"
#include "TrafficObject.h"
#include "Vehicle.h"
#include <memory>
#include <string>
#include <vector>

enum Cities {
    paris,
    nyc
};

class Simulator {
  public:
    Simulator(Cities city, int vehicleCount);

    void simulate();

  private:
    std::string backgroundImg;
    std::vector<std::shared_ptr<TrafficObject>> trafficObjects;

    void setupParis(
      std::vector<std::shared_ptr<Street>> &streets,
      std::vector<std::shared_ptr<Intersection>> &intersections,
      std::vector<std::shared_ptr<Vehicle>> &vehicles,
      int nVehicles
    );

    void setupNYC(
      std::vector<std::shared_ptr<Street>> &streets,
      std::vector<std::shared_ptr<Intersection>> &intersections,
      std::vector<std::shared_ptr<Vehicle>> &vehicles,
      int nVehicles
    );
};

#endif
