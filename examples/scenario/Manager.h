#ifndef MANAGER_H
#define MANAGER_H

#include "ColorT.h"
#include "GameObject.h"
#include "GeneratorBase.h"
#include <SDL.h>

class Manager: public GameObject {
 private:
  float accumulatedTime = 0;
  int sideSize=512;
  SDL_Texture *texture;
  bool isSimulating = false;

  //Tuck variables

  float waterLevel = 0.5;
  float sandLevel = 0.75;
  float grassLevel = 0.8;
  float mountainLevel = 0.9;

  int villageSpawnRate = 50;

  //Tuck variables

  std::vector<ScenarioGeneratorBase*> generators;
  int generatorId=0;

  void step();
 public:
  ~Manager();
  explicit Manager(Engine* engine, int size);

  void Start() override;
  void OnGui(ImGuiContext *context) override;
  void OnDraw(SDL_Renderer* renderer) override;
  void Update(float deltaTime) override;

  void Clear();
  int GetSize() const;

  void SetPixels(std::vector<Color32> &pixels);
};

#endif  // MANAGER_H
