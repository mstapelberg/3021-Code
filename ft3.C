#include<iostream>
#include<vector>
#include<algorithm>
#include"TRandomGen.h"

double en_fun(int p, int B){
    //ENERGY FUNCTIONS CALCULATIONS THE PROBABILITY OF GOING ONTO A PILLAR 
    //WILL IMPLEMENT THE INSTANCE WHERE IT LANDS ON ITSELF
    double p_B;
    double p_pill = 1.0 -1.0/double(p);
    if (B==1){
        p_B = 1.0 - p_pill;
    }
    else{
        p_B = 1.0;
    }
    return p_B;
}
int * mover(double rand, int cell_pos_x, int cell_pos_y, int n, int m){
       double left_cut = 0.25;
       double right_cut = 0.5;
       double up_cut = 0.75;
       //double down_cut = 1.0;
       static int temp[2]; //temp[0] is x coord, temp[1] is y coord
       temp[0] = cell_pos_x; //initializes the x pos
       temp[1] = cell_pos_y; //initializes the y pos
            if (0 <= rand && rand <= left_cut){
                if (cell_pos_x != 0){             //determines if at the left edge of the board
                    temp[0] = cell_pos_x - 1;        //moves cell to left
                    std::cout << "The cell x pos is now " << temp[0] << std::endl;
                }
                else{
                    temp[0] = cell_pos_x;
                }
            }                                     //end of left movement statement
            //Right Move
            else if (left_cut < rand && rand <=right_cut){
                if (cell_pos_x != n){               //determines if cell is at right bound
                    temp[0] = cell_pos_x + 1;
                    std::cout << "The cell x pos is now " << temp[0] << std::endl;
                }
                else{
                    //cell_pos_x = cell_pos_x +1;     //moves cell to right
                    temp[0] = cell_pos_x;
                }
                //break;
            }                                       //end of right movement statement

            //Up Move
            else if (right_cut < rand && rand <= up_cut){
                if (cell_pos_y != 0){               //checks if the cell is at the top of the matrix
                    temp[1] = cell_pos_y -1;         //moves cell up
                    std::cout << "The cell y pos is now " << temp[1] << std::endl;
                }
               else{
                    temp[1] = cell_pos_y;            //does not change
               }
            }
            //Down Move
            else{
                if (cell_pos_y != m){               //checks if the cell is at the bottom of the matrix
                    temp[1] = cell_pos_y + 1;          //moves cell down
                    std::cout << "The cell y pos is now " << temp[1] << std::endl;
                }
                else{
                    temp[1] = cell_pos_y;
                }
            }                                       //end of up movement
            return temp;
   }
void ft3(){
    const int m = 100; //number of rows add 1 to desired value
    const int n = 100; //number of columns add 1 to desired value
    const int p = 4; //pillar spacing
    int cell_pos_x = 50;
    int cell_pos_y = 50;
    double p_B, move_prob;
    int n_trials = 2000;
    double left_cut = 0.25;
    double right_cut = 0.5;
    double up_cut = 0.75;
    double down_cut = 1.0;

    TRandomMixMax256 *gr = new TRandomMixMax256();

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
    //BIG LOOP
    //int * mover(double rand, int cell_pos_x, int cell_pos_y, int n, int m){

    matrix[cell_pos_x][cell_pos_y] = 2;
    int * cell_coor;
    for (int i = 0; i < n_trials; i++){
            double move_dir = gr->Rndm();
            cell_coor = mover(move_dir, cell_pos_x, cell_pos_y, n, m);                                    // Classifier if statements
            if (matrix[cell_coor[0]][cell_coor[1]] == 1){    // if there is a pillar in the move direction
                p_B = en_fun(p, matrix[cell_coor[0]][cell_coor[1]]);
                move_prob = gr->Rndm();
                if (move_prob < p_B){
                    cell_pos_x = cell_coor[0]; //assigns the temp x to the cell
                    cell_pos_y = cell_coor[1]; //assigns the temp y to the cell
                    matrix[cell_pos_x][cell_pos_y] = 2; //covers pillar in cell
                }
                else{
                    matrix[cell_coor[0]][cell_coor[1]] = 1; //leaves pillar in place
                }
            }//end of if ==1 statement
            /*
            else if(matrix[cell_pos_x][cell_pos_y] == 2 && move_dir < left_cut && cell_coor[0]-1 >= 0){ //if we encounter another cell on the left
               matrix[cell_coor[0]][cell_coor[1]] =2;
               matrix[cell_coor[0]-1][cell_coor[1]] =2;
            }
            
            else if(matrix[cell_pos_x][cell_pos_y] == 2 && move_dir > left_cut && move_dir < right_cut && cell_coor[0]+1 <= n){ //if we encounter another cell on the right  
               matrix[cell_coor[0]][cell_coor[1]] =2;
               matrix[cell_coor[0]+1][cell_coor[1]] =2;

            }


            else if(matrix[cell_pos_x][cell_pos_y] == 2 && move_dir > right_cut && move_dir < up_cut && cell_coor[1]-1 <= 0){ //if we encounter another cell on the above  
               matrix[cell_coor[0]][cell_coor[1]] =2;
               matrix[cell_coor[0]][cell_coor[1]-1] =2;

            }

            else if(matrix[cell_pos_x][cell_pos_y] == 2 && move_dir > up_cut && cell_coor[1]+1 <= m){ //if we encounter another cell on the below  
               matrix[cell_coor[0]][cell_coor[1]] =2;
               matrix[cell_coor[0]][cell_coor[1]+1] =2;
            }
            */
            else { //no pillar 
                cell_pos_x = cell_coor[0];
                cell_pos_y = cell_coor[1];
                matrix[cell_pos_x][cell_pos_y] = 2;
            }//end of search and placement of cells
    }//end of for loop 1

    //Print matrix
    for (int k = 0; k < matrix.size(); k++){
        for (int l = 0; l < matrix[k].size(); l++){
            std::cout << matrix[k][l] << " ";
        }
        std::cout << std::endl;
    }


    //plot the board as 2D hist
    TH2I *h1 = new TH2I("h1", "Board", n, 0, n, m, 0, m);
    std::cout << "Size of Matrix[0] is" << matrix[0].size() << std::endl; 
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            h1->SetBinContent(i,j, matrix[i][j]);
        }
    }
    h1->Draw("COLZ");

}//end of main 
