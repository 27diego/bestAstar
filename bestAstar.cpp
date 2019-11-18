#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <map>
using namespace std;

int heuristic(pair<int, int> origin, pair<int, int> dest)
{
    return abs(origin.first - dest.first) + abs(origin.second - dest.second);
}


pair<int, int> bestAstar(map<pair<int,int>, pair<int, int>> distances, set<pair<int,int>> visited)
{
    pair<int, int> answer = pair<int, int>(-1,-1);
    int compare = INT_MAX;
    for(auto distance : distances)
    {
        if(!visited.count(distance.first) && distance.second.first +  distance.second.second <= compare)
        {
            compare = distance.second.first + distance.second.second;
            answer = distance.first;
        }
    }
    return answer;
}

vector<pair<int, int>> getNeighbors(int x, int y, int xBound, int yBound)
{
    // vector<int> xCoordinates = {-1,1,0,0,-1,1,-1,1};
    // vector<int> yCoordinates = {0,0,-1,1,1,1,-1,-1};
    vector<int> xCoordinates = {-1,1,0,0};
    vector<int> yCoordinates = {0,0,-1,1};
    vector<pair<int, int>> neighbors = {};
    for(int z=0;z<xCoordinates.size();z++)
    {
        int tempx = x + xCoordinates[z];
        int tempy = y + yCoordinates[z];
        if(tempx>=0 && tempx<xBound && tempy>=0 && tempy<yBound)
        {
            neighbors.push_back(pair<int,int>(tempx,tempy));
        }
    }
    return neighbors;
}

int AStar(pair<int, int> origin, pair<int, int>dest, vector<vector<bool>>grid)
{
    auto finalized = set<pair<int, int>>();
    auto distances = map<pair<int, int>, pair<int, int>>();

    distances[origin] = pair<int, int>(0,heuristic(origin, dest));
    auto current = origin;
    bool inBounds = false;

    while(current.first != dest.first || current.second != dest.second)
    {
        finalized.insert(current);
        for(auto neighbor : getNeighbors(current.first, current.second, grid.size(), grid[0].size()))
        {
            if(grid[neighbor.first][neighbor.second])
            {
                inBounds = true;
            }
            if(!finalized.count(neighbor) && inBounds==true)
            {
                if(!distances.count(neighbor))
                {
                    distances[neighbor] = pair<int, int>(distances[current].first + 1, heuristic(neighbor, dest));
                }
                else if(distances[neighbor].first>current.first + 1)
                {
                    distances[neighbor].first = distances[current].first + 1;
                }
            }
            inBounds = false;
        }
        current = bestAstar(distances, finalized);
    }

    return distances[current].first;
}


int main()
{
    vector<vector<bool>> grid = {
        {0,0,1,0},
        {0,0,1,1},
        {0,0,0,1},
        {0,1,1,1}
    };
    
    cout << AStar(pair<int, int>(0, 2), pair<int, int>(3, 1), grid)<<endl;
    
    
    /*
     
     0 2
     3 1
     
    OOOOOX
    XXOXOO
    OOXOOX
    XOOOOO
    OOXXXO
    XOOXOO
     */
}

