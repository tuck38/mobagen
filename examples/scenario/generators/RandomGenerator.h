#ifndef MOBAGEN_RANDOMSCENARIOGENERATOR_H
#define MOBAGEN_RANDOMSCENARIOGENERATOR_H

#include "../GeneratorBase.h"

class RandomScenarioGenerator: public ScenarioGeneratorBase{
 public:
  std::vector<Color32> Generate(float waterLevel, float sandLevel, float grassLevel, float mountainLevel, int villageRate, int sideSize, float displacement=0) override;
  std::string GetName() override;

};

#endif  // MOBAGEN_RANDOMSCENARIOGENERATOR_H
