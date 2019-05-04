#include <iostream>
#include <string>
#include <vector>

#include "program4.h"
#include "gtest/gtest.h"

using namespace std;
using std::string;
using std::vector;

void printCodes(std::vector<CCode> codes){
  for(int i = 0;i<codes.size();++i){
    std::cout<<"Symbol: "<<codes[i].c
             <<" -> Code: "<<codes[i].code<<std::endl;
  }
}

bool prefixFreeCode(vector<CCode>& codes){
  for(int i = 0; i<codes.size()-1; ++i){
    for(int j =i+1;j<codes.size();++j){
      int min_l = std::min( codes[i].code.length(),
                            codes[j].code.length() );
      int matches = 0;
      for ( ; matches<min_l; ++matches){
        if(   codes[i].code.at(matches) 
           != codes[j].code.at(matches) ) break;
      }
      if (matches == min_l) return false;
    }
  }
  return true;
}

void codeLengthOK(vector<CCode>& codes, char c, int expected){
  bool found = false;
  for (std::vector<CCode>::iterator it = codes.begin();it!=codes.end();++it){
    if(it->c == c){
       found = true;
       ASSERT_EQ(it->code.length(), expected)
              <<"Unexpected code length for " 
              <<it->c<<std::endl;
    }
  }
  ASSERT_TRUE(found)<<"Did not find character "<<c
                    <<" in codes"<<std::endl;
}

//simple test 
TEST(HuffTree, basic){
  std::cout<<"Basic example from slides:"<<std::endl;
  vector<CFreq> cfs;
  cfs.push_back(CFreq('A',0.35));
  cfs.push_back(CFreq('B',0.10));
  cfs.push_back(CFreq('C',0.20));
  cfs.push_back(CFreq('D',0.20));
  cfs.push_back(CFreq('_',0.15));

  vector<CCode> codes = getHuffCodes(cfs);
  ASSERT_EQ(codes.size(),cfs.size())<<"Your number of codes, codes.size(), is not the same size as the input frequencies."<<std::endl; 
  
  codeLengthOK(codes,'A',2);
  codeLengthOK(codes,'B',3);
  codeLengthOK(codes,'C',2);
  codeLengthOK(codes,'D',2);
  codeLengthOK(codes,'_',3);


  printCodes(codes); 
  
  bool prefixFree =  prefixFreeCode(codes);

 
  std::cout<<"The code is prefix-FREE is : " 
           << (prefixFree ? "true ": "false ")
           << std::endl;

  ASSERT_TRUE(prefixFree)<<"Your code was not PREFIX-FREE"<<std::endl;   
}

// longer test
TEST(HuffTree, larger10){
  std::cout<<"longer example"<<std::endl;
  vector<CFreq> cfs;
  cfs.push_back(CFreq('A',0.14));
  cfs.push_back(CFreq('B',0.105));
  cfs.push_back(CFreq('C',0.115));
  cfs.push_back(CFreq('D',0.12));
  cfs.push_back(CFreq('E',0.20));
  cfs.push_back(CFreq('F',0.01));
  cfs.push_back(CFreq('G',0.09));
  cfs.push_back(CFreq('H',0.05));
  cfs.push_back(CFreq('I',0.13));
  cfs.push_back(CFreq('J',0.04));


  vector<CCode> codes = getHuffCodes(cfs);
  ASSERT_EQ(codes.size(),cfs.size())<<"Your number of codes, codes.size(), is not the same size as the input frequencies."<<std::endl; 
  
  codeLengthOK(codes,'A',3);
  codeLengthOK(codes,'B',3);
  codeLengthOK(codes,'C',3);
  codeLengthOK(codes,'D',3);
  codeLengthOK(codes,'E',2);
  codeLengthOK(codes,'F',6);
  codeLengthOK(codes,'G',4);
  codeLengthOK(codes,'H',5);
  codeLengthOK(codes,'I',3);
  codeLengthOK(codes,'J',6);


  printCodes(codes); 
  
  bool prefixFree =  prefixFreeCode(codes);

 
  std::cout<<"The code is prefix-FREE is : " 
           << (prefixFree ? "true ": "false ")
           << std::endl;

  ASSERT_TRUE(prefixFree)<<"Your code was not PREFIX-FREE"<<std::endl;   
}
