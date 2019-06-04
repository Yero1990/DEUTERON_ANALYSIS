#include "analyze.h"
#include "analyze.C"
#include "util_macros/utilities.h"
#include <iostream>
#include <ctime>

using namespace std;

//int main_analysis(Bool_t run_simc=kFALSE, Bool_t run_data=kTRUE, string rlist="h2.dat")
int main_analysis()
{

  int input;
  string inputCutFileName;
  string runlist_name;
  int pm_set;
  int dataSet;
  Bool_t run_simc_flag;
  Bool_t run_data_flag;
  string react_type;
  ifstream ifs;
  int run;
  string line;

  cout << "Please Select Which Input Cut File to Use . . ." << endl;
  cout << "1 = set_heep_cuts.inp,   2 = set_deep_cuts.inp "<< endl;
  cin >> input;
  cout << "" << endl;
  
  if (input==1){

    inputCutFileName="set_heep_cuts.inp";
    runlist_name = "runlists/h2.dat";
    run_simc_flag = stoi(split(FindString("RUN_SIMC", inputCutFileName)[0], ':')[1]);
    run_data_flag = stoi(split(FindString("RUN_DATA", inputCutFileName)[0], ':')[1]);
    react_type = "heep";

  }
  
  else if (input==2){

    inputCutFileName="set_deep_cuts.inp";
    pm_set = stoi(split(FindString("pm_setting", inputCutFileName)[0], ':')[1]);
    dataSet = stoi(split(FindString("data_set", inputCutFileName)[0], ':')[1]);
    runlist_name = Form("runlists/d2_pm%i_set%i.dat", pm_set, dataSet);
    run_simc_flag = stoi(split(FindString("RUN_SIMC", inputCutFileName)[0], ':')[1]);
    run_data_flag = stoi(split(FindString("RUN_DATA", inputCutFileName)[0], ':')[1]);
    react_type = "deep";
    ifs.open(runlist_name);
    getline(ifs, line);
    run = stoi(line);  //get the 1st run from the runlist (all simc needs is to know the kinematic setting which can get from any run in thr runlist.)
    ifs.close();
  }
  
  //open runlist

   
  //=========================S I M C=========================

  if(run_simc_flag)
    {

      if (react_type=="heep"){
        
	ifs.open(runlist_name);

	//Read Run List
	while(getline(ifs, line))
	  {
	    run = stoi(line);
	    //Initialize Class Object (SIMC)
	    analyze a1(run, "SHMS", "simc", react_type);
	    a1.run_simc_analysis();
	  }
       
	ifs.close();
	cout << "closing file " << endl;
      }

      else if(react_type=="deep"){

	//Initialize Class Object (SIMC)
	analyze a1(run, "SHMS", "simc", react_type);
	a1.run_simc_analysis();

      }

    }
  
  //==========================================================
  

  if(run_data_flag){

    ifs.open(runlist_name);
    
    //Read Run List
    while(getline(ifs, line))
      {
	run = stoi(line);
	cout << "run = " << run << endl;
	cout << "reaction = " << react_type << endl;
	//cout << "pm_set =  " << pm_set << endl;
	//Initialize Class Object(DATA)
	analyze a2(run, "SHMS", "data", react_type);
	a2.run_data_analysis();
	
      }
    ifs.close();
      
  }
  
  
  
  return 0;
}
