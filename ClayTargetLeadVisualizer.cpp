// ClayTargetLeadVisualizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
Let's start simple with a 2D topdown view of a flatland.

We will draw the 'target' flight path as time passes in the 2D plane
(There will be no up or down to start, so no 'height')

We will draw the shooter in relation to the target, and his shot path to the target with the calculated lead

________________
|  s           | 
|   \          | 
|    **        | 
|   T  *       | 
|  *    *      | 
________________

s = shooter location
* = projected flight path over time
T = the current location of the target
\ = the shot path

*/

int main()
{
    std::cout << "Hello World!\n";
}