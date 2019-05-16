#include "analyze.h"
#include "analyze.C"
#include <iostream>
#include <ctime>
using namespace std;

int main_analysis()
{

      
  //Initialize Class Object
  analyze a1(3288, "SHMS", "simc");
  a1.SetDefinitions();
  a1.SetFileNames();
  a1.SetHistBins();
  a1.CreateHist();
  a1.ReadTree();
  a1.EventLoop();
  a1.WriteHist();
  

  
  //Initialize Class Object
  analyze a2(3371, "SHMS", "data");
  a2.SetDefinitions();
  a2.SetFileNames();
  a2.SetHistBins();
  a2.CreateHist();
  a2.ReadScalerTree("BCM4A");   //argument: "BCM1", "BCM2", "BCM4A", "BCM4B", "BCM4C"
  a2.ScalerEventLoop(5);       //argument represents current threshold(uA): usage in code-> Abs(bcm_current - set_current) < threshold
  a2.ReadTree();
  a2.EventLoop();
  a2.CalcEff();
  a2.WriteHist();
  a2.WriteReport();
  

  return 0;
}
