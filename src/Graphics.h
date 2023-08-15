#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <memory>
#include <opencv2/core.hpp>
#include <vector>
#include "TrafficObject.h"

class Graphics {
  public:
    void setBgFilename(std::string filename) {
      _bgFilename = filename;
    }
    void setTrafficObjects(std::vector<std::shared_ptr<TrafficObject>> &trafficObjects) {
      _trafficObjects = trafficObjects;
    };

    void simulate();

  private:
    void loadBackgroundImg();
    void drawTrafficObjects();

    std::string _bgFilename;
    std::string _windowName;
    std::vector<cv::Mat> _images;
    std::vector<std::shared_ptr<TrafficObject>> _trafficObjects;
};

#endif