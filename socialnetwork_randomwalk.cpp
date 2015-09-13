#include<math.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdio>  
#include <cstdlib>  
#include <fstream>
#include <vector>
#include <list>

using namespace std;

int networksize()
{  
	int max=0;
	FILE *p;
	if((p=fopen("graph.txt","rb"))==NULL)
	{cout<<"找不到文件";}
	int x,y;
   while(1)   
{
   if( fscanf(p,"%d%d",&x,&y)==EOF)
	   break;
   if(x>max)
   {max=x;}
   else
   {}
   if (y>max)
   {max=y;}
   else
   {}
}
   return max+1; //比较出网络里面最大节点的编号，因为网络编号从0开始的则网络大小为最大编号+1
}


void main()    
{  
	srand((unsigned)time(NULL));   //初始化随机数种子
	double randomnumber=0;
	int t=0;  //统计主程序循环执行了多少遍
	int N;  //网络大小
	int overflag=0; //是否有重边 
	int S=0;//易感染节点的个数  （未感染节点）
	int I=0;//感染节点的个  数    （传播节点）
	int R=0;//免疫节点          （免疫节点）
	int IMAX=0; //整个感染过程中I达到的最大值
	int RMAX=0; //收敛时刻的R的值
	int count1=0; //记录粒子所在位置度的变化
	double degree_sum=0; //所有粒子所在位置节点度之和
	double degreeavg=0;  //所有感染节点的平均度
	int nextloop=0; // 下一跳地址
	double izong=0;  //有多少不同
	double success=0;  //统计有多少能成功
	double biasum=0; 
	double bia=0; // 公式的后半段
	double inf=0;//统计将要感染节点个数
	double biaavg=0; //bia的平均值
	double degreesum=0; //统计节点的度和
	double degree_begin=0; //有偏随机行走的概率分配 区间开始
	double degree_end=0;   //有偏随机行走的概率分配 区间结束
	double rand_num=0;    //0-1之间的随机小数
 	double alpha=-1; //有偏随机行走的参数
	double lambda=1; //λ感染系数 感染系数设置为1保证可以感染
	double mu=0.1;   //μ  免疫系数
	double gamma=0;    //γ 易感节点的自免疫系数  因为随机行走过程传染速度较慢，自免疫系数设置的足够低
	double delta=0.1;    //δ 感染节点的自免疫系数  因为随机行走过程传染速度较慢  自免疫系数设置的足够低
    N=networksize();  //获得网络大小
	cout<<"网络大小为"<<N<<endl;
	double S_t=N-1;  //公式模拟S 除了初始节点 其余全是未感染
	double I_t=1;  //公式模拟I  只有一个感染节点
	double R_t=0;  //公式模拟R
	double I_increase=0; //本次增加的感染节点个数
	double I_selfimmune=0; //本次自免疫的感染节点个数
	double S_selfimmune=0; //本次自免疫的易感染节点个数
	double I_touch=0;//本次接触感染的节点个数
	vector<int> temp_inf;  //对将要被感染的节点存储一下
	vector<int> temp_imu;  //对将要被免疫的节点存储一下
	list<int> ele;      //储存随机行走过程的粒子位置
	int spread=5;   //每个感染节点（传播节点）每次释放出多少个粒子
    vector< vector<int> > a(N); //表示网络结构的二维数组   空出第一个位进行标识：0未感染节点  1传播节点 2免疫节点 
	int s=4; //s start   开始时候的传播节点的位置
	for (int startkind=0;startkind<N;startkind++)   //所有节点的第一位赋值，标识所有节点的初始状况
	{ 
		if (startkind!=s)     //如果它是感染节点
	{a[startkind].push_back(0);} //0表示易感染节点
	else
	{a[startkind].push_back(1);} //1表示感染节点 
	}
    FILE *f;
	if((f=fopen("graph.txt","rb"))==NULL)
	{cout<<"找不到文件";}
	int x,y;
   while(1)   
{
   if( fscanf(f,"%d%d",&x,&y)==EOF)
	   break;
  // cout<<x<<"  "<<y<<endl;
   for (int x_search=1;x_search<a[x].size();x_search++)//看一下a[x]下面的是否有y
   {
	   if(a[x][x_search]==y)
	   {overflag=1;break;}
   }
   if (overflag==0&&x!=y) //没有重边，没有自环
   {a[x].push_back(y);a[y].push_back(x);} //把y推入a[x],这里是按照无向图处理的
   overflag=0;
}
    /*
   for (int degreecount=0;degreecount<N;degreecount++)
   {
	//cout<<"编号为"<<degreecount<<"的节点度为"<<a[degreecount].size()-1<<endl;
	//getch();
	}
	*/
 //////////////////////////////////////////////////////////////////////////////////网络初始化结束，开始感染过程
   for(alpha=0;alpha<=0;alpha=alpha+0.2)
   {
	for (int restart=0;restart<N;restart++)   //所有节点的第一位重新赋值
	{ 
		if (restart!=s)     //如果它是感染节点
	{a[restart][0]=0;} //0表示易感染节点
	else
	{a[restart][0]=1;} //1表示感染节点 
	}
	while(1)
	{            
		////////////////////////////////////////////////////////////////////////首先每个感染（传播）节点释放粒子出来
		t++; //计数
		for(int elespread=0;elespread<N;elespread++)    //遍历所有节点
		{
		  if(a[elespread][0]==1)    //如果当前节点是感染节点
		  {
	         for (int spread_process=0;spread_process<spread;spread_process++)   //每个感染节点释放出spread个粒子
			 { 
	          ele.push_back(elespread);        //粒子压入队列尾部
			 }
		  }
		}
		  count1=0;
		  degree_sum=0;
		  success=0;
		  inf=0;
		  bia=0;
		  biaavg=0;
		  biasum=0;
	cout<<"网络内的粒子个数"<<ele.size()<<endl;
	////////////////////////////////////////////////////////////////////////////第一步 ：感染
		for (list<int>::iterator i=ele.begin(); i!= ele.end();)            //list现在是动态大小，使用迭代器遍历全部粒子
	{
          nextloop=0; //用了break与continue清零写在循环前面 
          degreesum=0;//度和清零
		  bia=0;
		 if(a[*i][0]==1&&(a[*i].size()-1)!=0)   //如果当前节点是传播节点 ，且有至少一个邻居
		 {   
			   count1++;	   
			   degree_sum=degree_sum+a[*i].size()-1;
			     for (int degree_count=1;degree_count<a[*i].size();degree_count++) //统计节点邻居的度
				 {
					 degreesum=degreesum+pow(a[a[*i][degree_count]].size()-1,alpha);
					 if(a[a[*i][degree_count]][0]==0) 
					 {success++;}   
				 }
                 rand_num=(double)rand()/RAND_MAX; 
				 for (int de=1;de<a[*i].size();de++) //统计节点邻居的bia
				 {    
					 bia=bia+pow(1-(pow(a[a[*i][de]].size()-1,alpha)/degreesum),spread);
				 }
				 for (int deg=1;deg<a[*i].size();deg++) //统计节点邻居的度
				 {    
					 degree_begin=degree_end;
					 degree_end=degree_end+pow(a[a[*i][deg]].size()-1,alpha)/degreesum;
				//	 cout<<*i<<"邻居是"<<a[*i][deg]<<"它的度为"<<a[a[*i][deg]].size()-1<<"为其分配的区间"<<degree_begin<<"-"<<degree_end<<endl;
					 if(rand_num>degree_begin&&rand_num<degree_end)
					 {nextloop=deg;break;}
					 else
					 {}
				 }
				 degree_begin=0; //区间清零
				 degree_end=0;          
				 biasum=biasum+a[*i].size()-1-bia; 
				// cout<<"下一跳地址"<<a[*i][nextloop]<<endl;
				 if(a[a[*i][nextloop]][0]==1||a[a[*i][nextloop]][0]==2)   //如果下一跳的节点为免疫节点，或者感染节点（传播节点）
				 {ele.erase(i++);continue;}     //删除粒子 然后迭代器前进
				 else
				 {}
				// cout<<"当前地址为"<<*i<<"下一跳地址为"<<a[*i][nextloop]<<endl;
	  	         if((double)rand()/RAND_MAX<lambda&&a[a[*i][nextloop]][0]==0)   //如果生成一个随机数小于λ,且下一跳的节点是未感染节点
				 {temp_inf.push_back(a[*i][nextloop]);ele.erase(i++);continue;} //记下将要被感染的节点编号,删除粒子，迭代器向前进 
				 else {i++;continue;}     //随机数必定符合条件 
		 }
		 else
		 {ele.erase(i++);}         //当前节点不是传播节点,或者没有邻居，删除粒子，迭代器也前进
	}
	 for (int inf=0;inf<temp_inf.size();inf++)
	{a[temp_inf[inf]][0]=1;}    //被感染的标示符置为1 被感染了
	temp_inf.clear();    //被感染的临时编号清零
    /*/////////////////////////////////////////////////////////////////////////////第二步：免疫
		 for (int imu=0;imu<N;imu++) 
   {
		 if(a[imu][0]==2)   //如果当前节点是免疫节点
		 {   
			 for (int immune=1;immune<a[imu].size();immune++)  //遍历一遍当前节点的邻居
			 {
				 if((double)rand()/RAND_MAX<mu&&a[a[imu][immune]][0]==1)   //如果生成一个随机数小于μ,且与当前节点邻接（接触）的节点是感染节点
				 {temp_imu.push_back(a[imu][immune]);} //记下将要被免疫的节点编号
			 }
		 }
	}
		 for (int im=0;im<temp_imu.size();im++)
		 {a[temp_imu[im]][0]=2;}    //被免疫的节点标示符置为2 被免疫了
		 temp_imu.clear();    //被感染的编号清零
    *//////////////////////////////////////////////////////////////////////////////第三步：自免疫
		  for (int selfimu=0;selfimu<N;selfimu++) 
   {
	//	 if(a[selfimu][0]==0&&(double)rand()/RAND_MAX<gamma)   //如果当前节点是易感染节点，且生成了一个小于γ的随机数
	//	 {a[selfimu][0]=2;} //状态标识符置为2   自免疫
		 if(a[selfimu][0]==1&&(double)rand()/RAND_MAX<delta)   //如果当前节点是感染节点（传播节点），且生成了一个小于δ的随机数
		 {a[selfimu][0]=2;} //状态标识符置为2   自免疫		 
	}
    /////////////////////////////////////////////////////////////////////////////感染过程全部结束 ，进入计数环节
		  for (int count=0;count<N;count++)
		  {                              // 0未感染节点  1传播节点 2免疫节点 
			  if(a[count][0]==0)
			  {S++;}
			  if(a[count][0]==1)
			  {I++;}
			  if(a[count][0]==2)
			  {R++;}
		  }
		  //////////////////////////////////////屏幕输出
		  cout<<"感染进行到第"<<t<<"步"<<endl;
		  cout<<"S易感染(未感染)节点个数:"<<S<<endl;
		  cout<<"I感染(传播节点)节点个数:"<<I<<endl;
		  cout<<"R免疫节点个数:"<<R<<endl;
		  if(I>IMAX)  //IMAX是I的最大值
		  {IMAX=I;}
		  ///////////////////////////////////////模拟输出
		  ofstream ztest("degree.txt", ios::app);
          ztest<<t<<" "<<degree_sum/count<<endl;
	      ztest.close();
		  if(count1==0)   //避免了0除以0的尴尬
		  {count1=1;}
		  else
		  {}
		  if(inf==0)   //避免了0除以0的尴尬
		  {inf=1;}
		  else
		  {}
		  degreeavg=degree_sum/count1;
		  biaavg=biasum/count1;
		  cout<<"感染节点的度和"<<degree_sum<<endl;
		  cout<<"感染节点的个数"<<count1<<endl;
		  cout<<"感染节点的平均度"<<degreeavg<<endl;
          if(degreeavg==0)
		  {I_increase=0;
		   cout<<"本次增加的感染节点数为0"<<endl;}
		  else
		  {
		 // cout<<"本次增加的感染节点数为"<<I_t*(success/degree_sum)*degreeavg*(1-pow((1-1/degreeavg),spread))<<endl;
		  I_increase=I_t*(biaavg-1)*(success/degree_sum)*1.06;
		  cout<<"平均一个能感染几个"<<biaavg<<endl;
		  cout<<"成功率"<<success/degree_sum<<endl;
		  }
		  S_t=S_t-I_increase;
		  I_t=I_t+I_increase;
		 // cout<<"本次接触免疫的节点个数"<<R_t*5*(I_t/N)*mu<<endl;
	   	 //  I_touch=R_t*5*(I_t/N)*mu;
		 // I_t=I_t-I_touch;
		 // R_t=R_t+I_touch;
		 // cout<<"本次自免疫的易感染节点个数"<<S_t*gamma<<endl;
		//  S_selfimmune=S_t*gamma;
		 // S_t=S_t-S_selfimmune;
		 // R_t=R_t+S_selfimmune;
		  cout<<"本次自免疫的感染节点个数"<<I_t*delta<<endl;
		  I_selfimmune=I_t*delta;
	      I_t=I_t-I_selfimmune;
		  R_t=R_t+I_selfimmune;
		  ofstream xtest("simuresult.txt", ios::app);
          xtest<<t<<" "<<S_t<<" "<<I_t<<" "<<R_t<<endl;
	      xtest.close();
		  ////////////////////////////////////////文本输出
		  ofstream ftest("result.txt", ios::app);
          ftest<<alpha<<" "<<t<<" "<<S<<" "<<I<<" "<<R<<endl;
	      ftest.close();
		  RMAX=R;
		  ////////////////////////////////////////
	      S=0;    //计数结束了  清零
		  I=0;
		  R=0;
		  if (t==150)
		  {t=0;
		  ofstream gtest("finresult.txt", ios::app);
          gtest<<alpha<<" "<<IMAX<<" "<<RMAX<<endl;
	      gtest.close();
		  IMAX=0;
		  RMAX=0;
		  nextloop=0;
		  degreesum=0; 
		  degree_begin=0; 
	      degree_end=0;   //有偏随机行走的概率分配 区间结束
	      rand_num=0;    //0-1之间的随机小数
          temp_inf.clear();  //对将要被感染的节点存储一下
          temp_imu.clear();  //对将要被免疫的节点存储一下
          ele.clear();      //储存随机行走过程的粒子位置
          break;}
	}
 }
}
