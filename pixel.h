#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include <string.h>

class Pixel {
public:
  u_int8_t r = 0;
  u_int8_t g = 0;
  u_int8_t b = 0;

  bool calculated_l = false;

  double l = 0;
  double k_luminosity = 0;

  // CONVERTS IMAGE TO BLACK AND WHITE BY USING LUMINOSITY AS PIXEL VALUE
  //
  int ConvertBlackAndWhite() {
    CalculateLuminosity(255);
    if (calculated_l == false) {
      std::cerr << "You need to calculate luminosity first\n";
      return 1;
    }
    r = static_cast<int>(255.999 * l);
    g = static_cast<int>(255.999 * l);
    b = static_cast<int>(255.999 * l);
    return 0;
  }

  void ClampColorChannel(int colorId, int clamp) {
    switch (colorId) {
    case 0:
      r = r > clamp ? clamp : r;
      break;
    case 1:
      g = g > clamp ? clamp : g;
      break;
    case 2:
      b = b > clamp ? clamp : b;
      break;
    }
  }

  void MuteColorChannel(int colorId) {
    switch (colorId) {

    case 0:
      r = 0;
      break;
    case 1:
      g = 0;
      break;
    case 2:
      b = 0;
      break;
    }
  }

  // CALCULATE IMAGE LUMINOSITY
  //

  void CalculateLuminosity(int imgMaxVal = 255) {
    double nR = 0.0;
    double nG = 0.0;
    double nB = 0.0;
    double maxval = static_cast<double>(imgMaxVal);
    nR = static_cast<double>(r) / maxval;
    nG = static_cast<double>(g) / maxval;
    nB = static_cast<double>(b) / maxval;
    l = 0.2126 * nR + 0.7152 * nG + 0.0722 * nB;
    calculated_l = true;
  }
};

#endif
