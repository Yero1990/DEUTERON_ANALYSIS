
string getString(char x)
{
  
  //method to convert a cvaracter to a string

  string s(1,x);
  return s;
}

vector <string> split(string str, char del=':')
{

  //method to split a string into a vetor of strings separated by a delimiter del
  //Returns a vector of strings, whose elements are separated by the delimiter del.

  using namespace std;

  string temp1, temp2;

  vector <string> parse_word;
  int del_pos;  //delimiter position
    
    for (int i=0; i < str.size(); i++){

      //Get position of delimiter
      if(str[i]==del){
	del_pos = i;
      }

    }

    for (int i=0; i < str.size(); i++){

      //append char to a string for char left of the delimiter
      if(i<del_pos){
	temp1.append(getString(str[i]));
      }      

      //append char to a string for char right of the delimiter
      else if(i>del_pos){
	temp2.append(getString(str[i]));
      }

    }
    parse_word.push_back(temp1);
    parse_word.push_back(temp2);
    
    return parse_word;
}

vector <string> FindString(string keyword, string filename)
{

  //Method: Finds string keyword in a given txt file. 
  //Returns the lines (stored in a vector) in which the keyword was found. Lines are counted from 0. 
  
  ifstream ifile(filename);

  vector <string> line_found; //vector to store in which lines was the keyword found
  
  int line_cnt = 0;
  string line;                  //line string to read
  
  int found = -1; //position of found keyword

  while(getline(ifile, line))
    {
        
      found = line.find(keyword);
      
      if(found<0||found>1000){found=-1;} //not found

      if(found!=-1){
	
	line_found.push_back(line);
	

      } //end if statement
    
      line_cnt++;
    } //end readlines



  return line_found;
}//end test.C


//Usage of methods:
/*
  First, use the FindString() methods to get where the line(s) with the specified keywords are.
  Second, Read the lines of such file, and require the specified lines to be found:
  Third, in such found line, use the split() method to split the line into a parsed vector separated by the delimiter
  Fourth: There might be numbers which you want to convert from strings to ints or double;  Use the C++ ,methods stoi() or stod()  
*/


//Apply Above Methods


int main()
{

  //Read Report File
  string filename = "example.txt";
  ifstream ifile(filename);

  // # of lines found with the string in question (starting at 1)
  int tot_lines = FindString("pHMS Angle", filename).size();
  
  //Get string of line found of the firt occurrence 
  string line_found = FindString("pHMS Angle", filename).at(0);
  
  //Split string into an array of strings using a delimiter
  split(line_found, ':')[0];

  split(split(line_found, ':')[1], 'd')[0];

  }

