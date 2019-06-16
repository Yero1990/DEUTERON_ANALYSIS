#define q2_avgkin_thnq_pm_cxx
#include "q2_avgkin_thnq_pm.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TRfn.h"
#include "THaRfn.h"
#include "TFLcut.h"
#include "TFWcut.h"


void q2_avgkin_thnq_pm::Loop(Long64_t n_events)
{
  
  
  // output files
  // default file name

  // all variables in GeV
  
  // create histograms
  // setup histograms and cuts here
  // some local variables
  
  Double_t pi = 3.141592654;
  Double_t dtr = pi/180.;
  Double_t MP = 0.938272; //GeV 
  Double_t MD = 1.87561; //GeV
  Double_t MN = 0.939566; //GeV
  
  // unit conversions
  Double_t mr2r = 1.e-3;
  Double_t cm2m = 1.e-2;
  Double_t p2f = 1.e-2;
  

  //-----------------------------------------------
  // open output file
  TFile *out_file = new TFile("q2_avgkin_thnq_pm.root","RECREATE");
  //-----------------------------------------------


  //-----------------------------------------------
  // get setup for this analysis
  //-----------------------------------------------
  cout << "Start setup " << endl;
  //-----------------------------------------------
  // setup  
  //-----------------------------------------------
  // rfn definitions
  #include "./root/setup.C"
  //-----------------------------------------------
  // cut values specific for kinematics, values are copies from steering
  // program
  #include "kin_cuts.C"
  //-----------------------------------------------
  // get histogram definitions
  cout << "Start histo_defs " << endl;
  //--------------- --------------------------------
  #include "histo_defs.C"
  //-----------------------------------------------
  //  common cut values
  #include "common_cut_parameters.C"

  // get cut definitions
  cout << "Start TFcut_defs " << endl;
  //-----------------------------------------------
  #include "TFcut_defs.C"
  //-----------------------------------------------

  //----------------------------------------------------
  
  //  Double_t theta_sp =18.9121; 
  theta_sp *= dtr;
  //  theta_spr *= -dtr;
  Double_t react_z = 0.;
  Double_t react_y = 0.;
  Double_t react_zr = 0.;
  Double_t react_yr = 0.;
  Double_t zsp = 0.;
  Double_t ysp = 0.;
  Double_t zspr = 0.;
  Double_t yspr = 0.;
  Double_t tan_theta_sp = tan(theta_sp);
  Double_t cos_theta_sp = cos(theta_sp);
  Double_t sin_theta_sp = sin(theta_sp);

  //  Double_t tan_theta_spr = tan(theta_spr);
  //  Double_t cos_theta_spr = cos(theta_spr);
  //  Double_t sin_theta_spr = sin(theta_spr);



 //----------------------------------------------------
  
  // this is really import and needs to agree with the settings
  // in the SIMC input files
  
  // drift distance to first cut
  // dl and dr from cut_definitions.C
  
  Double_t dl1 = dl;
  Double_t dl2 = dl+dc;
  
  Double_t dr1 = dr;
  Double_t dr2 = dr+dc;
   // cut output variables
  Int_t c_rfn_e = 0;
  Int_t c_rfn_p = 0;
  Int_t c_rfn = 0;
  Int_t c_rfn_count = 0;
  
  Int_t c_zdiff = 1;
  Int_t c_reactz_e = 0;
  Int_t c_reactz1_e = 0;
  Int_t c_reactz2_e = 0;
  Int_t c_reactz_p = 0;
  Int_t c_reactz1_p = 0;
  Int_t c_reactz2_p = 0;
  Int_t c_target = 0;
  Int_t c_target1 = 0;
  Int_t c_target2 = 0;
  
  Int_t c_s_l1 = 0;
  Int_t c_s_l2 = 0;
  
  Int_t c_s_r1 = 0;
  Int_t c_s_r2 = 0;
  Int_t c_W   = 0;
  Int_t c_solid_l = 0;
  Int_t c_solid_r = 0;
  Int_t c_solid = 0;
  Int_t c_dpcut = 0;
  Int_t c_accept = 0;
  Int_t c_fid = 0;
  Int_t c_em = 0;
  Int_t c_Q2 = 0;
  Int_t c_xbj = 0;
  Int_t c_pm = 0;

  cout << "Start Analysis Loop " << endl;
  
  if (fChain == 0) return;

  nevents =fChain-> GetEntries();
  Long64_t nentries = fChain->GetEntriesFast();
  if (n_events <= 0){
    n_events = nentries;
  }
  else{
      n_events = min(n_events, nentries);
    }
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<n_events;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if ((jentry%10000) == 0) {
          cout << "Event : " << jentry << endl;
    }
    
     if (ientry < 0) {
           cout << "analyzed  " << jentry << " events " << endl;
       break;
     }
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     // put my stuff here
     
     // some additional kinematic values
     // calculate x_bj and theta_nq
     Double_t X = Q2_t/(2.*MP*nu);

     Pm = TMath::Sqrt(Pmx*Pmx +Pmy*Pmy +Pmz*Pmz);
     // calculate final proton momentum (from reconstructed quantities)
     // neutron energy
       Double_t En = sqrt(Pm*Pm + MN*MN);


     //   Double_t En = sqrt(Pm*Pm);  // for hydrogen 

     // proton momentum
        Double_t Pf2 = pow((nu + MD - En), 2) - MP*MP; 
   
     //  Double_t Pf2 = pow((nu + MD), 2) - MP*MP;    

        Double_t Pf = sqrt(Pf2);     
     // electron kinematics
     Double_t E_f = E_inc - nu;
      Double_t th_e = sqrt(Q2_t/(4.*E_inc*E_f));
     // if (th_e>1 && -1<th_e) continue;
       // Double_t theta_e = 2.*asin(sqrt(Q2/(4.*E_inc*E_f)));
       Double_t theta_e = 2.*asin(th_e);
     
   
     // need to calculate the recoil angle (angle of the neutron)
     // PmPar (component parallel to q), Pm missing momentum
     // - sign since Pm points in the opposite direction of the neutron momentum
     // ----------------------------------------------------------------------
     // calculate alpha 
     //Pm = TMath::Sqrt(Pmx*Pmx +Pmy*Pmy +Pmz*Pmz);
     // z-component of neutron momentum
     Double_t pz_n = -PmPar;
     // perp component in GeV/c
     Double_t pt = sqrt(Pm*Pm - PmPar*PmPar);
     Double_t p_n_minus = En - pz_n;
     Double_t alpha = p_n_minus/MN;
     Double_t Pt_mevc = pt*1000.;
     // ----------------------------------------------------------------------
     
     Double_t cth_nq = -PmPar/Pm ;
     // bad kinematics
     if ( abs(cth_nq)>1. ) continue;
     Double_t theta_nq = acos(cth_nq)/dtr;

     // check alpha calculation
     //Double_t pzn = Pm*cth_nq;
     //Double_t E_n = sqrt(Pm*Pm + MN*MN);
     //Double_t alpha_c = (E_n - pzn)/MN;
     
     //cout << "pz_n = " << pz_n << " pzn =  " << pzn << endl;
     //cout << "E_n = " << E_n << " En = " << En << endl;
     //cout << "alpha = " << alpha << " alpha_c = " << alpha_c << endl;


     // Normfac SIMC normalization factor for counts
     // nevents : # events per set MUST be the same for all
     // charge_factor real charge in units of mC

       Double_t WEIGHT = Weight*Normfac*charge_factor/(1000*nevents);
     // for phase space calcuationg the weight is modified as 

     //  WEIGHT = WEIGHT/(sigcc*Jacobian);


     // cout << "Weight==" <<Weight<< " " << Normfac<<" " <<endl;
     // Double_t WEIGHT = 1.0;
       Double_t M_inv = W*1000.;
       
       Double_t E_miss = Em*1000;
       Double_t P_miss = Pm*1000;
       
      // transform variables from SIMC to analyzer form 

      Double_t Spec_l_th_tg = e_xptar;
      Double_t Spec_l_ph_tg = e_yptar;
      Double_t Spec_l_y_tg = e_ytar * cm2m;
      Double_t Spec_l_dp = e_delta * p2f;

      Double_t Spec_r_th_tg = h_xptar ;
      Double_t Spec_r_ph_tg = h_yptar ;
      Double_t Spec_r_y_tg = h_ytar * cm2m ;
      Double_t Spec_r_dp = h_delta * p2f;

      //----------------------------------------------------
      // need to calculate reactz
      // make sure the correct parameters are in the parameter file

      Double_t zsp = -Spec_l_y_tg/(Spec_l_ph_tg + tan_theta_sp);
      Double_t ysp = tan_theta_sp*zsp;
      // rotate back into beam system
      react_z = cos_theta_sp*zsp + sin_theta_sp*ysp;
      react_y = -sin_theta_sp*zsp + cos_theta_sp*ysp;

      Double_t Spec_l_reactz = react_z;
      //----------------------------------------------------
      
      // setting target length from proton side 
      //      Double_t zspr = -Spec_r_y_tg/(Spec_r_ph_tg + tan_theta_spr);
      //  Double_t yspr = tan_theta_spr*zspr;
      // rotate back into beam system
      // react_zr = cos_theta_spr*zspr + sin_theta_spr*yspr;
      // react_yr = -sin_theta_spr*zspr + cos_theta_spr*yspr;
      //  Double_t Spec_r_reactz = react_zr;

      // solid angle
      // for electron and proton

      Double_t xs_l1 = Spec_l_th_tg * dl1;
      Double_t ys_l1 = Spec_l_ph_tg * dl1 + Spec_l_y_tg;

      Double_t xs_l2 = Spec_l_th_tg * dl2;
      Double_t ys_l2 = Spec_l_ph_tg * dl2 + Spec_l_y_tg;

      Double_t xs_r1 = Spec_r_th_tg * dr1;
      Double_t ys_r1 = Spec_r_ph_tg * dr1 + Spec_r_y_tg;

      Double_t xs_r2 = Spec_r_th_tg * dr2;
      Double_t ys_r2 = Spec_r_ph_tg * dr2 + Spec_r_y_tg;

      // calculate r-values

      Double_t re = rfn_l_o->Eval(Spec_l_y_tg, Spec_l_dp, Spec_l_th_tg , Spec_l_ph_tg);
      Double_t rp = rfn_r_o->Eval(Spec_r_y_tg, Spec_r_dp, Spec_r_th_tg , Spec_r_ph_tg);

      // new
      c_rfn_e = Rfn_e_C.Eval(re);
      c_rfn_p = Rfn_p_C.Eval(rp);

      // combined cut

      c_rfn = c_rfn_e && c_rfn_p;
      c_rfn_count = Rfn_C.Eval(c_rfn); // this is only for counting
   
      // react-z cuts (vertex location)
      c_reactz_e = Reactz_C.Eval(Spec_l_reactz);
      c_reactz1_e = Reactz1_C.Eval(Spec_l_reactz);
      c_reactz2_e = Reactz2_C.Eval(Spec_l_reactz);

      //    c_reactz_p = Reactz_Cr.Eval(Spec_r_reactz);

      // general target length cut
       c_target = c_reactz_e ;
      // c_target =  c_reactz_p;
      c_target1 = c_reactz1_e;
      c_target2 = c_reactz2_e;
      // z-diff cut applied but not really i need it 

      //        c_zdiff =  Zdiff_C.Eval(Spec_r_reactz -Spec_l_reactz);

      // evaluate solid angle cuts as in mceep

      c_s_l1 = Xsl1_C.Eval(xs_l1) && Ysl1_C.Eval(ys_l1);
      c_s_l2 = Xsl2_C.Eval(xs_l2) && Ysl2_C.Eval(ys_l2);

      c_s_r1 = Xsr1_C.Eval(xs_r1) && Ysr1_C.Eval(ys_r1);
      c_s_r2 = Xsr2_C.Eval(xs_r2) && Ysr2_C.Eval(ys_r2);
      
      S1l_C.Eval(c_s_l1);
      S2l_C.Eval(c_s_l2);

      S1r_C.Eval(c_s_r1);
      S2r_C.Eval(c_s_r2);
      
      c_solid_l = c_s_l1 && c_s_l2;
      c_solid_r = c_s_r1 && c_s_r2;

      c_solid = c_solid_l && c_solid_r;

      // fiducial bin
      c_em   = Emiss_C.Eval(E_miss);
      c_pm   = Pmiss_C.Eval(P_miss);
      c_xbj  = Xbj_C.Eval(X); 
      c_Q2   = Qsq_C.Eval(Q2_t);
      
      //  c_fid = c_em && c_pm && c_Q2; // fiducial bin (no cut on x_bj)
         c_fid = c_em && c_Q2; // fiducial bin (no cut on x_bj)
      //   c_fid = c_Q2; // fiducial bin (no cut on x_bj)

      Fid_C.Eval(c_fid); // for book keeping

      // momentum acceptance cuts
      Dpe_C.Eval(Spec_l_dp);
      Dpp_C.Eval(Spec_r_dp);

      // this is the acceptance cut
      c_dpcut = Dpe_C.Cut && Dpp_C.Cut ;
      c_accept = c_solid && c_dpcut ;

      Accept_C.Eval(c_accept); // for book keeping
      
      // for angular distribution
      // 1d histo
      if (c_fid && c_pm && c_accept && c_rfn && c_target ){  // fiducial bin and acceptance cut coincidences

	histo_1d_yield->Fill(theta_nq, WEIGHT);
	histo_1d_counts->Fill(theta_nq, P_miss);
        avg_1d_q3->Fill(theta_nq, WEIGHT*q); 
        avg_1d_omega->Fill(theta_nq, WEIGHT*nu);
        avg_1d_theta_pq->Fill(theta_nq, WEIGHT*theta_pq);
        avg_1d_th_e_tg->Fill(theta_nq, WEIGHT*Spec_l_th_tg);
        avg_1d_ph_e_tg->Fill(theta_nq, WEIGHT*Spec_l_ph_tg);
        avg_1d_theta_e->Fill(theta_nq, WEIGHT*theta_e);
	avg_1d_theta_p->Fill(theta_nq, WEIGHT*theta_p);
	avg_1d_th_p_tg->Fill(theta_nq, WEIGHT*Spec_r_th_tg);
        avg_1d_ph_p_tg->Fill(theta_nq, WEIGHT*Spec_r_ph_tg);
       	avg_1d_Ein->Fill(theta_nq, WEIGHT*E_inc);
        avg_1d_pf->Fill(theta_nq, WEIGHT*Pf);
        avg_1d_ef->Fill(theta_nq, WEIGHT*E_f);
	avg_1d_pmiss->Fill(theta_nq, WEIGHT*P_miss);
	avg_1d_Q2->Fill(theta_nq, WEIGHT*Q2_t);
        avg_1d_ph_pq->Fill(theta_nq, WEIGHT*phi_pq);
        avg_1d_cph_pq->Fill(theta_nq, WEIGHT*TMath::Cos(phi_pq));
        avg_1d_sph_pq->Fill(theta_nq, WEIGHT*TMath::Sin(phi_pq));
	avg_1d_th_nq->Fill(theta_nq, WEIGHT*theta_nq);
	avg_1d_alpha->Fill(theta_nq, WEIGHT*alpha);
	avg_1d_pt->Fill(theta_nq, WEIGHT*Pt_mevc);

      }
      // 2d histos
      if (c_fid && c_accept && c_rfn && c_target ){  // fiducial bin and acceptance cut coincidences
	
	histo_yield->Fill(theta_nq, P_miss, WEIGHT);
	histo_counts->Fill(theta_nq, P_miss);
        avg_q3->Fill(theta_nq, P_miss, WEIGHT*q); 
        avg_omega->Fill(theta_nq, P_miss, WEIGHT*nu);
        avg_theta_pq->Fill(theta_nq, P_miss, WEIGHT*theta_pq);
        avg_th_e_tg->Fill(theta_nq, P_miss, WEIGHT*Spec_l_th_tg);
        avg_ph_e_tg->Fill(theta_nq, P_miss, WEIGHT*Spec_l_ph_tg);
        avg_theta_e->Fill(theta_nq, P_miss, WEIGHT*theta_e);
	avg_theta_p->Fill(theta_nq, P_miss, WEIGHT*theta_p);
	avg_th_p_tg->Fill(theta_nq, P_miss, WEIGHT*Spec_r_th_tg);
        avg_ph_p_tg->Fill(theta_nq, P_miss, WEIGHT*Spec_r_ph_tg);
       	avg_Ein->Fill(theta_nq, P_miss, WEIGHT*E_inc);
        avg_pf->Fill(theta_nq, P_miss, WEIGHT*Pf);
        avg_ef->Fill(theta_nq, P_miss, WEIGHT*E_f);
	avg_pmiss->Fill(theta_nq, P_miss, WEIGHT*P_miss);
	avg_Q2->Fill(theta_nq, P_miss, WEIGHT*Q2_t);
        avg_ph_pq->Fill(theta_nq, P_miss, WEIGHT*phi_pq);
        avg_cph_pq->Fill(theta_nq, P_miss, WEIGHT*TMath::Cos(phi_pq));
        avg_sph_pq->Fill(theta_nq, P_miss, WEIGHT*TMath::Sin(phi_pq));
	avg_th_nq->Fill(theta_nq, P_miss, WEIGHT*theta_nq);
	avg_alpha->Fill(theta_nq, P_miss, WEIGHT*alpha);
	avg_pt->Fill(theta_nq, P_miss, WEIGHT*Pt_mevc);

      }
      
  }

  cout << " ........loop ends here...."<<endl;

  // 1d calc

  avg_1d_q3->Divide(avg_1d_q3, histo_1d_yield);
  avg_1d_omega->Divide(avg_1d_omega, histo_1d_yield);
  avg_1d_theta_pq->Divide(avg_1d_theta_pq, histo_1d_yield);
  avg_1d_th_e_tg->Divide(avg_1d_th_e_tg,histo_1d_yield);
  avg_1d_ph_e_tg->Divide(avg_1d_ph_e_tg,histo_1d_yield);
  avg_1d_theta_e->Divide(avg_1d_theta_e, histo_1d_yield);
  avg_1d_theta_p->Divide(avg_1d_theta_p, histo_1d_yield);
  avg_1d_th_p_tg->Divide(avg_1d_th_p_tg,histo_1d_yield);
  avg_1d_ph_p_tg->Divide(avg_1d_ph_p_tg,histo_1d_yield);
  avg_1d_Ein->Divide( avg_1d_Ein, histo_1d_yield);
  avg_1d_pf->Divide( avg_1d_pf, histo_1d_yield);
  avg_1d_ef->Divide( avg_1d_ef, histo_1d_yield);
  avg_1d_pmiss->Divide( avg_1d_pmiss, histo_1d_yield);
  avg_1d_Q2->Divide( avg_1d_Q2, histo_1d_yield);

  avg_1d_ph_pq->Divide(avg_1d_ph_pq, histo_1d_yield);
  avg_1d_cph_pq->Divide(avg_1d_cph_pq, histo_1d_yield);
  avg_1d_sph_pq->Divide(avg_1d_sph_pq, histo_1d_yield);

  avg_1d_th_nq->Divide(avg_1d_th_nq, histo_1d_yield);

  avg_1d_alpha->Divide(avg_1d_alpha, histo_1d_yield);
  avg_1d_pt->Divide(avg_1d_pt, histo_1d_yield);

  // 2d calc

  avg_q3->Divide(avg_q3, histo_yield);
  avg_omega->Divide(avg_omega, histo_yield);
  avg_theta_pq->Divide(avg_theta_pq, histo_yield);
  avg_th_e_tg->Divide(avg_th_e_tg,histo_yield);
  avg_ph_e_tg->Divide(avg_ph_e_tg,histo_yield);
  avg_theta_e->Divide(avg_theta_e, histo_yield);
  avg_theta_p->Divide(avg_theta_p, histo_yield);
  avg_th_p_tg->Divide(avg_th_p_tg,histo_yield);
  avg_ph_p_tg->Divide(avg_ph_p_tg,histo_yield);
  avg_Ein->Divide( avg_Ein, histo_yield);
  avg_pf->Divide( avg_pf, histo_yield);
  avg_ef->Divide( avg_ef, histo_yield);
  avg_pmiss->Divide( avg_pmiss, histo_yield);
  avg_Q2->Divide( avg_Q2, histo_yield);

  avg_ph_pq->Divide(avg_ph_pq, histo_yield);
  avg_cph_pq->Divide(avg_cph_pq, histo_yield);
  avg_sph_pq->Divide(avg_sph_pq, histo_yield);

  avg_th_nq->Divide(avg_th_nq, histo_yield);

  avg_alpha->Divide(avg_alpha, histo_yield);
  avg_pt->Divide(avg_pt, histo_yield);

  // save histograms
  // 1d calc
  out_file->cd();
  
  histo_1d_yield->Write();
  histo_1d_counts->Write();
  avg_1d_q3->Write();
  avg_1d_omega->Write();
  avg_1d_theta_pq->Write();
  avg_1d_th_e_tg->Write();
  avg_1d_ph_e_tg->Write();
  avg_1d_theta_e->Write();
  avg_1d_theta_p->Write();
  avg_1d_th_p_tg->Write();
  avg_1d_ph_p_tg->Write();
  avg_1d_Ein->Write();
  avg_1d_pf->Write();
  avg_1d_ef->Write();
  avg_1d_pmiss->Write();
  avg_1d_Q2->Write();

  avg_1d_ph_pq->Write();
  avg_1d_cph_pq->Write();
  avg_1d_sph_pq->Write();

  avg_1d_th_nq->Write();

  avg_1d_alpha->Write();
  avg_1d_pt->Write();

  // 2d calc
  histo_yield->Write();
  histo_counts->Write();

  avg_q3->Write();
  avg_omega->Write();
  avg_theta_pq->Write();
  avg_th_e_tg->Write();
  avg_ph_e_tg->Write();
  avg_theta_e->Write();
  avg_theta_p->Write();
  avg_th_p_tg->Write();
  avg_ph_p_tg->Write();
  avg_Ein->Write();
  avg_pf->Write();
  avg_ef->Write();
  avg_pmiss->Write();
  avg_Q2->Write();

  avg_ph_pq->Write();
  avg_cph_pq->Write();
  avg_sph_pq->Write();

  avg_th_nq->Write();

  avg_alpha->Write();
  avg_pt->Write();

   cout << "Cuts used:" << endl;
   
   // print cut statistics
   Reactz_C.Print();Reactz_C.PrintStat();
   Dpe_C.Print();Dpe_C.PrintStat();
   Dpp_C.Print();Dpp_C.PrintStat();
   Fid_C.Print();Fid_C.PrintStat();
   Accept_C.Print();Accept_C.PrintStat();

   out_file->Close();
   return;
}




