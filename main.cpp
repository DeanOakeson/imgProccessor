#include "pixel.h"
#include <fstream>
#include <iostream>

struct Image {
  std::string magic;
  int width, height, maxval;
  std::vector<Pixel> pixels;
};

void writeColor(std::ostream &out, Pixel &p) {
  out << p.r << ' ' << p.g << ' ' << p.b << '\n';
}

// get height and width
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

int CalculateLuminosity(Image &img) {
  double nR = 0.0;
  double nG = 0.0;
  double nB = 0.0;
  double maxval = static_cast<double>(img.maxval);
  for (auto &p : img.pixels) {
    nR = p.r / maxval;
    nG = p.g / maxval;
    nB = p.b / maxval;
    p.l = 0.2126 * nR + 0.7152 * nG + 0.0722 * nB;
    std::cout << p.l;
  }
  return 0;
}

int CalculateKernelLuminosityScore(Image &img, int k_width, int k_height) {

  return 0;
}

int main() {

  Image img;
  // IMG PARSING
  ParseImage(img, "bliss.ppm");

  // IMAGE PROCESSING
  CalculateLuminosity(img);
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
