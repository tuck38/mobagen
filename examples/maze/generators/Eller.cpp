#include "Eller.h"
#include "../World.h"
#include "Random.h"
#include <climits>
#include <ctime>

bool Eller::Step(World* w) 
{ 
    if (start) 
    {
        currentRow = -(w->GetSize() - 1) / 2;
        currentColumn = -(w->GetSize() - 1) / 2;
        currentRowSet = std::vector<std::queue<Point2D>>(w->GetSize());
        start = false;
        srand(time(NULL));
    }

	if (currentRow <= (w->GetSize() - 1) / 2) 
    {
        if (currentColumn <= (w->GetSize() - 1) / 2) 
        {
            w->SetNodeColor(Point2D(currentColumn + 1, currentRow), Color::Red.Dark());
            currentRowSet[currentColumn + (w->GetSize() - 1) / 2].push(Point2D(currentColumn, currentRow));
            if (currentRow != -(w->GetSize() - 1) / 2)
            {
                connectColumn(w, Point2D(currentColumn, currentRow));
            }

            if (currentRow != (w->GetSize() - 1) / 2) 
            {
              connectRow(w, Point2D(currentColumn, currentRow));
            } 
            else {
              w->SetNodeColor(Point2D(currentColumn, currentRow), Color::Black);
              if (currentColumn != -(w->GetSize() - 1) / 2)
              {
                w->SetWest(Point2D(currentColumn, currentRow), false);
              }
            }
            /*std::cout << "node " << currentColumn << ": " << currentRowSet[currentColumn + (w->GetSize() - 1) / 2].empty() << std::endl;
            if (currentRow != -(w->GetSize() - 1) / 2)
            {
                std::cout << "prev " << currentColumn << ": " << prevRowSet[currentColumn + (w->GetSize() - 1) / 2].empty() << std::endl;
            }*/
            if (currentColumn == (w->GetSize() - 1) / 2) 
            {
              currentColumn = -(w->GetSize() - 1) / 2;
              prevRowSet = currentRowSet;
              for (int i = 0; i < currentRowSet.size(); i++) 
              {
                while (currentRowSet[i].empty() != true) 
                {
                  currentRowSet[i].pop();
                }
              }
              currentRow++;
            } 
            else 
            {
              currentColumn++;
            }
        }
        return true;
    }
    w->SetNodeColor(Point2D((w->GetSize() - 1) / 2, (w->GetSize() - 1) / 2),Color::Black);
    return false;
}

void Eller::connectRow(World* w, Point2D p) 
{ 
  int num = rand() % 2 + 1;
  if (p.x == -(w->GetSize() - 1) / 2) 
  {
    num = 2;
  }
  if (num == 1) 
  {
    int setToInsert = currentColumn - 1;
    while (currentRowSet[(setToInsert + (w->GetSize() - 1) / 2)].empty() == true || pointInQueue(Point2D(p.x - 1, p.y), currentRowSet[setToInsert + (w->GetSize() - 1) / 2]) == false) 
    {
      setToInsert--;
    }

    if (bothPointsInQueue(p, Point2D(p.x - 1, p.y), currentRowSet[(setToInsert + (w->GetSize() - 1) / 2)]) == false) 
    {
      w->SetWest(p, false);
      Point2D point = currentRowSet[(currentColumn + (w->GetSize() - 1) / 2)].front();
      currentRowSet[(currentColumn + (w->GetSize() - 1) / 2)].pop();
      currentRowSet[(setToInsert + (w->GetSize() - 1) / 2)].push(point);
    }
    w->SetNodeColor(p, Color::Black);
  } 
  else if (num == 2) 
  {
      w->SetNodeColor(p, Color::Black);
  }
  //std::cout << "node (" << currentColumn << ", " << currentRow << ") isempty: " << currentRowSet[currentColumn + (w->GetSize() - 1) / 2].empty() << std::endl;
}

void Eller::connectColumn(World* w, Point2D p) 
{ 
    int num = rand() % 2 + 1;
    Point2D aboveNode = Point2D(currentColumn, currentRow - 1);
    int aboveNodeGroup = currentColumn;
    /*if (currentColumn == -(w->GetSize() - 1) / 2) 
    {
      aboveNodeGroup = (w->GetSize() - 1) / 2;
      aboveNode = Point2D((w->GetSize() - 1) / 2, currentRow + 1);
    }*/
    bool setHasBottom = false;

    while (prevRowSet[aboveNodeGroup + (w->GetSize() - 1) / 2].empty() == true || pointInQueue(aboveNode, prevRowSet[aboveNodeGroup + (w->GetSize() - 1) / 2]) == false)
    {
      aboveNodeGroup--;
    }

    std::queue queueToLookAt = prevRowSet[aboveNodeGroup + (w->GetSize() - 1) / 2];
    Point2D pointWithBottom = currentRowSet[(currentColumn + (w->GetSize() - 1) / 2)].front();
    while (queueToLookAt.empty() == false)  
    {
      if(w->GetSouth(queueToLookAt.front()) == false) 
      {
        Point2D pointWithBottom = queueToLookAt.front(); 
        setHasBottom = true;
      } 
      queueToLookAt.pop();
    }

    if (num == 1 && canHorizConnect || setHasBottom == false && aboveNode == prevRowSet[aboveNodeGroup + (w->GetSize() - 1) / 2].back())
    {
       w->SetNorth(p, false);
      if (setHasBottom == true) 
      {
         Point2D point = currentRowSet[(currentColumn + (w->GetSize() - 1) / 2)].front();
        currentRowSet[(currentColumn + (w->GetSize() - 1) / 2)].pop();
        currentRowSet[pointWithBottom.x + (w->GetSize() - 1) / 2].push(point);
      } 
       canHorizConnect = false;
    }
    else if(num == 2 || canHorizConnect == false) 
    {
      canHorizConnect = true;
    }
}

bool Eller::pointInQueue(Point2D p, std::queue<Point2D> q)
{
    while (!q.empty())
    {
      if (q.front() == p)
      {
          return true;
      }
      q.pop();
    }
}

bool Eller::bothPointsInQueue(Point2D p1, Point2D p2, std::queue<Point2D> q) 
{
  bool firstIn = false;
  bool secondIn = false;
  while (!q.empty()) 
  {
    if (q.front() == p1) 
    {
      firstIn = true;
    } 
    else if (q.front() == p2)
    {
      secondIn = true;
    }

    if (firstIn && secondIn) 
    {
      return true;
    } 

    q.pop();
  }
  return false;
}

void Eller::Clear(World* w) 
{ 
    start = true;
}