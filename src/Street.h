#ifndef STREET_H
#define STREET_H

#include "TrafficObject.h"
#include <memory>

// forward declaration to avoid include cycle
class Intersection;

class Street : public TrafficObject, public std::enable_shared_from_this<Street> {
  public:
    Street();

    double getLength() {
      return _length;
    }
    std::shared_ptr<Intersection> getInIntersection() {
      return _interIn;
    }
    std::shared_ptr<Intersection> getOutIntersection() {
      return _interOut;
    }
    std::shared_ptr<Street> get_shared_this() {
      return shared_from_this();
    }

    void setInIntersection(std::shared_ptr<Intersection> in);
    void setOutIntersection(std::shared_ptr<Intersection> out);

  private:
    double _length; // in m

    // intersections from which a vehicle can enter
    // (one-way streets is always from 'in' to 'out')
    std::shared_ptr<Intersection> _interIn, _interOut;
};

#endif