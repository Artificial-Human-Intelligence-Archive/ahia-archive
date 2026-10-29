#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
using namespace std;

uint64_t buf;int b=0;

string Bi(int O,int mW){if(O==0)return string(mW,'0');string d;d.reserve(32);
while(O>0){d.push_back('0'+(O&1));O>>=1;}reverse(d.begin(), d.end());
int pad=(mW-(d.length()%mW))%mW;if(pad)d.insert(0,pad,'0');return d;};

int Z(const string& B){int v=0;for(char c:B){v=(v<<1)|(c-'0');}return v;};

void S(ofstream& fis,int ch){fis.put(static_cast<char>(ch));};

int C(ifstream& fis){int ch; ch=fis.get(); if(ch==EOF)return -1; else return ch;};

void pB(int B){if(B<0||B>255)return;buf=(buf<<8)|(B&0xFF);b+=8;};

string eB(int n){if(n<=0||n>b)return"";
uint32_t mask=(n==32)?0xFFFFFFFF:((1u<<n)-1);
uint32_t extracted=(buf>>(b-n))&mask;b-=n;buf=buf&((1u<<b)-1);
string result;result.reserve(n);for(int i=n-1;i>=0;i--){result.push_back((extracted&(1u<<i))?'1':'0');};return result;};

int LZ(ifstream& fis1,ofstream& fis2)
{
 int x,o,l,ch=C(fis1);if(ch<0)return 1;deque<int> ist,cit;bool g=1;string bu;
 for(x=0;x<3&&ch>-1;x++){cit.emplace_back(ch);ch=C(fis1);};if(x<3)return 2;
 while(b<25){pB(cit[0]);cit.pop_front();if(ch>-1)cit.emplace_back(ch);else return 3;ch=C(fis1);};
 while(g){if(eB(1)=="1"){o=Z(eB(16));l=Z(eB(8));for(x=0;x<l&&x+o<ist.size();x++){S(fis2,ist[o+x]);ist.emplace_back(ist[o+x]);};}
 else{o=Z(eB(8));S(fis2,o);ist.emplace_back(o);};while(ist.size()>65535)ist.pop_front();
 while(b<25&&cit.size()>1){pB(cit[0]);cit.pop_front();if(ch>-1)cit.emplace_back(ch);else g=0;ch=C(fis1);};};
 while(cit.size()>1){pB(cit[0]);cit.pop_front();};bu=eB(b-cit[0]);
 while(bu.length()){if(bu.substr(0,1)=="1")
      {bu.erase(0,1);o=Z(bu.substr(0,16));bu.erase(0,16);l=Z(bu.substr(0,8));bu.erase(0,8);
          for(x=0;x<l&&x+o<ist.size();x++){S(fis2,ist[o+x]);ist.emplace_back(ist[o+x]);};}
 else{bu.erase(0,1);o=Z(bu.substr(0,8));S(fis2,o);ist.emplace_back(o);};while(ist.size()>65535)ist.pop_front();};
return 0;};

int r;ifstream comp;ofstream org;

int main()
{org.open("O.txt",ios::binary);comp.open("Comp.txt",ios::binary); r=LZ(comp,org);switch (r)
{case 0:cout<<"Decompresie realizata cu succes!";break;
case 1:cout<<"EROARE!Fisierul e gol!";break;
case 2:cout<<"Eroare!Fisierul e prea mic!";break;
case 3:cout<<"Eroare!Fisierul este corupt!";break;};
return 0;}
