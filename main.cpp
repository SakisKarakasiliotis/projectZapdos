#include <iostream>
#include "dynamicGraph.h"
#include "staticGraph.h"


using namespace std;

int main(int argc, char const *argv[])
{
   int graphType;
   cout << "Please select dynamic (0) or static (1) graph type: ";
   cin >> graphType;
   cout << endl << endl;
   
   if (graphType) return staticGraph();
   return dynamicGraph();
}