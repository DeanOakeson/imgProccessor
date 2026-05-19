#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include <string.h>

class Pixel {
public:
  double r = 0;
  double g = 0;
  double b = 0;
  double l = 0;

  int getLuminosity() {
    l = 1.0;
    return 0.0;
  }
};

#endif
