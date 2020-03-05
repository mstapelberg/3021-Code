#include<iostream>
#include<vector>
#include<algorithm>
#include"TH2I.h"


double en_fun(int p, int B){
    //ENERGY FUNCTIONS CALCULATIONS THE PROBABILITY OF GOING ONTO A PILLAR 
    //WILL IMPLEMENT THE INSTANCE WHERE IT LANDS ON ITSELF
    double p_B;
    double p_pill = 1 -1/double(p);
    if (B==1){
        p_B = 1 - p_pill;
    }
    else{
        p_B = 1;
    }
    return p_B;
}

void board(){
    

    const int m = 101; //number of rows add 1 to desired value
    const int n = 101; //number of columns add 1 to desired value
    const int p = 1; //pillar spacing
    //std::vector<int> vals{1, 2, 3, 4, 5};
    //std::vector<std::vector<int>> mymatrix(m, std::vector<int>(n,))
    std::vector<std::vector<int>> matrix(m,std::vector<int>(n,0));
    if (m%p != 0 || n%p != 0){
        std::cout << "Error - spacing and mesh are incompatible, make sure that p (spacing) divides m (number of rows) and n (number of columns) evenly." << std::endl;
    }
    //loop for individual row
    std::vector<int> vals((unsigned)n);
    std::fill(vals.begin(), vals.end(),0);
    for (int i = 0; i < vals.size(); i++){
        if (i== 0 || i%p ==0){
            vals[i] = 1;
        }
        //else{
            //vals[i] = 0;
        //}
    }



    //to fill the rows
    for (int i = 0; i < matrix.size(); i++){
        if (i==0 || i%p == 0){//Spaces in the vertical direction
            matrix[i] = vals;
        }
        else{
            std::fill(matrix[i].begin(), matrix[i].end(),0); //fills row with 0s
        }
    }

    //prints vector
    //for (int i = 0; i < matrix.size(); i++){
        //for (int j = 0; j < matrix[i].size(); j++){
            //std::cout << matrix[i][j] << " ";
        //}
        //std::cout << std::endl;
    //}


    //plot the board as 2D hist
    TH2I *h1 = new TH2I("h1", "Board", n, 0, n, m, 0, m);
    //std::cout << "Size of Matrix[0] is" << matrix[0].size() << std::endl; 
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            h1->SetBinContent(i,j, matrix[i][j]);
        }
    }
    h1->Draw("COLZ");
}
