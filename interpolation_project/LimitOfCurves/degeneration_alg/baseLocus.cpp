#include <iostream>
#include <glpk.h>
#include "baseLocus.h"

using namespace std;

HomInterProblem::HomInterProblem(int d_, int m_, int n_): d(d_), m(m_), n(n_){}
bool HomInterProblem::findBaseLocus(){
  int expDim=(d*d + 3*d + 2 - n *m *(m+1) )/2;

  /*Let D=eH - sum m_i E_i
    a_i= #{m_j=i}, for i ranging from 1,..,m

    The system is
    (e^2+3e) - sum_i a_i (i+1)i >=0
    a_1+...+a_m <= n
    maximize
    ((e-1)(e-2)/2 - sum_i i*(i-1)/2 a_i) -1 -(de - m( sum_i i a_i))

    If the optimum value is greater or equal to zero, 
    this class could potentially be in the base locus.

    If the optimum value is smaller than zero, then there is
    no curve in the base locus!

    Simplifying the system:
    conditions: sum_i a_i(i+1)i <= e^2 +3e
    number of points: a_1+...+a_m <= n
    maximize 
    sum_i (mi - i*(i-1)/2) a_i

   */
  cout<<"Finding possible curves in base locus:"<<endl;
  glp_prob *lp;

 //turn messages off
  glp_iocp intSilent;
  glp_smcp simplexSilent;
  glp_init_iocp(&intSilent);
  glp_init_smcp(&simplexSilent);
  intSilent.msg_lev=GLP_MSG_ERR;
  simplexSilent.msg_lev=GLP_MSG_ERR;
  

  for(int e=1;e<=d;e++){
    lp=glp_create_prob();
    glp_set_prob_name(lp,"Base Locus Finder");
    glp_set_obj_dir(lp, GLP_MAX);
    glp_add_rows(lp,2);
    glp_set_row_name(lp,1,"conditions");
    glp_set_row_bnds(lp,1,GLP_UP,0.0, e*e +3*e);
    glp_set_row_name(lp,2,"number of points");
    glp_set_row_bnds(lp,2,GLP_UP,0.0, n);
    glp_add_cols(lp,m);
    int counter=1;
    int ia[1000], ja[1000];
    double ra[1000];
    for(int i=1;i<=m;i++){
      glp_set_col_name(lp,i,"a");
      glp_set_col_bnds(lp,i,GLP_LO,0.0,0.0);
      glp_set_col_kind(lp,i,GLP_IV);
      glp_set_obj_coef(lp,i,m*i-((i*(i-1))/2));

      ia[counter]=1;
      ja[counter]=i;
      ra[counter]=i*(i+1);
      counter++;
      ia[counter]=2;
      ja[counter]=i;
      ra[counter]=1;
      counter++;

    }

    glp_load_matrix(lp,counter-1, ia,ja,ra);

   
    glp_std_basis(lp);
    //    glp_adv_basis(lp, NULL);
    glp_simplex(lp, &simplexSilent);
    glp_intopt(lp, &intSilent);
    int solution=glp_mip_obj_val(lp);


    //solution =  sum_i (mi - i*(i-1)/2) a_i
    // degreeGap=((e-1)(e-2)/2 - sum_i i*(i-1)/2 a_i) -1 -(de - m( sum_i i a_i))

    int degreeGap= solution+ (e*e -3*e)/2 - d*e;
    //  cout<<"Best result for degree "<<e<<" has degree gap:"<<degreeGap<<endl; 
    
  if(degreeGap+expDim>=0){
    
      cout<<"Best result for degree "<<e<<" has degree gap:"<<degreeGap<<endl; 
      for(int i=1;i<=m;i++)
	cout<<"a_"<<i<<"= "<<glp_mip_col_val(lp,i)<<endl;
      if(degreeGap>=0){
	glp_delete_prob(lp);
	return true;
      }
    }
    glp_delete_prob(lp);
  }
  cout<<"No curves in base locus! (or the system is special)"<<endl;
  return false;
}
