#include "analyze.h"
#include "analyze.C"
#include <iostream>
#include <ctime>
using namespace std;

int main_analysis(Bool_t run_simc=kTRUE, Bool_t run_data=kTRUE, string rlist="h2.dat")
{
  
  //open runlist
  ifstream ifs(Form("runlist/%s", rlist.c_str()));
  
  int run;
  string line;
  
  //Read Run List
  while(getline(ifs, line))
    {
      run = stoi(line);
      
      if(run_simc){
	cout << "ANALYZING SIMC RUN " << run << endl;
	//Initialize Class Object (SIMC)
	analyze a1(run, "SHMS", "simc", "heep");
	a1.SetFileNames();
	a1.SetCuts();
	a1.SetDefinitions();
	a1.SetHistBins();
	a1.CreateHist();
	a1.ReadTree();
	a1.EventLoop();
	a1.WriteHist();
	a1.ElasticStudy();
      }
      
      
      if(run_data){
	cout << "ANALYZING DATA RUN " << run << endl;
	//Initialize Class Object(DATA)
	analyze a2(run, "SHMS", "data", "heep");
	a2.SetFileNames();
	a2.SetCuts();
	a2.SetDefinitions();
	a2.SetHistBins();
	a2.CreateHist();
	a2.ReadScalerTree("BCM4A");   //argument: "BCM1", "BCM2", "BCM4A", "BCM4B", "BCM4C"
	a2.ScalerEventLoop(5);       //argument represents current threshold(uA): usage in code-> Abs(bcm_current - set_current) < threshold
	a2.ReadTree();
	a2.EventLoop();
	a2.CalcEff();
	a2.ApplyWeight();
	a2.WriteHist();
	a2.WriteReport();
	a2.ElasticStudy();
      }
      
      
    }
  
  
  
  return 0;
}
