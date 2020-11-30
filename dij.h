
// A C++ Program to implement A* Search Algorithm - Geeks for Geeks
#include<bits/stdc++.h>
#include <vector>
//#include "map.h"

//#include <chrono>




//#include "ECE_Ghost.h"
//#include "map.h"


#define ROW 22 
#define COL 19 
class dij{
// Creating a shortcut for int, int pair type
    typedef std::pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type 
    typedef std::pair<double, std::pair<int, int>> pPair;

// A structure to hold the neccesary parameters 
    struct cell
    {
        // Row and Column index of its parent
        // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
        double parent_i, parent_j;
        // f = g + h
        double f, g, h;
    };
    //returns false if value is in vector of missed walls
    static bool isUnique(Pair p, std::vector<Pair> vec) {
        if (vec.empty()) return true;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == p) return false;
        }
        return true;
    }

// A Utility Function to check whether given cell (row, col) 
// is a valid cell or not. 
    static bool isValid(int row, int col)
    {
        // Returns true if row number and column number
        // is in range
        return (row >= -7) && (row < ROW) &&
               (col >= -9) && (col < COL);
    }
    
// A Utility Function to check whether the given cell is 
// blocked or not 
    static bool isUnBlocked(char grid[][COL], int row, int col, std::vector<Pair> &vec)
    {
        // Returns true if the cell is not blocked else false
        if (!isUnique(std::make_pair(row,col),vec) || grid[row][col] == 'h' || grid[row][col] == 'v' || (grid[row+1][col] == 'h' && (row < 18 || row == 20))) {
            //std::cout << row << ", " << col << " blocked" << std::endl;
            return false;
        }
        else return true;
    }

// A Utility Function to check whether destination cell has 
// been reached or not 
    static bool isDestination(int row, int col, Pair dest)
    {
        if (row == dest.first && col == dest.second)
            return (true);
        else
            return (false);
    }

// A Utility Function to calculate the 'h' heuristics. 
    static double calculateHValue(int row, int col, Pair dest)
    {
        // Return using the distance formula
        return abs((row-dest.first)) + abs((col-dest.second));
    }

// A Utility Function to trace the path from the source 
// to destination 
    static Pair tracePath(cell cellDetails[][COL], Pair dest)
    {
        //printf ("\nThe Path is ");
        int row = dest.first;
        int col = dest.second;

        std::stack<Pair> Path;

        while (!(cellDetails[row][col].parent_i == row
                 && cellDetails[row][col].parent_j == col ))
        {
            Path.push (std::make_pair (row, col));
            int temp_row = cellDetails[row][col].parent_i;
            int temp_col = cellDetails[row][col].parent_j;
            row = temp_row;
            col = temp_col;
        }
        int count = 0;
        Path.push (std::make_pair (row, col));
        while (!Path.empty())
        {
            //std::this_thread::sleep_for (std::chrono::seconds(1));
            std::pair<int,int> p = Path.top();
            Path.pop();
            if (count == 1)
            {
                int x = 15 - p.first;
                int y = 10 - p.second;
                return std::make_pair (x, y);
            }

            count++;
            //printf("-> (%d,%d) ",p.first,p.second);
        }

        return std::make_pair(0,0);
    }

// A Function to find the shortest path between 
// a given source cell to a destination cell according 
// to A* Search Algorithm 
public: static Pair aStarSearch(char grid[][COL], Pair src, Pair dest, std::vector<Pair> &vec)
    {
        // If the source is out of range
        if (!isValid(src.first, src.second))
        {
            printf ("Source is invalid\n");
            return std::make_pair(0,0);
        }

        // If the destination is out of range
        if (!isValid(dest.first, dest.second))
        {
            printf ("Destination is invalid\n");
            return std::make_pair(0,0);
        }

        //Either the source or the destination is blocked
        if (!isUnBlocked(grid, src.first, src.second, vec) ||
            !isUnBlocked(grid, dest.first, dest.second, vec))
        {
            //printf ("Source or the destination is blocked\n");
            return std::make_pair(0,0);
        }

        // If the destination cell is the same as source cell
        if (isDestination(src.first, src.second, dest) == true)
        {
            printf ("We are already at the destination\n");
            return std::make_pair(0,0);
        }

        // Create a closed list and initialise it to false which means
        // that no cell has been included yet
        // This closed list is implemented as a boolean 2D array
        bool closedList[ROW][COL];
        memset(closedList, false, sizeof (closedList));

        // Declare a 2D array of structure to hold the details
        //of that cell
        cell cellDetails[ROW][COL];

        int i, j;

        for (i=0; i<ROW; i++)
        {
            for (j=0; j<COL; j++)
            {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].h = FLT_MAX;
                cellDetails[i][j].parent_i = -1;
                cellDetails[i][j].parent_j = -1;
            }
        }

        // Initialising the parameters of the starting node
        i = src.first, j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j;

        /*
        Create an open list having information as-
        <f, <i, j>>
        where f = g + h,
        and i, j are the row and column index of that cell
        Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
        This open list is implenented as a set of pair of pair.*/
        std::set<pPair> openList;

        // Put the starting cell on the open list and set its
        // 'f' as 0
        openList.insert(std::make_pair (0.0, std::make_pair (i, j)));

        // We set this boolean value as false as initially
        // the destination is not reached.
        bool foundDest = false;

        while (!openList.empty())
        {
            pPair p = *openList.begin();

            // Remove this vertex from the open list
            openList.erase(openList.begin());

            // Add this vertex to the closed list
            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            /*
                Generating all the 8 successor of this cell

                    N.W N N.E
                    \ | /
                    \ | /
                    W----Cell----E
                        / | \
                    / | \
                    S.W S S.E

                Cell-->Popped Cell (i, j)
                N --> North	 (i-1, j)
                S --> South	 (i+1, j)
                E --> East	 (i, j+1)
                W --> West		 (i, j-1)
                N.E--> North-East (i-1, j+1)
                N.W--> North-West (i-1, j-1)
                S.E--> South-East (i+1, j+1)
                S.W--> South-West (i+1, j-1)*/

            // To store the 'g', 'h' and 'f' of the 8 successors
            double gNew, hNew, fNew;

            //----------- 1st Successor (North) ------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j) && isUnBlocked(grid, i-1, j, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i - 1, j, dest))
                {
                    // Set the Parent of the destination cell
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                    //printf ("The destination cell is found\n");
                    foundDest = true;
                    return tracePath (cellDetails, dest);
                    
                    
                }
                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (!closedList[i - 1][j] &&
                         isUnBlocked(grid, i - 1, j, vec))
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue (i-1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i-1][j].f == FLT_MAX ||
                        cellDetails[i-1][j].f > fNew)
                    {
                        openList.insert( std::make_pair(fNew,
                                                   std::make_pair(i-1, j)));

                        // Update the details of this cell
                        cellDetails[i-1][j].f = fNew;
                        cellDetails[i-1][j].g = gNew;
                        cellDetails[i-1][j].h = hNew;
                        cellDetails[i-1][j].parent_i = i;
                        cellDetails[i-1][j].parent_j = j;
                    }
                }
            }

            //----------- 2nd Successor (South) ------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j) && isUnBlocked(grid, i+1, j, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i + 1, j, dest))
                {
                    // Set the Parent of the destination cell
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                    //printf("The destination cell is found\n");
                    foundDest = true;
                    return tracePath(cellDetails, dest);
                    
                    
                }
                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (!closedList[i + 1][j] &&
                         isUnBlocked(grid, i + 1, j, vec))
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i+1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i+1][j].f == FLT_MAX ||
                        cellDetails[i+1][j].f > fNew)
                    {
                        openList.insert( std::make_pair (fNew, std::make_pair (i+1, j)));
                        // Update the details of this cell
                        cellDetails[i+1][j].f = fNew;
                        cellDetails[i+1][j].g = gNew;
                        cellDetails[i+1][j].h = hNew;
                        cellDetails[i+1][j].parent_i = i;
                        cellDetails[i+1][j].parent_j = j;
                    }
                }
            }

            //----------- 3rd Successor (East) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j + 1) && isUnBlocked(grid, i, j + 1, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i, j + 1, dest))
                {
                    // Set the Parent of the destination cell
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                    //printf("The destination cell is found\n");
                    foundDest = true;
                    return tracePath(cellDetails, dest);
                    
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (!closedList[i][j + 1] &&
                         isUnBlocked(grid, i, j + 1, vec))
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue (i, j+1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i][j+1].f == FLT_MAX ||
                        cellDetails[i][j+1].f > fNew)
                    {
                        openList.insert( std::make_pair(fNew,
                                                   std::make_pair (i, j+1)));

                        // Update the details of this cell
                        cellDetails[i][j+1].f = fNew;
                        cellDetails[i][j+1].g = gNew;
                        cellDetails[i][j+1].h = hNew;
                        cellDetails[i][j+1].parent_i = i;
                        cellDetails[i][j+1].parent_j = j;
                    }
                }
            }

            //----------- 4th Successor (West) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j - 1) && isUnBlocked(grid, i, j - 1, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i, j - 1, dest))
                {
                    // Set the Parent of the destination cell
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                    //printf("The destination cell is found\n");
                    foundDest = true;
                    return tracePath(cellDetails, dest);
                    
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (!closedList[i][j - 1] &&
                         isUnBlocked(grid, i, j - 1, vec))
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j-1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i][j-1].f == FLT_MAX ||
                        cellDetails[i][j-1].f > fNew)
                    {
                        openList.insert( std::make_pair (fNew,
                                                    std::make_pair (i, j-1)));

                        // Update the details of this cell
                        cellDetails[i][j-1].f = fNew;
                        cellDetails[i][j-1].g = gNew;
                        cellDetails[i][j-1].h = hNew;
                        cellDetails[i][j-1].parent_i = i;
                        cellDetails[i][j-1].parent_j = j;
                    }
                }
            }

            //----------- 5th Successor (North-East) ------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j + 1) && isUnBlocked(grid, i-1, j + 1, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i - 1, j + 1, dest))
                {
                    // Set the Parent of the destination cell
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                    //printf ("The destination cell is found\n");
                    foundDest = true;
                    return tracePath (cellDetails, dest);
                    
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i-1][j+1] == false &&
                         isUnBlocked(grid, i-1, j+1, vec) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i-1, j+1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i-1][j+1].f == FLT_MAX ||
                        cellDetails[i-1][j+1].f > fNew)
                    {
                        openList.insert( std::make_pair (fNew,
                                                    std::make_pair(i-1, j+1)));

                        // Update the details of this cell
                        cellDetails[i-1][j+1].f = fNew;
                        cellDetails[i-1][j+1].g = gNew;
                        cellDetails[i-1][j+1].h = hNew;
                        cellDetails[i-1][j+1].parent_i = i;
                        cellDetails[i-1][j+1].parent_j = j;
                    }
                }
            }

            //----------- 6th Successor (North-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (i-1, j-1) && isUnBlocked(grid, i-1, j - 1, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination (i-1, j-1, dest) == true)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                    //printf ("The destination cell is found\n");
                    foundDest = true;
                    return tracePath (cellDetails, dest);
                    
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i-1][j-1] == false &&
                         isUnBlocked(grid, i-1, j-1, vec) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i-1, j-1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i-1][j-1].f == FLT_MAX ||
                        cellDetails[i-1][j-1].f > fNew)
                    {
                        openList.insert( std::make_pair (fNew, std::make_pair (i-1, j-1)));
                        // Update the details of this cell
                        cellDetails[i-1][j-1].f = fNew;
                        cellDetails[i-1][j-1].g = gNew;
                        cellDetails[i-1][j-1].h = hNew;
                        cellDetails[i-1][j-1].parent_i = i;
                        cellDetails[i-1][j-1].parent_j = j;
                    }
                }
            }

            //----------- 7th Successor (South-East) ------------

            // Only process this cell if this is a valid one
            if (isValid(i+1, j+1) && isUnBlocked(grid, i+1, j+1, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i+1, j+1, dest) == true)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                    //printf ("The destination cell is found\n");
                    foundDest = true;
                    return tracePath (cellDetails, dest);
                    
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i+1][j+1] == false &&
                         isUnBlocked(grid, i+1, j+1, vec) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i+1, j+1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i+1][j+1].f == FLT_MAX ||
                        cellDetails[i+1][j+1].f > fNew)
                    {
                        openList.insert(std::make_pair(fNew,
                                                  std::make_pair (i+1, j+1)));

                        // Update the details of this cell
                        cellDetails[i+1][j+1].f = fNew;
                        cellDetails[i+1][j+1].g = gNew;
                        cellDetails[i+1][j+1].h = hNew;
                        cellDetails[i+1][j+1].parent_i = i;
                        cellDetails[i+1][j+1].parent_j = j;
                    }
                }
            }

            //----------- 8th Successor (South-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (i+1, j-1) && isUnBlocked(grid, i+1, j-1, vec))
            {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(i+1, j-1, dest) == true)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                    //printf("The destination cell is found\n");
                    foundDest = true;
                    return tracePath(cellDetails, dest);
                    
                }

                    // If the successor is already on the closed
                    // list or if it is blocked, then ignore it.
                    // Else do the following
                else if (closedList[i+1][j-1] == false &&
                         isUnBlocked(grid, i+1, j-1, vec) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i+1, j-1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //			 OR
                    // If it is on the open list already, check
                    // to see if this path to that square is better,
                    // using 'f' cost as the measure.
                    if (cellDetails[i+1][j-1].f == FLT_MAX ||
                        cellDetails[i+1][j-1].f > fNew)
                    {
                        openList.insert(std::make_pair(fNew,
                                                  std::make_pair(i+1, j-1)));

                        // Update the details of this cell
                        cellDetails[i+1][j-1].f = fNew;
                        cellDetails[i+1][j-1].g = gNew;
                        cellDetails[i+1][j-1].h = hNew;
                        cellDetails[i+1][j-1].parent_i = i;
                        cellDetails[i+1][j-1].parent_j = j;
                    }
                }
            }
        }

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destiantion cell. This may happen when the
        // there is no way to destination cell (due to blockages)
        if (foundDest == false)
           // printf("Failed to find the Destination Cell\n");

        return std::make_pair(0,0);
    }
};

// Driver program to test above function 


/*

int main()
{
    // Description of the Grid-
    //1--> The cell is not blocked
    //0--> The cell is blocked
    int grid[ROW][COL] =
            {
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                    { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                    { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
            };

    // Source is the left-most bottom-most corner
    Pair src = std::make_pair(5, 9);

    // Destination is the left-most top-most corner
    Pair dest = std::make_pair(11, 9);

    aStarSearch(map1, src, dest);

    return(0);
} */