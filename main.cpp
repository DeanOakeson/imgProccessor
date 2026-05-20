#include "pixel.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <stdint.h>
#include <vector>

struct Image {
  std::string magic;
  int width, height, maxval, kernel_w, kernel_h;
  std::vector<Pixel> pixels;
};

// PARSE .PPM IMAGES THAT ARE IN P6 FORMAT
//
int ParseImage(Image &img, const std::string &filePath) {

  std::ifstream image(filePath);

  if (!image.is_open()) {
    std::cerr << "Could not open file\n" << "Check file path\n";
    return 1;
  }

  auto skipComments = [&](std::ifstream &image) {
    char c;
    image >> std::ws;
    while (image.peek() == '#') {
      std::string dummy;
      std::getline(image, dummy);
      image >> std::ws;
    }
  };

  // GET HEIGHT AND WIDTH
  image >> img.magic;
  image.ignore(std::numeric_limits<std::streamsize>::max(),
               '\n'); // consume rest of line including \r
  skipComments(image);
  image >> img.width;
  std::cerr << "width: " << img.width << "\n";
  skipComments(image);
  image >> img.height;
  std::cerr << "height: " << img.height << "\n";
  skipComments(image);
  image >> img.maxval;
  std::cerr << "maxval: " << img.maxval << "\n";
  skipComments(image);

  img.pixels.resize(img.width * img.height);

  for (auto &p : img.pixels) {
    uint8_t r, g, b;
    image.read(reinterpret_cast<char *>(&r), 1);
    image.read(reinterpret_cast<char *>(&g), 1);
    image.read(reinterpret_cast<char *>(&b), 1);
    p.r = r;
    p.g = g;
    p.b = b;
  }
  return 0;
}

// WRITE COLOR OF PIXEL TO AN OUT FILE
//
void writeColor(std::ostream &out, Pixel &p) {
  out << (int)p.r << ' ' << (int)p.g << ' ' << (int)p.b << '\n';
}

// CALCULATES CHANCE OF A PIXEL BEING TURNED ON OR OFF BY ITS KERNEL'S
// LUMINOSITY

int CalculateKernelLuminosityScore(Image &img, int k_width, int k_height) {
  double k_luminosity;

  for (auto &p : img.pixels) {
  }

  return 0;
}

int main() {

  Image img;

  // IMG PARSING
  ParseImage(img, "bliss.ppm");

  // IMAGE PROCESSING LOOP
  for (auto &p : img.pixels) {
    // p.MuteGreenChannel();
    p.CalculateLuminosity(img.maxval);
    // p.ConvertBlackAndWhite();
    p.ClampColorChannels(255, 255, 255);
  }

  CalculateKernelLuminosityScore(img, 10, 10);

  // IMAGE OUT
  std::ofstream outImage;
  outImage.open("image.ppm");

  outImage << "P3\n"
           << img.width << " " << img.height << "\n"
           << img.maxval << "\n";

  if (!outImage.is_open()) {
    std::cerr << "file not open\n";
  }

  for (auto &p : img.pixels) {
    writeColor(outImage, p);
  }
}
