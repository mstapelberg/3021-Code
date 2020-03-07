#include <iostream>
#include <vector>
#include <algorithm>
#include "TRandomGen.h"
#include "TH2I.h"
#include "TMath.h"

double en_fun(int p, int A, int B){
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
        //else if (A == B && A == 2){
            //return 1;
        //}
        else if(A  > B){
            return p_b_ps;///(p_b_pp + p_b_ps + p_b_sp);
        }
        else{
            return p_b_sp;///(p_b_pp + p_b_ps + p_b_sp);
        }
    
}
/*
double en_fun(int p, int A,int B){
    double k_b = 8.617E-5;
    double T = 298;
    double k = 1E-3;
    double DeltaE;
    double p_b;

    DeltaE = 1.0/2.0 * k * TMath::Power(p,2);
    std::cout << " Delta E = " << DeltaE << std::endl;

    p_b = TMath::Exp(-DeltaE/(k_b * T)); 
    std::cout << " p_b = " <<  p_b << std::endl;

return p_b;
}
*/
int * mover(double rand, int cell_pos_x, int cell_pos_y, int suborpill, int n, int m, int p_move){
    double l_c = 0.25;
    double r_c = 0.5;
    double u_c = 0.75;
    int p;

    static int temp[2]; //temp[0] is x coord and temp [1] is y coord
    temp[0] = cell_pos_x; //initializes the x pos
    temp[1] = cell_pos_y; //initializes the y pos 
    /*
    if (cell_pos_x%p == 0 && cell_pos_y%p == 0){ //On a pillar
        p = p_move;
    }
    else{
        p = 1;
    }
    */


    if (suborpill == 0){ //if on the substrate
        p = 1;
    }
    else if (suborpill == 2){ //if on the cell move as on substrate
        p = 1;
    }
    else{ //if on pillar move on the pillars 
        p = p_move;
    }

    if (0 <= rand && rand <= l_c){                  //left move command
        if (cell_pos_x > p){
            temp[0] = cell_pos_x - p;               //determines if there is enough space to move to left
            std::cout << " The cell x pos is now " << temp[0] << std::endl;
        }
        else{
            temp[0] = cell_pos_x;
        }                                           //end of left movement statement 
    }
    else if( l_c < rand && rand <= r_c){
        if (cell_pos_x < n-p){                      //determines if there is enough space to move to right
            temp[0] = cell_pos_x + p;
            std::cout << " The cell x pos is now " << temp[0] << std::endl;

        }
        else{
            temp[0] = cell_pos_x; 
        }                                           //end of right move
    }
    else if(r_c < rand && rand < u_c){
        if (cell_pos_y > p){                        //determines if there is enough space to "up" 
            temp[1] = cell_pos_y - p;               //(which is really down the matrix)
            std::cout << " The cell y pos is now " << temp[1] << std::endl;

        }
        else {
            temp[1] = cell_pos_y;
        }                                           //end of up move
    }
    else if(rand > u_c){
        if (cell_pos_y < m-p){                      //determines if there is enough space to go down
            temp[1] = cell_pos_y + p;
            std::cout << " The cell y pos is now " << temp[1] << std::endl;

        }
        else{
            temp[1] = cell_pos_y;
        }
    }                                               //end of down move
    return temp;
}                                                   //end of mover function

void ft5(){
    /* *************************USER INPUT AREA *************************/
    const int m = 50;
    const int n = 50;
    const int p = 2;

    int cell_pos_x = 0;
    int cell_pos_y = 0;
    int n_trials = 5000;

    double p_B, move_prob;
    double l_c = 0.25, r_c = 0.5, u_c = 0.75, d_c = 1.0; 

    TRandomMixMax256 *gr = new TRandomMixMax256();

    std::vector<std::vector<int>> matrix(m,std::vector<int>(n,0));
    if (m%p != 0 || n%p){
        std::cout << "Error you have selected a pillar spacing that does not divide your number of columns right" << std::endl;
    }

    //loop to build first row of substrate 
    std::vector<int> vals((unsigned)n);
    std::fill(vals.begin(), vals.end(),0); //fills (1,n) matrix with 0s

    for (int i = 0; i < vals.size(); i++){
        if (i%p == 0){
            vals[i] = 1;
        }
        else{
            vals[i] = 0;
        }
    }

    //fill the rows of the main matrix accordingly
    for ( int i = 0 ; i < matrix.size(); i++ ){
        if (i%p == 0){//Spaces in the vertical direction
            matrix[i] = vals;
        }
        else{
            std::fill(matrix[i].begin(), matrix[i].end(), 0); //fills row with 0s
        }
    }
/*
    //prints out the vector 
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            std::cout << matrix[i][j] << " "; 
        }
        std::cout << std::endl;
    }
*/
    matrix[cell_pos_x][cell_pos_y] = 2; //places the cell in the inital position
    int * cell_coor;
    int i = 0;

    while(i < n_trials){
        double move_dir = gr->Rndm();
        cell_coor = mover(move_dir, cell_pos_x, cell_pos_y,matrix[cell_pos_x][cell_pos_y], n, m, p);               //mover driver
        p_B = en_fun(p, matrix[cell_pos_x][cell_pos_y], matrix[cell_coor[0]][cell_coor[1]]);
        move_prob = gr->Rndm(); 
            if (move_prob < p_B){
                cell_pos_x = cell_coor[0];                                          //assigns the temp x to the cell
                cell_pos_y = cell_coor[1];                                          //assigns the temp y to the cell
                matrix[cell_pos_x][cell_pos_y] = 2;                                 //populates element with cell
            }
            else{
                //matrix[cell_coor[0]][cell_coor[1]] = 1;                             //leaves the pillar in place
                continue;
            }
            i = i +1;
    }//end of while statement

    //Print the Matrix
    //Print matrix
     for (int k = 0; k < matrix.size(); k++){
         for (int l = 0; l < matrix[k].size(); l++){
             std::cout << matrix[k][l] << " ";
         }
         std::cout << std::endl;
     }

     //plot the board as 2D hist
     TH2I *h1 = new TH2I("h1", "Board", n+1, 0, n, m+1, 0, m);
     std::cout << "Size of Matrix[0] is" << matrix[0].size() << std::endl;
     for (int i = 0; i < n; ++i){
         for (int j = 0; j < m; ++j){
             h1->SetBinContent(i,j, matrix[i][j]);
         }
     }
     h1->Draw("COLZ");
}//end of main
