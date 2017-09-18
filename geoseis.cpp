#include <iostream>
#include <stdio.h>
using namespace std;
#include <sysdefine.h>
#include <projectmng.h>
#include <logfile.h>
#include <comfun.h>
#include <diskmng.h>
#include <nodemng.h>
#include <filemng.h>
#include <QDebug>
#include <QString>
int testnode()
{
    nodeMng node;
    nodeInfo *ni;
    int i;
    //nlist = new  vector <nodeInfo >;
    //ni = (nodeInfo * )&node.m_list->at(0);
   // ni = new nodeInfo();
     
    for (i = 0; i <node.size();i++)
   {
    
    ni =  (nodeInfo *) node.get(i); 
    //ni->getInfoFromMap();
    cout << ni->name <<endl;
    cout << ni->cluster <<endl;
    cout << ni->system <<endl;
    cout << ni->getStatus() <<endl;
    }
    
    node.removeItem((char *)"ibm1-212");
    
/*
        for (i = 0; i <node.size();i++)
   {
    
    ni =  (nodeInfo *) node.get(i); 
    //ni->getInfoFromMap();
    cout << ni->name <<endl;
    cout << ni->cluster <<endl;
    cout << ni->system <<endl;
    }
*/

    cout << "start dump======\n";
    node.dump();
}
/*
int testnode1()
{
    nodeMng node;
    nodeInfo *ni;
    int i;
    //nlist = new  vector <nodeInfo >;
    //ni = (nodeInfo * )&node.m_list->at(0);
   // ni = new nodeInfo();
    for (i = 0; i <node.m_list->size();i++)
   {
    
    ni =  &node.m_list->at(i); 
    //ni->getInfoFromMap();
    cout << ni->name <<endl;
    cout << ni->cluster <<endl;
    cout << ni->system <<endl;
    }

    cout << "start dump======\n";
   // node.dump();

   // cout << "size = " << node.size() <<endl;
   // cout << "find = " << node.find("name") <<endl;
  //  cout << "remove = " << node.remove("name") <<endl;
  //  cout << "find = " << node.find("name") <<endl;

    return 1;
*/

    
/*
    for (i =0; i <node.m_list->size(); i++)
    {
        cout << "ffff\n";
       // cout << node.getList()->at(i).name <<endl;
       // cout << node.m_list->at(i).name <<endl;
       // cout <<  node.m_list->at(i).cluster <<endl;
        cout << "wwwwwwwww\n";
    }*/
//}
int testProject()
{
   int i;

   
    
   projectMng p;   
   PROJECTList list; 
   list = p.getProjectList();
   cout << " all projects = "<< list.size() << endl;

   MPR1("projects information:\n");
   MPR1("-----------------------\n");

   for (i = 0; i<list.size(); i++) 
   {
      cout << "n = " <<list[i].name <<" u= "<< list[i].user <<" d= " << list[i].date << endl;
   }
   /*
   MPR1("-----------------------\n");
   MPR1("test log message:\n");
   MPR1("-----------------------\n");
   cout << "date = " << p.tm.cdate() <<endl;
   logFile log;
   //logFile log();
   log.line("this in LOG line");
   log.tline("this in LOG tline");
   log.warning("this in LOG warning");
   log.error("this in LOG error");
   MPR1("-end of log----------------------\n");
  
   MPR1("remove project: myproject1=========\n");
   if(p.removeProject((char*)"myproject1"))   
       MPR1(" failed\n");
   else
       MPR1(" OK \n");
   //exit(1);

  // p.createProject("myproject");*/
   MPR1("create project: myproject1=========\n");
   if(p.createProject((char*)"myproject1"))   
       MPR1(" failed\n");
   else
       MPR1(" OK \n");

   MPR1("set project: myproject\n");
   p.setProject((char*)"myproject");
   MPR1("create line1 ----\n");
   if(p.createLine((char*)"line1"))
       MPR1(" failed\n");
   else
       MPR1(" OK \n");
    MPR1("remove line1 ----- \n");
   if(p.removeLine((char*)"line1"))
       MPR1("remove failed\n");
   else
       MPR1(" OK \n");

    MPR1("remove line2:----- \n");
   if(p.removeLine((char*)"line2"))
   {
       MPR1("remove failed\n");
   }
   else
       MPR1("OK\n");

   MPR1("create line2:----- \n");
   if(p.createLine((char*)"line2"))
   {
       MPR1("create failed\n");
   }
   else
       MPR1("OK\n");
       //dirs:
       return(0);
}


void testSplit()
{
   int i;
   string str;
   stringList sl,sl1;
  // string str;
   sl.push_back("1111");
   sl.push_back("2222");
   sl.push_back("3333");
   str = mergeStr(sl);
   cout << str << endl;
   sl1 = splitStr(str);
   for (i = 0; i<sl1.size(); i++) 
   {
      cout << sl1[i] << endl;
   }
 
}
void testInfo()
{
    //baseInfo *bp;
    diskMng dm;
    diskInfo *di;
    float f;
    int i;
    MPR1("load begin\n");
    if (dm.loadDisk() != 0) 
    {
        MPR1("load error\n");
    }
    //test speed:
    for (i = 0; i < 1 ;i++) 
    {
      di = (diskInfo *)dm.get(0); 
      f =di->getSpeed();
      MPR3("diskspeed %s= %f M/s\n",di->name.c_str(),f);

      di = (diskInfo *)dm.get(1);
      f =di->getSpeed();
      MPR3("diskspeed %s= %f M/s\n",di->name.c_str(),f);
    }
    /*
    /s0/u/cjh/work/geoseis/Debug/geoseis 
    load begin
    diskspeed /s0/u/cjh/disk1= 0.000000 M/s
    Abort (core dumped)

 
*/

     //   exit(1);
    MPR1("after load\n");
    MPR1("start dump:  ---\n");
    //dm.dump();
    dm.saveDisk();
    MPR1("after save\n");
    //di.getStatus();
 
}
void testspeed()
{
    //baseInfo *bp;
    diskMng dm;
    diskInfo *di;
    float f;
    int i;
    MPR1("load begin\n");
    if (dm.loadDisk() != 0) 
    {
        MPR1("load error\n");
    }
    //test speed:
    for (i = 0; i < 2 ;i++) 
    {
      di = (diskInfo *)dm.get(0); 
      f =di->getSpeed();
      MPR3("diskspeed %s= %f M/s\n",di->name.c_str(),f);

      di = (diskInfo *)dm.get(1);
      f =di->getSpeed();
      MPR3("diskspeed %s= %f M/s\n",di->name.c_str(),f);
    }
}
    /*
    /s0/u/cjh/work/geoseis/Debug/geoseis 
    load begin
    diskspeed /s0/u/cjh/disk1= 0.000000 M/s
    Abort (core dumped)
 
*/
 
 
void testfind()
{
    int i;
    stringList list;
    list = findFiles((char *)"/s0/u/cjh/test",(char *)"*");
    cout << "files = " << list.size()<<endl;

    for (i = 0; i <list.size(); i++) 
    {
        //MPR1(list.at[i]);
        cout<<i << " " << list.at(i) <<endl;
    }
    //testdirfile:
    list = dirFiles((char *)"/s0/u/cjh/test");
cout << "test dirFiles=======================\n";
    for (i = 0; i <list.size(); i++) 
    {
        //MPR1(list.at[i]);
        cout<<i << "== " << list.at(i) <<endl;
    }
        //testdirfile:
    list.clear();

cout << "test dirFileAll=======================\n";

    dirFileAll((char *)"/s0/u/cjh/test",list);

cout << "after size = " << list.size() <<endl;
    for (i = 0; i <list.size(); i++) 
    {
        //MPR1(list.at[i]);
        cout<<i << "all== " << list.at(i) <<endl;
    }



}
/*
void testpattern()
{
    cout <<"--------------\n";
    if(isPattern((char *)"123",(char *)"1*"))
        cout << "123 in 1* is ok\n" ;
    else
         cout << "123 in 1* is falut\n" ;

     cout <<"--------------\n";

    if(isPattern((char *)"12223",(char *)"1*3"))
        cout << "12223 in 1*3 is ok\n" ;
    else
         cout << "12223 in 1*3 is falut\n" ;

    string cmd ;
    size_t len;
    ssize_t   ret;
    int i;
    char *line =NULL;
    //char *pt = "geo*";
    char *pt = (char *)"base*";

    cmd = "ls -ltr";//ok
    cmd = "ls -ltr *.cpp";//ok
    cmd = "ls -ltr";//ok
    FILE *fp = popen(cmd.c_str(),"r");
 
    i =0;
    if (fp !=NULL)
    {
        while (ret = getline(&line,&len,fp) != -1) 
        {
            
             if(isPattern(line,pt))
             {
                 
                 cout << " i = " << i << " " << line ;
                 i++;
             }
             else
                 continue;
        }
        pclose(fp);
    }
}
*/
void testvector()
{
    vector <int *> *ia;
    int *a,*b;
    a = new int;
    *a=10;
    cout << "0 addr = "<<a<< " v = "<<*a <<endl;

    ia = new vector<int *>;
    ia->push_back(a);

     b= (*ia)[0];
     cout << "0 addr b= "<<b<< " v = "<<*b <<endl;


    delete a;
    b= ia->at(0);

    cout << "1 addr b= "<<b<< " v = "<<*b <<endl;

    ia->clear();
    cout << "1 addr = "<<a<< " v = "<<*a <<endl;
    cout << "1 addr b= "<<b<< " v = "<<*b <<endl;

     vector <int > *iia;
     int aa,bb;
     aa = 20;
     iia = new vector<int>;
     iia->push_back(aa);
     bb =(*iia)[0];
     cout << "00 addr a= "<<aa<< " v = "<<&aa <<endl;
     cout << "00 addr b= "<<bb<< " v = "<<&bb <<endl;
     iia->clear();
     cout << "00 addr a= "<<aa<< " v = "<<&aa <<endl;
     cout << "01 addr b= "<<bb<< " v = "<<&bb <<endl;




}
void testfile()
{
    logMng log;
    fileInfo *fp;
    log.setProject((char *)"myproject1");

    cout << "size of files = " << log.size() <<endl;

    log.dump();
    int i ;
    for (i = 0 ; i <log.size() ; i++) 
    {
       fp =  (fileInfo *)(log.get(i));
       cout << fp->name <<endl;
       cout << fp->path <<endl;
       cout << fp->size <<endl;
       cout << fp->time <<endl;
       cout << fp->user <<endl;
    }

    cout << "======================\n";
    log.setProject((char *)"myproject",(char *)"line2");
    for (i = 0 ; i <log.size() ; i++) 
    {
       fp =  (fileInfo *)(log.get(i));
       cout << fp->name <<endl;
       cout << fp->path <<endl;
       cout << fp->size <<endl;
       cout << fp->time <<endl;
       cout << fp->user <<endl;
    }

}
void testdata()
{
    dataMng log;
    fileInfo *fp;
    log.setProject((char *)"myproject1");

    cout << "size of files = " << log.size() <<endl;

    log.dump();
    int i ;
    for (i = 0 ; i <log.size() ; i++) 
    {
       fp =  (fileInfo *)(log.get(i));
       cout << fp->name <<endl;
       cout << fp->path <<endl;
       cout << fp->size <<endl;
       cout << fp->time <<endl;
    }
        cout << "======================\n";
    log.setProject((char *)"myproject",(char *)"line2");
    for (i = 0 ; i <log.size() ; i++) 
    {
       fp =  (fileInfo *)(log.get(i));
       cout << fp->name <<endl;
       cout << fp->path <<endl;
       cout << fp->size <<endl;
       cout << fp->time <<endl;
    }
}
void testlog()
{
    logFile log;
    log.tline("12345\n");
    
}
void testdoc()
{
    qDebug() << "doc = " << getDocDir();
}
int main (int argc, char *argv[])
{//
    testdoc();
     //testProject();
    // testInfo();
    //testSplit();
    //testInfo();
     //testspeed();
    // testfind();
    //testpattern();//ok
    // testnode();
     //testvector();
     //testfile();
    //testdata();
    //testlog();
 
     return(0);
}

       
 
