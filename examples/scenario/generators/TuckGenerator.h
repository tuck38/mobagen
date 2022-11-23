#ifndef MOBAGEN_TUCKGENERATOR_H
#define MOBAGEN_TUCKGENERATOR_H

#include "../GeneratorBase.h"

class TuckGenerator : public ScenarioGeneratorBase {
 public:
  std::vector<Color32> Generate(float waterLevel, float sandLevel, float grassLevel, float mountainLevel, int villageRate, int sideSize, float displacement = 0) override;
  std::string GetName() override;
  Color32 terrainType(float rgb);

private:
  float waterLevel = 0.5;
  float sandLevel = 0.75;
  float grassLevel = 0.8;
  float mountainLevel = 0.9;

  int villageSpawnRate = 50;
};

#endif  // MOBAGEN_TUCKGENERATOR_H