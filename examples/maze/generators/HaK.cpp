#include "HaK.h"
#include "../World.h"
#include "Random.h"
#include <climits>
#include <ctime>

bool HuntandKill::Step(World* w) 
{
	if(start) 
	{
       start = false;
       srand(time(NULL));
       max = Point2D(-(w->GetSize() - 1) / 2, -(w->GetSize() - 1) / 2);
       min = Point2D((w->GetSize() - 1) / 2, (w->GetSize() - 1) / 2);
       int randX = rand() % min.x + max.x;
       int randY = rand() % min.y + max.y;
       originalPoint = Point2D(randX, randY);
       currentNode = Point2D(randX, randY);
    }

    hunt = Walk(w);
    if (hunt) 
    {
       nextNode = Hunt(w);
       if (nextNode == originalPoint)
       {
         return false;
       }
    }
    w->SetNodeColor(currentNode, Color::Black);
    w->SetNodeColor(nextNode, Color::Red.Dark());

    currentNode = nextNode;

    return true;
}

void HuntandKill::Clear(World* world) 
{
  start = true;
}

Point2D HuntandKill::Hunt(World* w) 
{
  for (int i = max.x; i <= min.x; i++) 
  {
    for (int k = max.y; k <= min.y; k++) 
    {
      if (w->GetNorth(Point2D(i, k)) && w->GetEast(Point2D(i, k)) 
      && w->GetSouth(Point2D(i, k)) && w->GetWest(Point2D(i, k)))
      {
        std::cout << "hunting\n";
        hunt = false;
        return Point2D(i, k);
      }
    }
  }
  return originalPoint;
}

bool HuntandKill::Walk(World* w) 
{ 
  Point2D Visitable[4];
  int visitablePoints = 0;

   if (w->GetNorth(Point2D(currentNode.x + 1, currentNode.y)) && w->GetEast(Point2D(currentNode.x + 1, currentNode.y)) 
   && w->GetSouth(Point2D(currentNode.x + 1, currentNode.y)) && w->GetWest(Point2D(currentNode.x + 1, currentNode.y)) && currentNode.x != min.x)
   {
     Visitable[visitablePoints] = Point2D(currentNode.x + 1, currentNode.y);
     visitablePoints++;
   }

   if (w->GetNorth(Point2D(currentNode.x - 1, currentNode.y)) && w->GetEast(Point2D(currentNode.x - 1, currentNode.y)) 
   && w->GetSouth(Point2D(currentNode.x - 1, currentNode.y)) && w->GetWest(Point2D(currentNode.x - 1, currentNode.y)) && currentNode.x != max.x)
   {
     Visitable[visitablePoints] = Point2D(currentNode.x - 1, currentNode.y);
     visitablePoints++;
   }

   if (w->GetNorth(Point2D(currentNode.x, currentNode.y + 1)) && w->GetEast(Point2D(currentNode.x, currentNode.y + 1)) 
   && w->GetSouth(Point2D(currentNode.x, currentNode.y + 1)) && w->GetWest(Point2D(currentNode.x, currentNode.y + 1)) && currentNode.y != min.y)
   {
     Visitable[visitablePoints] = Point2D(currentNode.x, currentNode.y + 1);
     visitablePoints++;
   }

   if (w->GetNorth(Point2D(currentNode.x, currentNode.y - 1)) && w->GetEast(Point2D(currentNode.x, currentNode.y - 1)) 
   && w->GetSouth(Point2D(currentNode.x, currentNode.y - 1)) && w->GetWest(Point2D(currentNode.x, currentNode.y - 1)) && currentNode.y != max.y)
   {
     Visitable[visitablePoints] = Point2D(currentNode.x, currentNode.y - 1);
     visitablePoints++;
   }

   if (visitablePoints == 0) 
   {
     return true;
   } 
   else 
   {
     int nextSide = rand() % visitablePoints;
     std::cout << "array size: " << visitablePoints - 1 << std::endl;
     std::cout << "next side: " << nextSide << std::endl;
     nextNode = Visitable[nextSide];

    if (Point2D(nextNode.x + 1, nextNode.y) == currentNode) 
    {
      w->SetWest(currentNode, false);
    }
    else if (Point2D(nextNode.x - 1, nextNode.y) == currentNode) 
    {
      w->SetEast(currentNode, false);
    }
    else if (Point2D(nextNode.x, nextNode.y + 1) == currentNode) 
    {
      w->SetNorth(currentNode, false);
    }
    else if (Point2D(nextNode.x, nextNode.y - 1) == currentNode) 
    {
      w->SetSouth(currentNode, false);
    }
   }


   //w->SetNodeColor(nextNode, Color::Red.Dark());
   
   return false;
}