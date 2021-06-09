#include <iostream>
#include <stdlib.h>

#define N 32
using namespace std;

class IHO
{
private:
        unsigned char A[N*2];
public:
       IHO();
       void OLIA(unsigned char* );
       void HANA(unsigned char*);
       void operator +=(IHO );
       IHO operator +(IHO );
       int operator >(IHO );
       int operator ==( IHO );
       void operator -=(IHO );
       IHO operator -(IHO );
       IHO operator *(IHO);
       void operator >>(int);
       void operator <<(int);
       void HANA_Dil(IHO, IHO*);
       IHO operator %(IHO );
       IHO operator /(IHO );
       int PER_10();
       void HANA_10(unsigned char* );
       void HANECHKA(unsigned char*);
       IHO EXPM(IHO B,IHO M);
       int SB ( unsigned int );
       void longA(unsigned long );
       unsigned long BUBU();
       IHO GEN_P();
       int TEST_1();
       void Shifr(unsigned char* , unsigned char* , IHO , IHO );
       void DeShifr(unsigned char* ,  unsigned char* ,IHO , IHO );
};
//constructor
IHO::IHO()
{
for(int i=0; i<N*2; i++)
A[i]=0;

}
//translates the symbolic representation of a number into 
//an internal representation in the form of a binary code of arbitrary length
 void IHO::OLIA( unsigned char* h)
 {
 int i,j,n,m;
 for(i=0; i<N; i++)
 A[i]=0;
 
 i=0;
 while(*(h+i)!=0)
 i++;
 n=0; m=0;
 
 for(j=i-1; j>=0; j--)
 {
 if(n==2)
 {n=0; m++;}
 
 if(n==0)
         if(*(h+j)<='9')
 A[m]=(*(h+j)-'0');
 else
 A[m]=(*(h+j)-'A'+10);
 else
     if(*(h+j)<='9')
     A[m]+=(*(h+j)-'0')<<4;
     else
      A[m]+=(*(h+j)-'A'+10)<<4;
 n++;
 }

 }
 
void IHO::HANA(unsigned char*h)
{
int i,j,n;
i=N-1;
while(A[i--]==0);
i++;

unsigned char B[2];
n=0;

for(j=i; j>=0; j--)
{
if(((A[j]>>4)&0xF) <=9)
B[0]=((A[j]>>4)&0xF)+'0';
else
B[0]=((A[j]>>4)&0xF)-10+'A';


if((A[j]&0xF) <=9)
B[1]=(A[j]&0xF)+'0';
else
B[1]=(A[j]&0xF)-10+'A';

*(h+n)=B[0];
*(h+n+1)=B[1];
n+=2;
}

*(h+n)=0;
}
//add operator
void IHO::operator +=(IHO B)
{   
int j,p,a,b,c;
p=0;

for(int j=0; j<N; j++)
{
a=A[j];
b=B.A[j];
c=a+b+p;
A[j]=c;
p=((c>>8)&0x1);
}
}

//add operator
IHO IHO::operator +(IHO B)
{   
int j,p,a,b,c;
p=0;
IHO C=*this;
for(int j=0; j<N; j++)
{
a=C.A[j];
b=B.A[j];
c=a+b+p;
C.A[j]=c;
p=((c>>8)&0x1);
}
return C;
}


//comparison operator
int IHO::operator >( IHO Y)
{
int j;
for(j=N-1; j>=0; j--)
if(A[j]>Y.A[j])  return 1; 
else if(A[j]<Y.A[j]) return 2;

return 1;
}
int IHO::operator ==( IHO Y)
{
int j;

for(j=N-1; j>=0; j--)
if(A[j]!=Y.A[j])  return 0;

return 1;
}
//subtraction operator
void IHO::operator -=(IHO B)
{
int a,b,c;
int P= *this > B;
IHO X,Y;

if(P==1)
{
X=*this;
Y=B;
}
else
{X=B; Y=*this;}

int Z=0;
for(int j=0; j<N; j++)
{a=X.A[j];
b=Y.A[j];
a-=Z;
Z=0;

if(a<0)
      { a=0xFF; Z=1;} 
if(a>b)
c=a-b;
else
if(a<b)
{c=a-b+256; Z=1;}
else c=0;
X.A[j]=c;
}
*(this)=X;

}
//subtraction operator
IHO IHO::operator -(IHO B)
{
int a,b,c;
int P= *this > B;
IHO X,Y;
IHO ABC;


if(P==1)
{
X=*this;
Y=B;
}
else
{X=B; Y=*this;}

int Z=0;
for(int j=0; j<N; j++)
{a=X.A[j];
b=Y.A[j];
a-=Z;
Z=0;

if(a<0)
       {a=0xFF;Z=1;} 
if(a>b)
c=a-b;
else
if(a<b)
{c=a-b+256; Z=1;}
else c=0;
X.A[j]=c;
}
*(this)=X;
ABC=X;
return ABC;
}

//multiplication operator
IHO IHO:: operator *(IHO B)
{
int i, j;
unsigned char Z[N]={0};
for(i=0; i<N; i++)
Z[i]=0;
 unsigned long a,b,c;
 unsigned long* h;
for(i=0; i<N; i++)
         for(j=0; j<N; j++ )
         {
         a=A[i];
         b=B.A[j];
         c=a*b;
         
         h=(unsigned long*)&Z[i+j];

         *h += c;
         }

IHO T;
int p=0;
for(i=N-1; i>=0; i--)
T.A[i]=Z[i];

return T;

}

//bit offset function to lower digits
void IHO::operator >>(int n)
{
int i,j;
for(i=N-1; i>0; i--)
{

A[i]=A[i]<<1;
if( (A[i-1]&0x80))
A[i]|=1;

}
A[0]=A[0]<<1;

}
//bit offset function to higher digits
void IHO::operator <<(int n)
{
int i,j;

for(i=0; i<(N-1); i++)
{
A[i]=A[i]>>1;
if( (A[i+1]&1))
A[i]|=0x80;
else
A[i]&=0x7F;
}
A[N-1]=A[N-1]>>1;

}
//division function
void IHO::HANA_Dil(IHO B,IHO* ABC)
{

 IHO C,D,U,SD;


 while(*this >B==1)
 {

     for(int i=0; i<N; i++)
     SD.A[i]=0;
     SD.A[0]=1;
     for(int i=0; i<N; i++)
     C.A[i]=B.A[i];
     

     while(*this > C ==1)
     {
     C>>1;
     SD>>1;
     } 
   
     
     C<<1;
     SD<<1;
 D +=SD;
     *this -= C;
 }

  for(int i=0; i<N;i++)
  ABC->A[i]=D.A[i];

 cout<<dec;
}

//balance finding function
IHO IHO::operator %(IHO B)
{

 IHO C,D,U,SD, ST;
 ST=*this;
 while((ST >B) ==1)
 {

     for(int i=0; i<N; i++) SD.A[i]=0;
     SD.A[0]=1;
     for(int i=0; i<N; i++) C.A[i]=B.A[i];
     

     while((ST > C) ==1)
     {
     C>>1;
     SD>>1;
     } 
   
     
     C<<1;
     SD<<1;
     D += SD;
     ST -= C;
 }


return ST;
 cout<<dec;
}

//division function
IHO IHO::operator /(IHO B)
{

 IHO C,D,U,SD, ST;
 ST=*this;

 while((ST >B) ==1)
 {

     for(int i=0; i<N; i++)
     SD.A[i]=0;
     SD.A[0]=1;
     for(int i=0; i<N; i++)
     C.A[i]=B.A[i];

     while((ST > C) ==1)
     {
     C>>1;
     SD>>1;
     } 
     C<<1;
     SD<<1;
     D += SD;
     ST -= C;
 }
  for(int i=0; i<N;i++)
  {ST.A[i]=D.A[i]; }
cout<<dec;
return ST;
 
}

void IHO::HANA_10(unsigned char* h)
{
     
int n=0;
IHO B;
unsigned char D[9] ="A";
B.OLIA(&D[0]);

while(this->PER_10()==1)
                        {
                        IHO C;
                        
                        this->HANA_Dil(B, &C);
                        D[n]=A[0]+'0';
                        n++;
                     
                        for(int i=0; i<N; i++)
                        A[i]=C.A[i];
                        }

D[n]=A[0]+'0';
int m=0;
for(int i=n; i>=0;i--)
{*(h+m)=D[i]; m++;}
}

int IHO:: PER_10()
{
unsigned char B[N]={0};
B[0]=10;
int i=N-1;
while(A[i]==0)
i--;
if(A[i]>=B[i])
return 1;
else
return 0;
}
//HANECHKA 
void IHO::HANECHKA(unsigned char* h)
{
unsigned char H[N]={0};
unsigned int i, q,j,k,n,a,b,c;
for(i=0; i<N; i++) A[i]=0;
q=0;
while(*(h+q)!=0)
{
for(j=0; j<N;j++) H[j]=A[j];
for(i=N-1; i>0; i--)
{
A[i]<<=1; if(A[i-1]&0x80) A[i]|=1;
}
A[0]<<=1;
for(j=0; j<3;j++){
for(i=N-1; i>0; i--)
{
H[i]<<=1; if(H[i-1]&0x80) H[i]|=1;
}
H[0]<<=1;
}

k=0;
for(i=0; i<N; i++)
{a=A[i]; b=H[i]; c=a+b+k; A[i]=c; k=((c>>8)&1);}

b=*(h+q)-'0';
k=0;
for(i=0; i<N; i++)
{a=A[i];  c=a+b+k; A[i]=c; k=((c>>8)&1); b=0;}
q++;
}

}
//modular exposition
IHO IHO::EXPM(IHO B,IHO M)
{
 IHO R;
 R.A[0]=1;

  int m=127;

 while(m>=0)
            {
            R= R * R;
            R= R % M;
            if(B.SB(m)!=0)
            R = (R * *this) % M;
            m--;
            }  
 return R;
}

int IHO::SB ( unsigned int n)
{
unsigned int i= n/8;
unsigned int s= n%8;
if((A[i]&(1<<s))==0)
return 0; 
return 1;
}

void IHO:: longA(unsigned long K)
{
A[0]=K;
A[1]=K>>8;
A[2]=K>>16;
A[3]=K>>24;
}

unsigned long IHO::BUBU()
{
unsigned long D= A[0]+(A[1]<<8)+ (A[2]<<16)+ (A[3]<<24);
return D;
}



IHO IHO::GEN_P()
{
unsigned char R[53];
unsigned char TA[5][4]={{0x03,0x5D,0x1F,0x40},{0x9D,0x40,0x91,0x49},{0xB0,0x98,0x17,0x2E},{0x75,0x09,0x8F,0x45},{0xF7,0x2C,0xD4,0x4A}};

int m, n,k, i,j,h;
unsigned long b=0;
   IHO D,C,P;
m=0; k=0; h=0;
for( i=3; i<256; i++)
        {int f=0;
         for( j=2; j<=i/2; j++)
                 if(i%j==0)
                 f=1;
         if(f==0)
         {R[m]=i; m++;}      
        }    
 int f=0;       
     do
     {
       f=0; 
        //Generation of random number
       for( i=0; i<N; i++)  P.A[i]=rand()&0xFF;
            P.A[0]|=1;
            P.A[N-1]|=0x50;
            P.A[N-1]&=0x7F;  
           // unsigned char ABC[200]="31991";
           // HANECHKA(&ABC[0]);
            
       for( i=0; i<m; i++) // Cheking that number divided by array of prime 
        {
        D.A[0]=R[i];
        C= P % D;
        if( C.A[0] == 0) f=1; 
        }
        h=0;
 unsigned char A3[100]={0};
P.HANA_10(&A3[0]);
cout<<"\n MOO= "<<A3;

        while(f!=1 && h<5)
        {//A
           f=0;
           D=P;
           D.A[0]&=0xFE; //D=p-1
           while((D.A[0]&1)==0) //calculate m
           {b++; D<<1;}    


           for(i=4; i<N*2; i++) C.A[i]=0;//C is random A
          for(i=0; i<4; i++) C.A[i]=TA[h][i];
           h++;
          
unsigned char A1[N*2]={0};
C.HANA_10(&A1[0]);
cout<<"\n A= "<<A1;
D.HANA_10(&A1[0]);
cout<<"\n E= "<<A1;
P.HANA_10(&A1[0]);
cout<<"\n M= "<<A1;


           C= C.EXPM(D,P);  j=0;// C=Z=(A^m)modP          
           C.A[0]-=1;
           i=0;
       
           while((C.A[i]==0) && (i<N)) i++;//IF C=Z==1
          // cout<<"\n HANA"; 
           if(i==N) f=2;
           C.A[0]+=1;

           P.A[0]-=1;
           i=0;
           while((C.A[i]==P.A[i])&& (i<N))    i++;//IF C=Z=P-1
           if(i==N) f=2;
          P.A[0]+=1;

           while(f==0)
           {  //B
             P.A[0]-=1;
             i=0;
             while((i<N)&&(C.A[i]==P.A[i]))  i++;//IF C=Z=P-1
             if(i==N) f=2; //f==2 prime number
             P.A[0]+=1;

             if(f==0)
             {
                      C.A[0]-=1;
                      i=0;
                      while(C.A[i]==0 && i<N) i++;//IF C=Z==1
                      if(i==N) f=1;  //f==1 p- not prime number
                      C.A[0]+=1; 
                      if(f==0)
                              if(j==b) f=3;
                              else
                              {
                              j++;
                               C= C * C; //Calculate C=Z=(Z^2)modP
                               C= C % P;
                              }
             }
             cout<<"\n Lovely HANA";
           }//B

           cout<<"\nDear Olia f="<<f<<" h= "<<h;
        
        }//A
        cout<<"\n Dear INNA f="<<f;
     }while(f==1);
cout<<"\n HANA F="<<f;
return P;
}
//encryption function
void IHO::Shifr(unsigned char* h, unsigned char* nn,IHO K, IHO M)
{
IHO AA;
unsigned char S1=0;
unsigned char S2=0;
unsigned char S3[3]={0};

int j=0;
int i=0;
while(*(h+i)!=0){
          if(((*(h+i)>>4)&0x0F)<10)
                 S1=((*(h+i)>>4)&0x0F)+'0';
          else   S1=((*(h+i)>>4)&0x0F)-10+'A';     
          if((*(h+i)&0x0F)<10)
                 S2=(*(h+i)&0x0F)+'0';
          else S2=(*(h+i)&0x0F)-10+'A';   
        
                 S3[0]=S1;
                 S3[1]=S2;
          AA.OLIA(&S3[0]);
          AA= AA.EXPM(K,M);
for(int m=2; m>=0; m--)
        {*(nn+j)=AA.A[m]; j++;  }   
i++;
}
*(nn+j)=0;
*(nn+j+1)=0;
*(nn+j+2)=0;
i=0;
}
//decryption function
void IHO::DeShifr(unsigned char* h, unsigned char* nn,IHO K2, IHO M)
{

int j=0;
int i=0;
while(*(h+i)!=0 || *(h+i+1)!=0 || *(h+i+2)!=0)
        {
                IHO AA;
                AA.A[0]=*(h+i+2); 
                AA.A[1]= *(h+i+1); 
                AA.A[2]=*(h+i); 
               AA=AA.EXPM(K2,M);
                *(nn+j)=AA.A[0];
                j++;
                i+=3;
        }        
}


void ProstiChisla();

int main()
{
IHO A,B,M,R,D,F,P;
IHO K1,K2,pci, H,K;
IHO ARA;
unsigned char SA[100]="1EB";
unsigned char SB[100]="23B";
unsigned char SK1[100]="295";
unsigned char SK2[100]="279D";
unsigned char SD[100]="1";
unsigned char SR[100]={0};
unsigned char SRR[100]={0};

K1.OLIA(&SK1[0]);
K2.OLIA(&SK2[0]);
A.OLIA(&SA[0]);
B.OLIA(&SB[0]);
P.OLIA(&SD[0]);
M= A*B; //modul

unsigned char SS[100]={0};
unsigned char S1={0};
unsigned char HHH[100]={0};
cout<<"\n Enter the message using the capital letters. If you want to stop enter 0 and press button Enter\n";
unsigned char c=0;
int m=0;
int f=1;
do
{
cin>>c;
if(c=='0')
f=0;
else
SS[m]=c;
m++;
}while(f==1);
ARA.Shifr(&SS[0],&HHH[0],K1,M);
int i=0;
cout<<"\n Shifr \n";
          while(HHH[i]!=0|| (HHH[i+1]!=0) || (HHH[i+2]!=0)){
          cout<<" "<<hex<<HHH[i]+0<<" "<<HHH[i+1]+0<<HHH[i+2]+0<<dec; i+=3;}
char ss='N'; cout<<"   N="<<ss+0;


unsigned char HH[100]={0};
ARA.DeShifr(&HHH[0],&HH[0],K2,M);
i=0;
cout<<"\n If you want to decording enter 1\n";
int d;
cin>>d;
if(d==1){
cout<<"\n Deshifr\n";
          while(HH[i]!=0)
          cout<<HH[i++];
}
int dd;
cin>> dd;
}


void ProstiChisla()
{
unsigned char A[200]={0};
int m=0;
for(int i=3; i<256; i++)
        {int f=0;
         for(int j=2; j<=i/2; j++)
                 if(i%j==0)
                 f=1;
         if(f==0)
         {A[m]=i; m++; cout<<" "<<A[m-1]+0;}      
         if(m%5 ==0)
         cout<<"\n";
        }    
cout<<"\n"<<m-1;
            
}

