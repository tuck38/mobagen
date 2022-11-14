#ifndef HaK_H
#define HaK_H

#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>
#include <queue>
#include <list>

class HuntandKill : public MazeGeneratorBase 
{
 private:

	 Point2D originalPoint;
	 Point2D currentNode;
	 Point2D nextNode;
	 
	 Point2D max;
     Point2D min;

	 bool hunt;
     bool start;

 public:

	HuntandKill() = default;
	std::string GetName() override { return "HaK"; };
	bool Step(World* w) override;
	void Clear(World* world) override;

	Point2D Hunt(World* w);
    bool Walk(World* w);

};

#endif