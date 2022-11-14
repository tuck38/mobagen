#ifndef ELLER_H
#define ELLER_H

#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>
#include <queue>
#include <list>

class Eller : public MazeGeneratorBase 
{
private:
	std::vector<std::queue<Point2D>> prevRowSet;
    std::vector<std::queue<Point2D>> currentRowSet;
	int currentRow = 0;
	int currentColumn = 0;

	bool start = true;
    bool canHorizConnect = true;

 public:
    Eller() = default;
	std::string GetName() override { return "Eller"; };
	bool Step(World* world) override;
	void Clear(World* world) override;

	bool bothPointsInQueue(Point2D p1, Point2D p2, std::queue<Point2D> q);
	bool pointInQueue(Point2D p, std::queue<Point2D> q);


    void connectRow(World* w, Point2D p);
    void connectColumn(World* w, Point2D p);

};

#endif