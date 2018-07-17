void run_multiple()
{


  TString path = "../SCRIPTS/HMS/";
  TSrring replay_CMD = ""
  
 
  for (int runNUM = 3306; runNUM<=3340; runNUM++ )
    {
     
      gSystem->Exec(Form("./run_full_deep.sh %d", runNUM));
    
    }

}
