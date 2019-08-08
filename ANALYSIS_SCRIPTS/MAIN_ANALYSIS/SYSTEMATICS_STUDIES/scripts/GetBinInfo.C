//code to get bin information and store it in txt file

void GetBinInfo(TH1F *h1, string ofname="default_bin_info.txt", string comments="")
{


  
  Int_t Nbins = h1->GetNbinsX();  //total number of bins
  Int_t binw = h1->GetBinWidth(1);      //bin width

  //Create Empty Vectors in which to store bin info
  vector<Int_t> bin_arr;              //bin number id: 
  vector<Double_t> xbin_arr;          //x-value of bin at bin-center
  vector<Double_t> xlow_arr;         //x-value at low edge of bin center         
  vector<Double_t> xup_arr;        //x-value at up edge of bin center
  vector<Double_t> binContent_arr;    //bin content
  vector<Double_t> binContentErr_arr; //error in bin content
  
  //Loop over all bins (exclude underflow/overflow bins)
  for(int ib=1; ib<=Nbins; ib++)
    {
      bin_arr.push_back(ib);
      xbin_arr.push_back( h1->GetXaxis()->GetBinCenter(ib) );
      binContent_arr.push_back( h1->GetBinContent(ib) );
      binContentErr_arr.push_back( h1->GetBinError(ib) );
      xlow_arr.push_back( h1->GetXaxis()->GetBinLowEdge(ib));
      xup_arr.push_back(  h1->GetXaxis()->GetBinUpEdge(ib));

    }

  ofstream ofile;
  ofile.open(ofname);
  ofile << Form("#1D Bin Information for %s", ofname.c_str()) << endl; 
  ofile << "#bin: bin id \n#xbin: xvalue at bin center \n#xlow: xvalue at lower bin edge \n#xup: xvalue at upper bin edge \n#binw: bin width \n#nbins: total number of bins \n" << endl; 
  ofile << "" << endl;
  ofile << Form("#comments: %s", comments.c_str()) << endl;
  ofile << "" << endl;

  ofile << "#!bin[i,0]/   xbin[f,1]/    xlow[f,2]/    xup[f,3]/    binCont[f,2]/   binCont_err[f,3]/  binw[i,4]/   nbins[i, 5]/" << endl;
  
  for(int ib=1; ib<=Nbins; ib++)
    {
      ofile << bin_arr[ib-1] << setw(15) << xbin_arr[ib-1] << setw(15) << xlow_arr[ib-1] << setw(15) << xup_arr[ib-1] << setw(15) << binContent_arr[ib-1] << setw(15) << binContentErr_arr[ib-1] << setw(15) << binw << setw(15) << Nbins << endl;
    }

  ofile.close();
  

}
