#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
using namespace std;

uint32_t buf;int b=0;

string Bi(int O,int mW=8){if(O==0)return string(mW,'0');string d;d.reserve(32);
while(O>0){d.push_back('0'+(O&1));O>>=1;}reverse(d.begin(), d.end());
int pad=(mW-(d.length()%mW))%mW;if(pad)d.insert(0,pad,'0');return d;}

int Z(const string& B){int v=0;for(char c:B){v=(v<<1)|(c-'0');}return v;}

void S(ofstream& fis,int ch){fis.put(static_cast<char>(ch));};

int C(ifstream& fis){int ch; ch=fis.get(); if(ch==EOF)return -1; else return ch;};

void pb(int B,ofstream& f2){buf=(buf<<1)|B; b++; if(b==8){S(f2,buf&0xFF); b=0; buf=0;}}

void pB(const string& Bs,ofstream& fi2){for(char c:Bs)pb(c-'0',fi2);}

int LZ(ifstream& fis1,ofstream& fis2)
{int chc,c,l,o;deque<int>ist,cit;bool g,gt;int x,i;
chc=C(fis1); if(chc==-1)return 1;pB(Bi(chc,8),fis2);
ist.emplace_back();ist.back()=chc;for(x=0;x<256;x++){chc=C(fis1);if(chc!=-1){cit.emplace_back();cit.back()=chc;};};
while(cit.size()>0){i=0;l=0;gt=1;g=0;
for(x=0;x<ist.size()&&gt;x++){if(ist[x]==cit[i]){l++;if(i+1<cit.size())i++;g=1;};if(g&&ist[x]!=cit[i]){gt=0;g=0;};if(cit[0]==ist[x]&&g)o=x;};
if(l>0){pB("1",fis2); pB(Bi(o,16),fis2); pB(Bi(l,8),fis2);}else{pB("0",fis2); pB(Bi(cit[0],8),fis2);l=1;};
for(x=0;x<l;x++){ist.emplace_back();ist.back()=cit.front();cit.pop_front();};
while(ist.size()>65535){ist.pop_front();};for(x=cit.size();x<256;x++){chc=C(fis1);if(chc!=-1){cit.emplace_back();cit.back()=chc;};};};
if(b>0){for(x=1;b!=0;x++)pB("0",fis2);S(fis2,x-1);}else S(fis2,0);
return 0;};

ifstream org;
ofstream comp;
int r;

int main()
{ org.open("O.docx",ios::binary); comp.open("Comp.txt",ios::binary);r=LZ(org,comp);
if(r==0)cout<<"Compresie realizata cu succes!";else cout<<"EROARE! Fisierul e gol!";
return 0;}
