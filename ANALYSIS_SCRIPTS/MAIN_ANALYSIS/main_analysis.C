#include "analyze.h"
#include "analyze.C"
#include "util_macros/utilities.h"
#include <iostream>
#include <ctime>


using namespace std;

int main_analysis()
{

  int input;
  string inputCutFileName;
  string runlist_name;
  int pm_set;
  string theory;
  string model;
  int dataSet;
  Bool_t run_simc_flag;
  Bool_t run_data_flag;
  Bool_t rad_corr_flag;
  Bool_t single_run_flag;
  Bool_t Qnorm_flag;  //flag to normalize by total charge once all ROOTfiles have been combined.
  string react_type;
  ifstream ifs;
  int run;
  string line;
  int cnt = 0; //line counter

  cout << "Please Select Which Input Cut File to Use . . ." << endl;
  cout << "1 = set_heep_cuts.inp,   2 = set_deep_cuts.inp "<< endl;
  cin >> input;
  cout << "" << endl;
  
  //Do H(e,e'p)
  if (input==1){
    

    inputCutFileName="set_heep_cuts.inp";
    runlist_name = "runlists/h2.dat";
    run_simc_flag = stoi(split(FindString("RUN_SIMC", inputCutFileName)[0], ':')[1]);
    run_data_flag = stoi(split(FindString("RUN_DATA", inputCutFileName)[0], ':')[1]);
    rad_corr_flag = stoi(trim(split(FindString("rad_corr_flag", inputCutFileName)[0], ':')[1])); 
    single_run_flag = stoi(split(FindString("single_run_flag", inputCutFileName)[0], ':')[1]);
    react_type = "heep";


  }
  
  //Do D(e,e'p)n
  else if (input==2){

    //Set Input Parameter File Name
    inputCutFileName="set_deep_cuts.inp";
    
    //Read Necessary Input Parameters to Run Analysis
    pm_set = stoi(split(FindString("pm_setting", inputCutFileName)[0], ':')[1]);
    theory = trim(split(FindString("theory", inputCutFileName)[0], ':')[1]);
    model = trim(split(FindString("model", inputCutFileName)[0], ':')[1]);
    dataSet = stoi(split(FindString("data_set", inputCutFileName)[0], ':')[1]);
    runlist_name = Form("runlists/d2_pm%i_set%i.dat", pm_set, dataSet);
    run_simc_flag = stoi(split(FindString("RUN_SIMC", inputCutFileName)[0], ':')[1]);
    run_data_flag = stoi(split(FindString("RUN_DATA", inputCutFileName)[0], ':')[1]);
    rad_corr_flag = stoi(trim(split(FindString("rad_corr_flag", inputCutFileName)[0], ':')[1])); 
    single_run_flag = stoi(split(FindString("single_run_flag", inputCutFileName)[0], ':')[1]);
    react_type = "deep";
    
    
    ifs.close();
  }

  
  //==================================== D  A  T  A ============================================
  if(run_data_flag){
    
    
    if(single_run_flag){      
      cout << "=====Analyzing DATA: Single Run=====" << endl;
      //create instance of the 'analyze' class, called a1
      analyze a1(-1, "SHMS", "data", react_type);   //Setting run = -1 will trigger a flag in analyze.C that will read the single run file
                                                    //created by the user in the set_heep(deep).inp file

      //call method to run data analysis. This method call all necessary methods to analyze data.(See analyze.C)
      a1.run_data_analysis();
    }
    
    else
      {
	//Open Data Run List
	ifs.open(runlist_name);
	cnt=0;
	Qnorm_flag = 0;
	//Read Run List
	while(getline(ifs, line))
      {
	//convert string to integer
	run = stoi(line);                               
	
	cnt++;  //line counter
	if(get_total_lines(runlist_name)==cnt){
	  Qnorm_flag=1;
	  cout << "Reached Final Run: " << run << endl;
	}
	
	if(react_type=="heep"){
	  cout << "==================================" << endl;
	  cout << Form("Analyzing H(e,e'p) DATA: Run %i ",  run) << endl;
	  cout << "==================================" << endl;
	}
	else if(react_type=="deep"){
	  cout << "==================================" << endl;
	  cout << Form("Analyzing D(e,e'p)n DATA: Run %i ", run) << endl;
	  cout << Form("Pm: %d MeV || Set: %d", pm_set, dataSet) << endl;
	  cout << "==================================" << endl;
	}
	
	//create instance of the 'analyze' class, called a1
	analyze a1(run, "SHMS", "data", react_type);
	
	//call method to run data analysis. This method call all necessary methods to analyze data.(See analyze.C)
	a1.run_data_analysis(Qnorm_flag);
	
      }
	
	//Close Run List file
	ifs.close();
      }
    
  }
  
  //============================================================================================



  //======================================== S I M C ===========================================

  if(run_simc_flag)
    {
	
      if (react_type=="heep"){

	if(single_run_flag){      
	  cout << "=====Analyzing SIMC H(e,e'p): Single Run=====" << endl;

	  //create instance of the 'analyze' class, called a1
	  analyze a1(-1, "SHMS", "simc", react_type);   //Setting run = -1 will trigger a flag in analyze.C that will read the single run file
	                                                //created by the user in the set_heep(deep).inp file
	  
	  //call method to run data analysis. This method call all necessary methods to analyze data.(See analyze.C)
	  a1.run_simc_analysis();
	}

	else{
	  //Open H(e,e'p) Elasic Run List
	  ifs.open(runlist_name);
	  
	  //Read Run List
	while(getline(ifs, line))
	  {	
	    //convert string to integer
	    run = stoi(line);
	    
	    cout << "==================================" << endl;
	    cout << Form("Analyzing H(e,e'p) SIMC: Run %i", run) << endl;
	    cout << "==================================" << endl;
	    
	    //create instance of the 'analyze' class, called a1
	    analyze a1(run, "SHMS", "simc", react_type);
	    
	    //call method to run simc analysis. This method call all necessary methods to analyze simc.(See analyze.C)
	    //rad_corr_flag| 0: do NOT do radiative corrections,  1: do radiatie corrections (controlled from input file) 
	    a1.run_simc_analysis(rad_corr_flag);   
	    
	    
	  }
	
	ifs.close();
	}
      
      } //end H(e,e'p)
      
      else if(react_type=="deep"){

	if(single_run_flag){     

	  cout << "=====Analyzing SIMC D(e,e'p)n: Single Run=====" << endl;

 
	  //create instance of the 'analyze' class, called a1
	  analyze a1(-1, "SHMS", "simc", react_type);   //Setting run = -1 will trigger a flag in analyze.C that will read the single run file
	                                                //created by the user in the set_heep(deep).inp file
	  
	  //call method to run data analysis. This method call all necessary methods to analyze data.(See analyze.C)
	  a1.run_simc_analysis();
	}
	 
	else{
	  cout << "==================================" << endl;
	  cout << "Analyzing D(e,e'p)n SIMC " << endl;
	  cout << Form("Pm: %d MeV || Set: %d", pm_set, dataSet) << endl;
	  cout << Form("Theory: %s || Model: %s", theory.c_str(), model.c_str()) << endl;
	  cout << "==================================" << endl;
	  
	  //get the 1st run from the runlist (all simc needs is to know the kinematic setting 
	  //which can get from any run in the runlist.)
	  ifs.open(runlist_name);
	  getline(ifs, line);
	  run = stoi(line); 
	  
	  //create instance of the 'analyze' class, called a1
	  analyze a1(run, "SHMS", "simc", react_type);
	  
	  //call method to run simc analysis. This method call all necessary methods to analyze simc.(See analyze.C)
	  //rad_corr_flag| 0: do NOT do radiative corrections,  1: do radiatie corrections (controlled from input file) 
	  a1.run_simc_analysis(rad_corr_flag);
	  
	  

	}
	  
      }
      
    }
  
  //============================================================================================
  

  
  
  
  
  return 0;
}
