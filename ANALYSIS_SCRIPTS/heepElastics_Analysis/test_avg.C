void test_avg()
{

  Double_t sum = 0;
  int total = 0;

  for(int i=0; i<10; i++)
    {
      sum =  sum + i;
      total = total + 1;
      
      cout << "sum = " << sum << endl;
      cout << "total = " << total << endl;

      cout << "avg = " << sum /  total << endl;	
	
    }

}
