int test(ifstream& fis1,ofstream& fis2)
{
 int x,ch=C(fis1); if(ch==-1)return 1;
 deque<int> cit;
 while(ch!=-1)
 {for(x=0;x<65535&&ch!=-1;x++){cit.emplace_back(ch);ch=C(fis1);};
  while(cit.size()>0){pB(Bi(cit[0],8),fis2);cit.pop_front();};};
return 0;};
