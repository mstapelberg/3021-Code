#include<iostream>
#include"TMath.h"


double endrive(int p, int A, int B){
    double k_b = 8.617E-5;
    double T = 298;
    double k;
    double DeltaE;
    double p_b;

    
        double k_pp = 1E-6 * TMath::Power(10,p); //Will get small as p increases
        double k_ps = TMath::Power(10,-p); //Pillar to substrate will get big as p increases  
        double k_sp = 1E-1 * TMath::Power(10, 1/2 * p) ; //Substrate to Pillar
        double DeltaE_pp = 1.0/2.0 * k_pp * TMath::Power(p,2);
        double DeltaE_ps= 1.0/2.0 * k_ps * TMath::Power(p,2);
        double DeltaE_sp = 1.0/2.0 * k_sp * TMath::Power(p,2);
        double p_b_pp = TMath::Exp(-DeltaE_pp/(k_b * T)); 
        double p_b_ps = TMath::Exp(-DeltaE_ps/(k_b * T)); 
        double p_b_sp = TMath::Exp(-DeltaE_sp/(k_b * T)); 
        
        if( A == B){
            return p_b_pp;///(p_b_pp + p_b_ps + p_b_sp);
        }
        else if(A  > B){
            return p_b_ps; ///(p_b_pp + p_b_ps + p_b_sp);
        }
        else{
            return p_b_sp/(p_b_pp + p_b_ps + p_b_sp);
        }
    
}

void enfun(){
    int p = 2;
    int A = 1;
    int B = 0;
    double p_b;
    
    p_b = endrive(p, A, B);

        std::cout << " Value of A is " << A << " Value of B is " << B << std::endl;
        std::cout << " Value of p is " << p << std::endl;
        //DeltaE = 1.0/2.0 * k * TMath::Power(p,2);
        //std::cout << " Delta E = " << DeltaE << std::endl;
        //p_b = TMath::Exp(-DeltaE/(k_b * T)); 
        std::cout << " p_b = " <<  p_b << std::endl;
}
