#include "../Noise.h"
#include "../PerlinNoise.hpp"
#include "TuckGenerator.h"
#include <iostream>
std::vector<Color32> TuckGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;
  //   create your own function for noise generation
  siv::BasicPerlinNoise<float> noise;
  srand(time(NULL));
  noise.reseed(1337);
  //Noise noise(1337, 1024,0,255);
  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) {
      float rgb = abs(noise.octave3D(c / 50.0, l / 50.0, displacement, 2) * 255);

      colors.emplace_back(terrainType(rgb));
      //double color = noise.noise2D(c/50.0,l/50.0);
      //colors.emplace_back(color,color,color);
    }
  }
  std::cout << "tryna see smthn: " << std::endl;
  return colors;
}
std::string TuckGenerator::GetName() { return "Tuck"; }

Color32 TuckGenerator::terrainType(float rgb) 
{
    if (rgb < waterLevel)
    {
        return Color32(rgb, rgb, rgb * 5);
    } 
    else if (rgb < 75) 
    {
        return Color32(rgb * 7, rgb * 6, rgb * 5);
    }
    else if (rgb < grassLevel) 
    {
        return Color32(rgb, rgb * 5, rgb);
    } 
    else 
    {
        return Color32(rgb, rgb, rgb);
    }
}
