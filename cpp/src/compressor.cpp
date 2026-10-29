#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

uint32_t buf;int b=0;
ifstream org;ofstream comp;
struct dTab;

string Bi(int O,int mW){if(O==0)return string(mW,'0');string d;d.reserve(32);
while(O>0){d.push_back('0'+(O&1));O>>=1;}reverse(d.begin(), d.end());
int pad=(mW-(d.length()%mW))%mW;if(pad)d.insert(0,pad,'0');return d;}

int Z(const string& B){int v=0;for(char c:B){v=(v<<1)|(c-'0');}return v;}

void S(ofstream& fis,int ch){fis.put(static_cast<char>(ch));};

int C(ifstream& fis){int ch; ch=fis.get(); if(ch==EOF)return -1; else return ch;};

void pb(int B,ofstream& f2){buf=(buf<<1)|B; b++; if(b==8){S(f2,buf&0xFF);b=0;buf=0;}}

void pB(const string& Bs,ofstream& fi2){for(char c:Bs)pb(c-'0',fi2);}

int cR(unsigned long long int N,unsigned int n)
{
 if(N<=0||n<=1||N<n) return 5;
 double r=(double)N/n;int R=5+(int)round(log2(r));
 if(N<100)R=5;
   else if(N<500)R=min(R,6);
   else if(N<2000)R=min(R,7);
   else if(N<10000)R=min(R,8);
   else if(N<50000)R=min(R,9);
 int Rm;
 if(n<=4)Rm=8;
   else if(n<=16)Rm=10;
   else if(n<=64)Rm=11;
    else Rm=12;
 R=min(R,Rm);if(R<5)R=5;
return R;};

vector<int>nF(const vector<long long>& cs,int L)
{
 int n=cs.size();vector<int>fs(n,0);
 long long N=0;for(auto c:cs)N+=c;if(N==0)return fs;
 long long s=0;int I=-1;long long C=-1;
 for (int g=0;g<n;g++){if(cs[g]==0)continue;
   double sc=(double)cs[g]*L/N;int v=(int)round(sc);v=max(v,1);
   fs[g]=v;s+=v;if(cs[g]>C){C=cs[g];I=g;};};
 if(I<0)return fs;long long d=L-s;fs[I]+=(int)d;
 fs[I]=max(fs[I],1);return fs;};

int LZ(string f1,string f2)
{ org.open(f1,ios::binary);comp.open(f2,ios::binary);
 int x,i,l=0,o=0,ch=C(org);bool g,ga,gt;deque<int> cit,ist;
 if(ch==-1)return 1;
 ist.emplace_back(ch);pB("0",comp);pB(Bi(ch,8),comp);ch=C(org);
 for(x=0;x<255&&ch!=-1;x++){cit.emplace_back(ch);ch=C(org);};
 while(cit.size()){i=0;l=0;gt=1;g=0;ga=1;
   for(x=0;x<ist.size()&&gt;x++)
    {if(g&&ist[x]!=cit[i]){gt=0;g=0;};
     if(ist[x]==cit[i]){l++;if(i+1<cit.size())i++;else break;g=1;};
     if(cit[0]==ist[x]&&ga){o=x;ga=!ga;};};
   if(l){if(l>255)l=255;pB("1",comp);pB(Bi(o,16),comp);pB(Bi(l,8),comp);}
     else{pB("0",comp);pB(Bi(cit[0],8),comp);l=1;};
   while(l){ist.emplace_back(cit[0]);cit.pop_front();l--;};
   while(cit.size()<256&&ch!=-1){cit.emplace_back(ch);ch=C(org);};
   while(ist.size()>65535)ist.pop_front();};
 for(x=0;b;x++)pb(0,comp);
 pB(Bi(x,8),comp);
 org.close();comp.close();
return 0;};

int tANS(string f1, string f2)
{ org.open(f1,ios::binary);vector<unsigned long long int> t1;unsigned long long int N=0;
 {int ch=C(org);for(int x=0;x<256;x++)t1.emplace_back(0);if(ch<0)return 1;
 while(ch>-1){t1[ch]++;ch=C(org);N++;};org.close();};
 int n=t1.size(),r=cR(N,n),l=2^r;vector<int> fs=nF(t1,l);
 int s=(l>>1)+(L>>3)+3,p=0;if(!(s%2))s++;
 for(int i=0;i<n;i++)for(int j;j<fs[i];j++){}
return 0;}

string ori,com;
int r;

int main()
{
 cin>>ori>>com;r=LZ(ori,com);if(r==0)cout<<"Compresie realizata cu succes! ";else cout<<"EROARE! Fisierul e gol! ";
return 0;}
