#include "hitOrMiss.h"
#include <iostream>
#include <string>
#include <vector>

#define FIRST_PATTERN_NUMBER 40

using namespace std;
//First Stage Patterns
string firstPatterns[FIRST_PATTERN_NUMBER];



bool hitOrMiss2(unsigned char inputWindow[][3]){
	//Spur
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) &&  ((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if(  ((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	     ((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) &&  ((bool)inputWindow[2][2])    ){
		return true;
	}
	
	//Single 4-connection
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	
	//L Corner
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}

	//Corner Cluster
	if( (bool)inputWindow[0][0]  && (bool)inputWindow[0][1] &&
		(bool)inputWindow[1][0]  && (bool)inputWindow[1][1]    ){	    
		return true;
	}
	if( (bool)inputWindow[1][1]  && (bool)inputWindow[1][2] &&
		(bool)inputWindow[2][1]  && (bool)inputWindow[2][2]    ){	    
		return true;
	}

	//Tee Branch
	if( 							   ((bool)inputWindow[0][1]) 							   &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2])    ){
		return true;
	}
	if( 							   ((bool)inputWindow[0][1]) 							   &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) 							   &&
	    							   ((bool)inputWindow[2][1]) 							      ){
		return true;
	}
	if(  ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    							   ((bool)inputWindow[2][1]) 							      ){
		return true;
	}
	if( 							   ((bool)inputWindow[0][1]) 							   &&
	     							   ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    						 	   ((bool)inputWindow[2][1]) 							      ){
		return true;
	}

	//Vee Branch
	if(  (((bool)inputWindow[2][0]) ||  ((bool)inputWindow[2][1]) ||  ((bool)inputWindow[2][2])) &&	    
	      ((bool)inputWindow[0][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[0][2])   ){	     
		return true;
	}
	if(  (((bool)inputWindow[0][2]) ||  ((bool)inputWindow[1][2]) ||  ((bool)inputWindow[2][2])) &&	    
	      ((bool)inputWindow[0][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[2][0])   ){	     
		return true;
	}
	if(  (((bool)inputWindow[0][0]) ||  ((bool)inputWindow[0][1]) ||  ((bool)inputWindow[0][2])) &&	    
	      ((bool)inputWindow[2][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[2][2])   ){	     
		return true;
	}
	if(  (((bool)inputWindow[0][0]) ||  ((bool)inputWindow[1][0]) ||  ((bool)inputWindow[2][0])) &&	    
	      ((bool)inputWindow[0][2]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[2][2])   ){	     
		return true;
	}
	

	//Diagonal Branch
	if(   							   ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	     ((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) 							      ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) 							   &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	     							  !((bool)inputWindow[2][1]) &&  ((bool)inputWindow[2][2])    ){
		return true;
	}
	if( 							  !((bool)inputWindow[0][1]) &&  ((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) 							      ){
		return true;
	}
	if(  ((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) 							   &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	     							   ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}

	return false;
}


bool hitOrMiss(unsigned char inputWindow[][3]){
	
	fillInfo();	
	for(int p=0; p<FIRST_PATTERN_NUMBER; p++){
		if(compare(inputWindow, firstPatterns[p])){
			return true;
		}
	}
	return false;		
}

bool compare(unsigned char inputWindow[][3], string pattern){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			int patternElement;
			patternElement = (((int) (pattern[i*3+j] - '0'))*255);
			if(inputWindow[i][j] != patternElement){
				return false;
			}
		}
	}
	return true;
}

void fillInfo(){
	
	//TK, 4
	firstPatterns[0] = "010011000";
	firstPatterns[1] = "010110000";
	firstPatterns[2] = "000110010";
	firstPatterns[3] = "000011010";
	//STK, 4
	firstPatterns[4] = "001011001";	
	firstPatterns[5] = "111010000";
	firstPatterns[6] = "100110100";
	firstPatterns[7] = "000010111";	
	//STK, 6
	firstPatterns[8] = "111011000";	
	firstPatterns[9] = "011011001";
	firstPatterns[10] = "111110000";
	firstPatterns[11] = "110110100";
	firstPatterns[12] = "100110110";	
	firstPatterns[13] = "000110111";
	firstPatterns[14] = "000011111";
	firstPatterns[15] = "001011011";
	//STK, 7
	firstPatterns[16] = "111011001";	
	firstPatterns[17] = "111110100";
	firstPatterns[18] = "100110111";
	firstPatterns[19] = "001011111";
	//STK, 8
	firstPatterns[20] = "011011011";	
	firstPatterns[21] = "111111000";
	firstPatterns[22] = "110110110";
	firstPatterns[23] = "000111111";
	//STK, 9
	firstPatterns[24] = "111011011";	
	firstPatterns[25] = "011011111";
	firstPatterns[26] = "111111100";
	firstPatterns[27] = "111111001";
	firstPatterns[28] = "111110110";	
	firstPatterns[29] = "110110111";
	firstPatterns[30] = "100111111";
	firstPatterns[31] = "001111111";
	//STK, 10
	firstPatterns[32] = "111011111";	
	firstPatterns[33] = "111111101";
	firstPatterns[34] = "111110111";
	firstPatterns[35] = "101111111";
	//K,11
	firstPatterns[36] = "111111011";
	firstPatterns[37] = "111111110";
	firstPatterns[38] = "110111111";
	firstPatterns[39] = "011111111";


}


