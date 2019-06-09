int get_total_lines(string rlist="")
{

  //Open a file and replace a string 
  fstream fs;
  ofstream ofs;
  ifstream ifs;

  string line;
  int cnt=0;

  //input runlist
  ifs.open(rlist);


  while(getline(ifs, line))
    {
      cnt++;
  
      //cout << "line counter: " << cnt << endl;

    }

  return cnt;
}

int main()
{
  cout << get_total("runlists/d2_pm580_set1.dat") << endl;;

}
