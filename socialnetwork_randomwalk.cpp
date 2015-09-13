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
	{cout<<"�Ҳ����ļ�";}
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
   return max+1; //�Ƚϳ������������ڵ�ı�ţ���Ϊ�����Ŵ�0��ʼ���������СΪ�����+1
}


void main()    
{  
	srand((unsigned)time(NULL));   //��ʼ�����������
	double randomnumber=0;
	int t=0;  //ͳ��������ѭ��ִ���˶��ٱ�
	int N;  //�����С
	int overflag=0; //�Ƿ����ر� 
	int S=0;//�׸�Ⱦ�ڵ�ĸ���  ��δ��Ⱦ�ڵ㣩
	int I=0;//��Ⱦ�ڵ�ĸ�  ��    �������ڵ㣩
	int R=0;//���߽ڵ�          �����߽ڵ㣩
	int IMAX=0; //������Ⱦ������I�ﵽ�����ֵ
	int RMAX=0; //����ʱ�̵�R��ֵ
	int count1=0; //��¼��������λ�öȵı仯
	double degree_sum=0; //������������λ�ýڵ��֮��
	double degreeavg=0;  //���и�Ⱦ�ڵ��ƽ����
	int nextloop=0; // ��һ����ַ
	double izong=0;  //�ж��ٲ�ͬ
	double success=0;  //ͳ���ж����ܳɹ�
	double biasum=0; 
	double bia=0; // ��ʽ�ĺ���
	double inf=0;//ͳ�ƽ�Ҫ��Ⱦ�ڵ����
	double biaavg=0; //bia��ƽ��ֵ
	double degreesum=0; //ͳ�ƽڵ�ĶȺ�
	double degree_begin=0; //��ƫ������ߵĸ��ʷ��� ���俪ʼ
	double degree_end=0;   //��ƫ������ߵĸ��ʷ��� �������
	double rand_num=0;    //0-1֮������С��
 	double alpha=-1; //��ƫ������ߵĲ���
	double lambda=1; //�˸�Ⱦϵ�� ��Ⱦϵ������Ϊ1��֤���Ը�Ⱦ
	double mu=0.1;   //��  ����ϵ��
	double gamma=0;    //�� �׸нڵ��������ϵ��  ��Ϊ������߹��̴�Ⱦ�ٶȽ�����������ϵ�����õ��㹻��
	double delta=0.1;    //�� ��Ⱦ�ڵ��������ϵ��  ��Ϊ������߹��̴�Ⱦ�ٶȽ���  ������ϵ�����õ��㹻��
    N=networksize();  //��������С
	cout<<"�����СΪ"<<N<<endl;
	double S_t=N-1;  //��ʽģ��S ���˳�ʼ�ڵ� ����ȫ��δ��Ⱦ
	double I_t=1;  //��ʽģ��I  ֻ��һ����Ⱦ�ڵ�
	double R_t=0;  //��ʽģ��R
	double I_increase=0; //�������ӵĸ�Ⱦ�ڵ����
	double I_selfimmune=0; //���������ߵĸ�Ⱦ�ڵ����
	double S_selfimmune=0; //���������ߵ��׸�Ⱦ�ڵ����
	double I_touch=0;//���νӴ���Ⱦ�Ľڵ����
	vector<int> temp_inf;  //�Խ�Ҫ����Ⱦ�Ľڵ�洢һ��
	vector<int> temp_imu;  //�Խ�Ҫ�����ߵĽڵ�洢һ��
	list<int> ele;      //����������߹��̵�����λ��
	int spread=5;   //ÿ����Ⱦ�ڵ㣨�����ڵ㣩ÿ���ͷų����ٸ�����
    vector< vector<int> > a(N); //��ʾ����ṹ�Ķ�ά����   �ճ���һ��λ���б�ʶ��0δ��Ⱦ�ڵ�  1�����ڵ� 2���߽ڵ� 
	int s=4; //s start   ��ʼʱ��Ĵ����ڵ��λ��
	for (int startkind=0;startkind<N;startkind++)   //���нڵ�ĵ�һλ��ֵ����ʶ���нڵ�ĳ�ʼ״��
	{ 
		if (startkind!=s)     //������Ǹ�Ⱦ�ڵ�
	{a[startkind].push_back(0);} //0��ʾ�׸�Ⱦ�ڵ�
	else
	{a[startkind].push_back(1);} //1��ʾ��Ⱦ�ڵ� 
	}
    FILE *f;
	if((f=fopen("graph.txt","rb"))==NULL)
	{cout<<"�Ҳ����ļ�";}
	int x,y;
   while(1)   
{
   if( fscanf(f,"%d%d",&x,&y)==EOF)
	   break;
  // cout<<x<<"  "<<y<<endl;
   for (int x_search=1;x_search<a[x].size();x_search++)//��һ��a[x]������Ƿ���y
   {
	   if(a[x][x_search]==y)
	   {overflag=1;break;}
   }
   if (overflag==0&&x!=y) //û���رߣ�û���Ի�
   {a[x].push_back(y);a[y].push_back(x);} //��y����a[x],�����ǰ�������ͼ�����
   overflag=0;
}
    /*
   for (int degreecount=0;degreecount<N;degreecount++)
   {
	//cout<<"���Ϊ"<<degreecount<<"�Ľڵ��Ϊ"<<a[degreecount].size()-1<<endl;
	//getch();
	}
	*/
 //////////////////////////////////////////////////////////////////////////////////�����ʼ����������ʼ��Ⱦ����
   for(alpha=0;alpha<=0;alpha=alpha+0.2)
   {
	for (int restart=0;restart<N;restart++)   //���нڵ�ĵ�һλ���¸�ֵ
	{ 
		if (restart!=s)     //������Ǹ�Ⱦ�ڵ�
	{a[restart][0]=0;} //0��ʾ�׸�Ⱦ�ڵ�
	else
	{a[restart][0]=1;} //1��ʾ��Ⱦ�ڵ� 
	}
	while(1)
	{            
		////////////////////////////////////////////////////////////////////////����ÿ����Ⱦ���������ڵ��ͷ����ӳ���
		t++; //����
		for(int elespread=0;elespread<N;elespread++)    //�������нڵ�
		{
		  if(a[elespread][0]==1)    //�����ǰ�ڵ��Ǹ�Ⱦ�ڵ�
		  {
	         for (int spread_process=0;spread_process<spread;spread_process++)   //ÿ����Ⱦ�ڵ��ͷų�spread������
			 { 
	          ele.push_back(elespread);        //����ѹ�����β��
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
	cout<<"�����ڵ����Ӹ���"<<ele.size()<<endl;
	////////////////////////////////////////////////////////////////////////////��һ�� ����Ⱦ
		for (list<int>::iterator i=ele.begin(); i!= ele.end();)            //list�����Ƕ�̬��С��ʹ�õ���������ȫ������
	{
          nextloop=0; //����break��continue����д��ѭ��ǰ�� 
          degreesum=0;//�Ⱥ�����
		  bia=0;
		 if(a[*i][0]==1&&(a[*i].size()-1)!=0)   //�����ǰ�ڵ��Ǵ����ڵ� ����������һ���ھ�
		 {   
			   count1++;	   
			   degree_sum=degree_sum+a[*i].size()-1;
			     for (int degree_count=1;degree_count<a[*i].size();degree_count++) //ͳ�ƽڵ��ھӵĶ�
				 {
					 degreesum=degreesum+pow(a[a[*i][degree_count]].size()-1,alpha);
					 if(a[a[*i][degree_count]][0]==0) 
					 {success++;}   
				 }
                 rand_num=(double)rand()/RAND_MAX; 
				 for (int de=1;de<a[*i].size();de++) //ͳ�ƽڵ��ھӵ�bia
				 {    
					 bia=bia+pow(1-(pow(a[a[*i][de]].size()-1,alpha)/degreesum),spread);
				 }
				 for (int deg=1;deg<a[*i].size();deg++) //ͳ�ƽڵ��ھӵĶ�
				 {    
					 degree_begin=degree_end;
					 degree_end=degree_end+pow(a[a[*i][deg]].size()-1,alpha)/degreesum;
				//	 cout<<*i<<"�ھ���"<<a[*i][deg]<<"���Ķ�Ϊ"<<a[a[*i][deg]].size()-1<<"Ϊ����������"<<degree_begin<<"-"<<degree_end<<endl;
					 if(rand_num>degree_begin&&rand_num<degree_end)
					 {nextloop=deg;break;}
					 else
					 {}
				 }
				 degree_begin=0; //��������
				 degree_end=0;          
				 biasum=biasum+a[*i].size()-1-bia; 
				// cout<<"��һ����ַ"<<a[*i][nextloop]<<endl;
				 if(a[a[*i][nextloop]][0]==1||a[a[*i][nextloop]][0]==2)   //�����һ���Ľڵ�Ϊ���߽ڵ㣬���߸�Ⱦ�ڵ㣨�����ڵ㣩
				 {ele.erase(i++);continue;}     //ɾ������ Ȼ�������ǰ��
				 else
				 {}
				// cout<<"��ǰ��ַΪ"<<*i<<"��һ����ַΪ"<<a[*i][nextloop]<<endl;
	  	         if((double)rand()/RAND_MAX<lambda&&a[a[*i][nextloop]][0]==0)   //�������һ�������С�ڦ�,����һ���Ľڵ���δ��Ⱦ�ڵ�
				 {temp_inf.push_back(a[*i][nextloop]);ele.erase(i++);continue;} //���½�Ҫ����Ⱦ�Ľڵ���,ɾ�����ӣ���������ǰ�� 
				 else {i++;continue;}     //������ض��������� 
		 }
		 else
		 {ele.erase(i++);}         //��ǰ�ڵ㲻�Ǵ����ڵ�,����û���ھӣ�ɾ�����ӣ�������Ҳǰ��
	}
	 for (int inf=0;inf<temp_inf.size();inf++)
	{a[temp_inf[inf]][0]=1;}    //����Ⱦ�ı�ʾ����Ϊ1 ����Ⱦ��
	temp_inf.clear();    //����Ⱦ����ʱ�������
    /*/////////////////////////////////////////////////////////////////////////////�ڶ���������
		 for (int imu=0;imu<N;imu++) 
   {
		 if(a[imu][0]==2)   //�����ǰ�ڵ������߽ڵ�
		 {   
			 for (int immune=1;immune<a[imu].size();immune++)  //����һ�鵱ǰ�ڵ���ھ�
			 {
				 if((double)rand()/RAND_MAX<mu&&a[a[imu][immune]][0]==1)   //�������һ�������С�ڦ�,���뵱ǰ�ڵ��ڽӣ��Ӵ����Ľڵ��Ǹ�Ⱦ�ڵ�
				 {temp_imu.push_back(a[imu][immune]);} //���½�Ҫ�����ߵĽڵ���
			 }
		 }
	}
		 for (int im=0;im<temp_imu.size();im++)
		 {a[temp_imu[im]][0]=2;}    //�����ߵĽڵ��ʾ����Ϊ2 ��������
		 temp_imu.clear();    //����Ⱦ�ı������
    *//////////////////////////////////////////////////////////////////////////////��������������
		  for (int selfimu=0;selfimu<N;selfimu++) 
   {
	//	 if(a[selfimu][0]==0&&(double)rand()/RAND_MAX<gamma)   //�����ǰ�ڵ����׸�Ⱦ�ڵ㣬��������һ��С�ڦõ������
	//	 {a[selfimu][0]=2;} //״̬��ʶ����Ϊ2   ������
		 if(a[selfimu][0]==1&&(double)rand()/RAND_MAX<delta)   //�����ǰ�ڵ��Ǹ�Ⱦ�ڵ㣨�����ڵ㣩����������һ��С�ڦĵ������
		 {a[selfimu][0]=2;} //״̬��ʶ����Ϊ2   ������		 
	}
    /////////////////////////////////////////////////////////////////////////////��Ⱦ����ȫ������ �������������
		  for (int count=0;count<N;count++)
		  {                              // 0δ��Ⱦ�ڵ�  1�����ڵ� 2���߽ڵ� 
			  if(a[count][0]==0)
			  {S++;}
			  if(a[count][0]==1)
			  {I++;}
			  if(a[count][0]==2)
			  {R++;}
		  }
		  //////////////////////////////////////��Ļ���
		  cout<<"��Ⱦ���е���"<<t<<"��"<<endl;
		  cout<<"S�׸�Ⱦ(δ��Ⱦ)�ڵ����:"<<S<<endl;
		  cout<<"I��Ⱦ(�����ڵ�)�ڵ����:"<<I<<endl;
		  cout<<"R���߽ڵ����:"<<R<<endl;
		  if(I>IMAX)  //IMAX��I�����ֵ
		  {IMAX=I;}
		  ///////////////////////////////////////ģ�����
		  ofstream ztest("degree.txt", ios::app);
          ztest<<t<<" "<<degree_sum/count<<endl;
	      ztest.close();
		  if(count1==0)   //������0����0������
		  {count1=1;}
		  else
		  {}
		  if(inf==0)   //������0����0������
		  {inf=1;}
		  else
		  {}
		  degreeavg=degree_sum/count1;
		  biaavg=biasum/count1;
		  cout<<"��Ⱦ�ڵ�ĶȺ�"<<degree_sum<<endl;
		  cout<<"��Ⱦ�ڵ�ĸ���"<<count1<<endl;
		  cout<<"��Ⱦ�ڵ��ƽ����"<<degreeavg<<endl;
          if(degreeavg==0)
		  {I_increase=0;
		   cout<<"�������ӵĸ�Ⱦ�ڵ���Ϊ0"<<endl;}
		  else
		  {
		 // cout<<"�������ӵĸ�Ⱦ�ڵ���Ϊ"<<I_t*(success/degree_sum)*degreeavg*(1-pow((1-1/degreeavg),spread))<<endl;
		  I_increase=I_t*(biaavg-1)*(success/degree_sum)*1.06;
		  cout<<"ƽ��һ���ܸ�Ⱦ����"<<biaavg<<endl;
		  cout<<"�ɹ���"<<success/degree_sum<<endl;
		  }
		  S_t=S_t-I_increase;
		  I_t=I_t+I_increase;
		 // cout<<"���νӴ����ߵĽڵ����"<<R_t*5*(I_t/N)*mu<<endl;
	   	 //  I_touch=R_t*5*(I_t/N)*mu;
		 // I_t=I_t-I_touch;
		 // R_t=R_t+I_touch;
		 // cout<<"���������ߵ��׸�Ⱦ�ڵ����"<<S_t*gamma<<endl;
		//  S_selfimmune=S_t*gamma;
		 // S_t=S_t-S_selfimmune;
		 // R_t=R_t+S_selfimmune;
		  cout<<"���������ߵĸ�Ⱦ�ڵ����"<<I_t*delta<<endl;
		  I_selfimmune=I_t*delta;
	      I_t=I_t-I_selfimmune;
		  R_t=R_t+I_selfimmune;
		  ofstream xtest("simuresult.txt", ios::app);
          xtest<<t<<" "<<S_t<<" "<<I_t<<" "<<R_t<<endl;
	      xtest.close();
		  ////////////////////////////////////////�ı����
		  ofstream ftest("result.txt", ios::app);
          ftest<<alpha<<" "<<t<<" "<<S<<" "<<I<<" "<<R<<endl;
	      ftest.close();
		  RMAX=R;
		  ////////////////////////////////////////
	      S=0;    //����������  ����
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
	      degree_end=0;   //��ƫ������ߵĸ��ʷ��� �������
	      rand_num=0;    //0-1֮������С��
          temp_inf.clear();  //�Խ�Ҫ����Ⱦ�Ľڵ�洢һ��
          temp_imu.clear();  //�Խ�Ҫ�����ߵĽڵ�洢һ��
          ele.clear();      //����������߹��̵�����λ��
          break;}
	}
 }
}
