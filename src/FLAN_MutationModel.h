/**
  * FLAN Software
  *
  * @author 2015-2020 Adrien Mazoyer  <adrien.mazoyer@imag.fr> 
  * @see The GNU Public License (GPL)
  */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef FLAN_MUTATION_MODEL_H
#define FLAN_MUTATION_MODEL_H

#include "FLAN_Clone.h"
using namespace Rcpp ;


class FLAN_MutationModel {
  
private:
    
    FLAN_Clone* mClone;    // Clone object
    
protected:
    
    double mMutNumber;     // Mean number of mutations
    double mFitness;       // Relative fitness
    double mDeath;         // Death probability
    
    bool mLT;              // logical: if TRUE probabilities are P[X <= x]
			   //   otherwise, P[X > x]
    
    NumericVector mSample;
    double mMfn,mCvfn;
    double mScale;
    List mTuning;
    
    
    void init_GFest(){
//       List tu=Environment::global_env().get(".tunings");
      Environment FlanEnv("FlanEnv");
      List tu=FlanEnv.get(".tunings");
      mTuning=tu;
    };
    
public: 

    //  Create an object 
    FLAN_MutationModel(){};
    
    // Create object for GF method
    FLAN_MutationModel(double death,std::string model){
  
      mDeath=death;
      FLAN_Clone* clone;
      
      if(model.compare("LD") == 0){
	clone=new FLAN_ExponentialClone(death);
      }
      if(model.compare("H") == 0){
	clone=new FLAN_DiracClone(death);
      }
      mClone=clone;
    //   mZ4=0.55;
      mLT=true;
    };
    
    // Create object for GF method
    FLAN_MutationModel(double rho,double death,std::string model){
  
      mFitness=rho;
      mDeath=death;
      
      FLAN_Clone* clone;
      
      if(model.compare("LD") == 0){
	clone=new FLAN_ExponentialClone(rho,death);
      }
      if(model.compare("H") == 0){
	clone=new FLAN_DiracClone(rho,death);
      }
      mClone=clone;
      
      mLT=true;
    };
    
    // Create object for distribution
    FLAN_MutationModel(List args){
  
      if(args.size()==5){
	mMutNumber=as<double>(args["mutations"]);
	mFitness=as<double>(args["fitness"]);
	mDeath=as<double>(args["death"]);
	
	std::string model=args["model"];
	
	FLAN_Clone* clone;
	
	if(model.compare("LD") == 0){
	  clone=new FLAN_ExponentialClone(mFitness,mDeath);
	}
	if(model.compare("H") == 0){
	  clone=new FLAN_DiracClone(mFitness,mDeath);
	}
	mClone=clone;
	
	mLT=as<bool>(args["lt"]);
	
      } else if (args.size()==7){
	
	mSample=args["mc"];
	if(!Rf_isNull(args["mfn"])){
	  mMfn=as<double>(args["mfn"]);
	  mCvfn=as<double>(args["cvfn"]);
	} else {
	  mMfn=-1;
	  mCvfn=-1;
	}
	
	mFitness=as<double>(args["fitness"]);
	mDeath=as<double>(args["death"]);
	
	std::string model=args["model"];
	
	FLAN_Clone* clone;
	
	if(model.compare("LD") == 0){
	  clone=new FLAN_ExponentialClone(mFitness,mDeath);
	}
	if(model.compare("H") == 0){
	  clone=new FLAN_DiracClone(mFitness,mDeath);
	}
	mClone=clone;
	
	mScale=as<double>(args["scale"]);
	
	init_GFest();
	
      }

    };
    
    // Destructor
    ~FLAN_MutationModel(){};   
    
    
    // Set attributes
    void setMutNumber(double alpha) {
      mMutNumber=alpha;
    };
    void setFitness(double rho){
      mFitness=rho;
    };
    void setDeath(double death){
      mDeath=death;
    };
    void setClone(FLAN_Clone* clone){
      mClone=clone;
    };
    
//     List getFns(){
//       return mClone->get();
// }
    
    // Get attributes
    
    double getMutNumber(){
      return mMutNumber;
    };
    double getFitness(){
      return mFitness;
    };
    double getDeath(){
      return mDeath;    
    };
    FLAN_Clone* getClone(){
      return mClone;
    };
    
    
    
    // --------------------------
    // Probability methods
    //---------------------------
    
    
    NumericVector computeProbability(int m) ;

    NumericVector deduceProbability(int m,NumericVector& pClone) ;
			
			    
    List computeProbability1DerivativeAlpha(int m
// 					    NumericVector& Q,
// 					    NumericVector& dQ_da
							  )  ;    
    List deduceProbability1DerivativeAlpha(int m,
					    NumericVector& pClone
// 					    NumericVector& Q,
// 					    NumericVector& dQ_da
							 )  ;
    
					      
    List computeProbability1DerivativeRho(int m
// 					  NumericVector& Q,
// 					  NumericVector& dQ_dr
							)  ;
    List deduceProbability1DerivativeRho(int m,
					  NumericVector& pClone,
					  NumericVector& dpClone_r
// 					  NumericVector& Q,
// 					  NumericVector& dQ_dr
						       ) ;
    
					    
    List computeProbability1DerivativesAlphaRho(int m
// 						NumericVector& Q,
// 						NumericVector& dQ_da,
// 						NumericVector& dQ_dr
					       )  ;
    List deduceProbability1DerivativesAlphaRho(int m,
						NumericVector& pClone,
						NumericVector& dpClone_r
// 						NumericVector& Q,
// 						NumericVector& dQ_da,
// 						NumericVector& dQ_dr
					      )  ;
    
//     void computeProbability1Derivatives(int m,double alpha,double rho,double death) ;
    
    NumericVector computeCumulativeFunction(int m) ;
    
    
    
    //  compute the Generating function and its derivative
//     double computeGeneratingFunction(double z)  ;
//     double computeGeneratingFunctionDerivative(double z)  ;
//    
//     // --------------------
//     // GF ESTIMATION covariance methods
//     // -------------------
    
    List MutationGFEstimation();
    
    double computeGeneratingFunction(double z);
    
// 
    double covariance2(double z1, double z2) ;
//     
    NumericMatrix covariance(double z1,double z2,double z3) ;
//     
// 		    
//     // Unbiased estimation of pi and its standart deviation if fluctuation of final counts
    List unbiasPiEstimation(double sd, double z,
			    double mfn,double cvfn);

};
#endif
