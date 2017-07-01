/*
 * allPairsShortestPath.h
 *
 *  Created on: 11. 3. 2015.
 *      Author: Tomislav
 */
#ifndef __allPairsShortestPath_
#define __allPairsShortestPath_

#include "tocka.h"
#include <vector>
#include <algorithm>

void findShortestPathRecursive(std::vector<tocka> & tocke, std::vector<tocka> & shortestPath, double *pathLength);
void findShortestPathNonrecursive(std::vector<tocka> & tocke, std::vector<tocka> & shortestPath, double *pathLength);

#endif /* allPairsShortestPath_ */
