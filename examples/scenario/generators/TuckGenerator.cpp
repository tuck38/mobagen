#include "../Noise.h"
#include "../PerlinNoise.hpp"
#include "TuckGenerator.h"
#include <iostream>
std::vector<Color32> TuckGenerator::Generate(float water, float sand, float grass, float mountain, int village, int sideSize, float displacement) 
{
  waterLevel = water;
  sandLevel = sand;
  grassLevel = grass;
  mountainLevel = mountain;
  villageSpawnRate = village;

  srand(time(NULL));

  std::vector<Color32> colors;
  std::vector<float> heightMap;
  siv::BasicPerlinNoise<float> noise;
  noise.reseed(1337);
  for (int l = 0; l < sideSize; l++) 
  {
    for (int c = 0; c < sideSize; c++) 
    {
      float height = ((noise.octave3D(c / 50.0, l / 50.0, displacement, 3, 0.5) + 1) / 2);

      colors.emplace_back(terrainType(height));
    }
  }
  return colors;
}
std::string TuckGenerator::GetName() { return "Tuck"; }

Color32 TuckGenerator::terrainType(float height) {
  if (height <= waterLevel) 
  {
    return Color32(0, 0, height * 255);
  } 
  else if (height <= sandLevel) 
  {
    return Color32(height * 85.1, height * 69.8, height * 50.2);
  } 
  else if (height <= grassLevel) 
  {
    int doVillageSpawn;
    if (villageSpawnRate != 0 && villageSpawnRate != 100) {
      doVillageSpawn = rand() % villageSpawnRate;
    } 
    else if (villageSpawnRate == 100) 
    {
      doVillageSpawn = 1;
    }
    else 
    {
      doVillageSpawn = 0;
    }
    if (doVillageSpawn == 0) 
    {
      return Color32(255, 0, 0);
    } 
    else 
    {
      return Color32(height * 49.73, height * 78.02, height * 31.45);
    }
  } 
  else if (height <= mountainLevel) 
  {
    return Color32(height * 149, height * 141, height * 133);
  } 
  else 
  {
    // default to snowwy peaks
    if (height >= 1) {
      return Color32(255, 255, 255);
    } 
    else 
    {
      return Color32(height * 255, height * 255, height * 255);
    }
  }
}
