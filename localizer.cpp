#include "localizer.h"
#include "helpers.cpp"
#include <stdlib.h>
#include "debugging_helpers.cpp"
#include <numeric>

using namespace std;

vector< vector <float> > initialize_beliefs(vector< vector <char> > grid) {
  
  	int rows = grid.size();
  	int cols = grid[0].size();
   	float area = rows * cols;
  	float bpc = 1.0 / area;
  
vector< vector <float> > newGrid( rows, vector <float> (cols, bpc));
  
    vector <float> ro;
    for (int i = 0; i < rows; i++ ) {
        ro.clear();
    	for ( int j = 0; j < cols; j++ ) {
        	ro.push_back(bpc);        
        }
       newGrid.push_back(ro);
    }                                     
	return newGrid;
}

vector< vector <float> > move(int dy, 
                              int dx, 
  			      vector < vector <float> > beliefs,
  			      float blurring) 
{
      	int rows = beliefs.size();
  	int cols = beliefs[0].size();
    
vector < vector <float> > newGrid( rows, (vector <float> (cols, 0.0)));
    
    int newi;
    int newj;
    
//     newGrid = (rows, (vector <float> (cols, 0.0))); // this grid is initialized using line 112
    for (int i = 0; i < rows; i++ ) {
    	for (int j = 0; j < cols; j++ ) {
        	newi = (i + dy) % rows;
            newj = (j + dx) % cols;
           	newGrid[newi][newj] = beliefs[i][j];
        }
    }

  return blur(newGrid, blurring);
}

vector< vector <float> > sense(char color, 
	vector< vector <char> > grid, 
	vector< vector <float> > beliefs, 
	float p_hit,
	float p_miss) 
{

	
vector< vector <float> > newGrid;

    int rows = grid.size();
  	int cols = grid[0].size();
  
    float miss;
  	float hit;
  	vector< vector <float> > preGrid;
  	vector <float> ro;
      for (int i = 0; i < rows; i++ ) {
        ro.clear();
    	for (int j = 0; j < cols; j++ ) {
          	miss = beliefs[i][j] * p_miss;
            hit = beliefs[i][j] * p_hit;
			if (color == grid[i][j]) {
            	ro.push_back(hit); 
              }
            else {
            	ro.push_back(miss); 
             }
          }
         preGrid.push_back(ro);
        }
       
//     vector <float> sum;
//     float a;
//     for ( int i = 0; i < preGrid.size(); i++ ) {
//     	a = accumulate(preGrid[i].begin(), preGrid[i].end(), 0);
//         sum.push_back(a);
//     }
  
//   	float sumofsum = accumulate(sum.begin(), sum.end(), 0);
//   	vector <float> nrow;
//     for ( int i = 0; i < preGrid.size(); i++ ) {
//     	nrow.clear();
//       	for (int j = 0; j < cols; j++ ) {
//         	nrow.push_back(preGrid[i][j] / sumofsum) ;            
//         }
//       	newGrid.push_back(nrow);
//     }


	return normalize(newGrid);
}
                      
     
                      
                 
