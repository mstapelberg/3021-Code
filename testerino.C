#include<iostream>
#include"TMath.h"


double testerino(){
    //ENERGY FUNCTIONS CALCULATIONS THE PROBABILITY OF GOING ONTO A PILLAR 
    //WILL IMPLEMENT THE INSTANCE WHERE IT LANDS ON ITSELF
    double p = 2;
    double B = 1;
    double p_B;
    double p_pill = 1.0/double(p);
    double DeltaE;
    double k = 10E-5; //PLAY WITH THIS 
    double T = 298; //KELVIN
    double k_b = 8.617E-5; //eV/K

    p_B = 1/p;
    DeltaE = 0.5 * k * TMath::Power(p_B, 2);

    std::cout << TMath::Exp((-1)*DeltaE/(k_b * T)) << std::endl;
    return 0;
}
