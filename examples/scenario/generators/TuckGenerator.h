#ifndef MOBAGEN_TUCKGENERATOR_H
#define MOBAGEN_TUCKGENERATOR_H

#include "../GeneratorBase.h"

class TuckGenerator : public ScenarioGeneratorBase {
 public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;
};

#endif  // MOBAGEN_TUCKGENERATOR_H