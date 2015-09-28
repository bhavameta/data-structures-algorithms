#include <iostream>
#include <Eigen/Dense>
#include <stdio.h>
#include <float.h>
#include <iostream>
#include <math.h>

using namespace Eigen;
using namespace std;

 MatrixXd A;
 MatrixXd b;
 MatrixXd c;
 MatrixXd v;

MatrixXd optimum_vtx;
double optimum_val;
int m,n ;
int flag= 0;
double eps= 1.8;

typedef struct {
       MatrixXd P;
       MatrixXd Q;
       MatrixXd R;
       MatrixXd S;
 } vinfo;
 vinfo tmp ;

void getinput(const char *filename, const char *vertex, const char *cost);
vinfo simplex_v(MatrixXd V);
vinfo factorize(MatrixXd V);
double point_cost(MatrixXd V);
MatrixXd get_nbr(vinfo vinf, MatrixXd V);
MatrixXd get_vertex(vinfo vinf, MatrixXd V);
bool check_feasible(MatrixXd V);
bool is_unbounded(MatrixXd A, MatrixXd b);
void change_sys(void);
void change_degen(void);

int main()
{
    getinput("system.txt", "vertex.txt", "cost.txt");
    cout<<"Given system"<<endl;
    cout<<endl;
    cout<<A <<endl ;
    cout<<endl;
    cout<<b <<endl;
    cout<<endl;
    cout<<"Given cost matrix"<<endl;
    cout<<endl;
    cout<<c <<endl;
    cout<<endl;
    cout<<"Given initial vertex"<<endl;
    cout<<endl;
    cout<<v <<endl;
    cout<<endl;
    vinfo R,T;

    double bmin= 1;
    for(int i=0; i<m-1; i++)
    {
        if((b(i,0)<=0))
            continue;
        else if(b(i,0)<bmin )
             bmin= b(i,0);
        else
            continue;
    }

    if(bmin>0)
    {
        eps= bmin/1.8 ;
    }
    tmp.P= A; tmp.Q= b;
    tmp.R= c; tmp.S= v;

    if(check_feasible(v)==0)
    {m++; n++;

    while(check_feasible(v)==0)
    {
        eps= eps/2 ;
        change_sys();
        T= simplex_v(v) ;
        //check if sysetm is infeasible
        if(optimum_vtx(n-1,0)< 0)
            {
                cout<<"system is infeasible..exiting"<<endl ;
                cout<<endl ;
                cout<<optimum_vtx(n-1,0)<<endl;
                cin>>flag ;
                return 0;
            }
            v.resize(n-1,1);
            v= optimum_vtx.block(0,0,n-1,1);
            cout<<v;
    }
        //again swith back to original sytem with feasible point
        A= tmp.P; b=tmp.Q;
        c=tmp.R; v=optimum_vtx.block(0,0,n-1,1);
        m--; n-- ;

    cout<<A <<endl ;
    cout<<endl;
    cout<<b <<endl;
    cout<<endl;
    cout<<"Given cost matrix"<<endl;
    cout<<endl;
    cout<<c <<endl;
    cout<<endl;
    cout<<"Given initial vertex"<<endl;
    cout<<endl;
    cout<<v <<endl;
    cout<<endl;
    }

    R= simplex_v(v) ;
    //check if system is unbounded
    if(flag==1)
    {   cin>>flag;
        return 0; }

    cout<<"Final Sets: Ad, Add, bd, bdd"<<endl;
    cout<<endl;
    cout<< R.P<<endl;
    cout<<endl;
    cout<< R.Q<<endl;
    cout<<endl;
    cout<< R.R<<endl;
    cout<<endl;
    cout<< R.S<<endl;
    cout<<endl;
    cout<<"optimal vertex"<<endl;
    cout<<endl;
    cout<< optimum_vtx<<endl;
    cout<<endl;
    cout<<"optimal cost"<<endl;
    cout<<endl;
    cout<< optimum_val<<endl;
    cout<<endl;

    int k;
    cin>>k ;
}


vinfo simplex_v(MatrixXd V)
{
    vinfo vdata;
    vdata= factorize(V);

    if(vdata.P.cols()==1)
       {  if(vdata.P(0,0)==-1)
           {
             change_degen();
             return simplex_v(V) ;
           }
       }

    cout<<"untight rows at the point"<<endl;
    cout<<endl;
    cout<<vdata.Q<<endl;
    cout<<endl;
    cout<<vdata.S<<endl;
    cout<<endl;
    if(vdata.P.rows()!= n)
    {
        V= get_vertex(vdata, V);
        cout<<"finding vertex..solution"<<endl;
        cout<<endl;
        cout<<V<<endl ;
        cout<<endl;
        return simplex_v(V) ;
    }
    double cost=0;
    cost= point_cost(V);
    MatrixXd nbr ;

    vdata= factorize(V);
    nbr= get_nbr(vdata, V) ;

    if((nbr.rows() == 1)&&(nbr(0,0)== 0))
    {
        flag= 1;
        return vdata;
    }

    cout<<"next neighbour: solution"<<endl ;
    cout<<endl;
    cout<<nbr<<endl;
    cout<<endl;
    MatrixXd nullmat(1,1);
    nullmat << -1;

    if((nbr.rows() == 1)&&(nbr(0,0)== -1))
        {
            optimum_vtx= V;
            optimum_val= cost ;
            return vdata;
        }
    else
        {
            return simplex_v(nbr);
        }
}

MatrixXd get_vertex(vinfo vinf, MatrixXd V)
{
    MatrixXd B;
    MatrixXd dir;
    dir.resize(n,1);

    if(vinf.P.rows()== 0)
    {
        dir(0,0)= 1;
        for(int i=1; i<n; i++)
            dir(i,0)= 0 ;
    }
    else
    {
        B= vinf.P.fullPivLu().kernel();
        dir= B.block(0,0,n,1);
    }
    cout<<"direction"<<endl;
    cout<<dir<<endl;
    cout<<endl;
        //cout<<vinf.P;
        //cout<<"nullspace"<<endl;
        //cout<<endl;
        //cout<<B<<endl;
        //cout<<endl;

        double T;
        double U;
        double Utight;
        double mag= 0 ;
        int j=0;
        int tight=0;

        for(j=0; j<vinf.Q.rows(); j++)
    {
        double val= 0;
        MatrixXd temp;
        MatrixXd temp1;
//        cout<<vinf.P<<endl ;
//        cout<<vinf.R<<endl ;
//        cout<<vinf.Q<<endl ;
//        cout<<vinf.S<<endl ;
//        cout<<endl ;
        temp = vinf.Q.block(j,0,1,n)*V ;
        T= vinf.S.block(j,0,1,1)(0,0)- temp(0,0) ;
        temp1= vinf.Q.block(j,0,1,n)*dir ;
        U= temp1(0,0) ;
        if(U==0)
            continue;

        val= T/U ;

        if(mag==0)
            {mag= T/U ;
             tight= j;}
        else if(abs(val) < abs(mag))
            {mag= val;
            tight= j;
             Utight= U;
             }
         else
            continue ;
    }
    //if(Utight<0)
       return V+ mag*dir ;
}


MatrixXd get_nbr(vinfo vinf, MatrixXd V)
{
   MatrixXd B;
   B= vinf.P.inverse();
   B= -1*B;
   //cout<<B<<endl ;
   MatrixXd newpt;
   int i=0;
   int ubdd=0;

   for(i=0; i<n; i++)
   {
       double cold= point_cost(V);
       double cnew;
       newpt= V + B.block(0,i,n,1);
       cnew= point_cost(newpt) ;
       if(cnew > cold)
         break;
       else
         continue;
   }

   if(i==n)
    {
        MatrixXd nullmat(1,1);
        nullmat << -1;
        return nullmat;
    }
    else
    {
        double T;
        double U;
        double mag= 0 ;
        int j=0;
        int tight=0;

        for(j=0; j<m-n; j++)
    {
        double val= 0;
        MatrixXd temp;
        MatrixXd temp1;
//        cout<<vinf.P<<endl ;
//        cout<<vinf.R<<endl ;
//        cout<<vinf.Q<<endl ;
//        cout<<vinf.S<<endl ;
        temp = vinf.Q.block(j,0,1,n)*V ;
        T= vinf.S.block(j,0,1,1)(0,0)- temp(0,0) ;
        temp1= vinf.Q.block(j,0,1,n)*B.block(0,i,n,1) ;
        U= temp1(0,0) ;
        if(U<=0)
            { ubdd++;
              continue; }

        val= T/U ;

        if(mag==0)
            {mag= T/U ;
             tight= j;}
        else if(val < mag)
            {mag= val;
            tight= j;}
         else
            continue ;
    }

    if(ubdd== m-n)
    {
        cout<<"The system is unbounded..Exiting"<<endl ;
        cout<<endl;
        MatrixXd nullmat(1,1);
        nullmat << 0;
        return nullmat;
    }

    MatrixXd x= V + mag*B.block(0,i,n,1) ;

           return x;
       }
    }

vinfo factorize(MatrixXd V)
{
    MatrixXd Ad;
    MatrixXd Add;
    MatrixXd bd;
    MatrixXd bdd;
    int k=0 ;
    int l=0 ;
    vinfo vdata;

    for(int i=0; i<m; i++)
    {
       MatrixXd p;
       double f=0 ;
       p.resize(1,1) ;
       p(0,0)= 0;
       p= A.block(i,0,1,n)*V ;
       f= p(0,0);
       if(abs(f - b(i,0))<0.0000001)
       {
           k++;
       }
       else
       {
           l++;
       }
    }

    //check is system is degenerate at this vertex
    if(k>n)
    {
        vdata.P.resize(1,1);
        vdata.P(0,0) = -1;
        cout<<"system is degenerate at this vertex..changing system"<<endl ;
        cout<<endl ;
        return vdata;
    }

    Ad.resize(k,n);
    Add.resize(l,n);
    bd.resize(k,1);
    bdd.resize(l,1);
    k=0 ;l= 0 ;

    for(int i=0; i<m; i++)
    {
       MatrixXd p;
       double f=0 ;
       p.resize(1,1);
       p(0,0)= 0;
       p= A.block(i,0,1,n)*V ;
       f= p(0,0);

       if(abs(f - b(i,0))<0.0000001)
       {
           Ad.block(k,0,1,n)= A.block(i,0,1,n) ;
           bd.block(k,0,1,1)= b.block(i,0,1,1) ;
           k++;
       }
       else
       {
           Add.block(l,0,1,n)= A.block(i,0,1,n) ;
           bdd.block(l,0,1,1)= b.block(i,0,1,1) ;
           l++;
       }
    }

     vdata.P= Ad;
     vdata.Q= Add;
     vdata.R= bd;
     vdata.S= bdd;
    //cout<<vdata.Q<<endl;
    //cout<<endl;
    //cout<<vdata.S<<endl;
    //cout<<endl;

     return vdata;
}

double point_cost(MatrixXd V)
{
    MatrixXd m;
    m = c.transpose()*V ;
    double c;
    c = m(0,0);
    return c;
}

void getinput(const char *filename, const char *vertex, const char *cost)
{
   cout<<"enter size of system"<<endl;
   cout<<endl;
   cin>>m;
   cin>>n;
   cout<<endl;
   FILE *afile= fopen(filename,"r");
   FILE *bfile= fopen(vertex,"r");
   FILE *cfile= fopen(cost,"r");
   A.resize(m, n) ;
   b.resize(m, 1) ;
   v.resize(n, 1) ;
   c.resize(n, 1) ;
   int i,j,k,l ;
   for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
         {
             fscanf (afile, "%lf", &A(i,j));
         }
         fscanf (afile, "%lf", &b(i));
    }

    for(k=0; k<n; k++)
     {
        fscanf (bfile, "%lf", &v(k));
     }

     for(l=0; l<n; l++)
     {
        fscanf (cfile, "%lf", &c(l));
     }

     fclose(afile);
     fclose(bfile);
     fclose(cfile);

     return ;
}

bool check_feasible(MatrixXd V)
{
    MatrixXd F= tmp.Q- tmp.P*V ;
    for(int i=0; i<F.rows(); i++)
    {
        if(F(i,0)<0)
            return 0;
    }
       return 1;
}

void change_sys()
{
    A.resize(m, n);
    b.resize(m,1);
    v.resize(n,1);

    A.block(0,0,m-1,n-1)= tmp.P;
    b.block(0,0,m-1,1)= tmp.Q;

    double bmin= b(0,0);

    for(int i=0; i<m-1; i++)
    {
        if(b(i,0)<bmin)
            bmin= b(i,0);
        A(i,n-1)= 1 ;
    }
    b(m-1,0)= -bmin ;

    for(int j=0; j<n; j++)
    {
        A(m-1,j)= 0 ;
    }
    A(m-1,n-1)= -1;

    for(int k=0; k<n; k++)
    {
        if(k<n-1)
            v(k,0)= 0;
        else
            v(k,0)= bmin;
    }

    c.resize(n,1);
    for(int l=0; l<n; l++)
    {
        c(l,0)= 0;
    }
    c(n-1,0)= 1 ;

    for(int i=0; i<b.rows(); i++)
    {
        b(i,0)= b(i,0)+ eps*i ;
    }
//    bool p= check_feasible(v);
//    cout<<p<<endl;
//    cout<<endl;
    cout<<"initial pt. not feasible..searching for it"<<endl;
    cout<<endl;
    cout<<A <<endl ;
    cout<<endl;
    cout<<b <<endl;
    cout<<endl;
    cout<<"New initial vertex"<<endl;
    cout<<endl;
    cout<<v <<endl;
    cout<<endl;
    cout<<c<<endl ;
    cout<<endl ;
}

void change_degen(void)
{
    eps= eps/2 ;
    for(int i=0; i<b.rows(); i++)
    {
        b(i,0)= b(i,0)+ pow(eps,i) ;
    }
}







