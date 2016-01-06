#include "hitOrMiss.h"
#include <iostream>
#include <string>
#include <vector>

#define FIRST_PATTERN_NUMBER 58

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
	
	//L Cluster
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) &&  ((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) &&  ((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if(  ((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if(  ((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	//
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	     ((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	     ((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) &&  ((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) &&  ((bool)inputWindow[2][2])    ){
		return true;
	}

	//4-Connected Offset
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) &&  ((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if(  ((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) &&  ((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) &&  ((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}

	//Spur Corner Cluster
	if( (((bool)inputWindow[0][1]) || ((bool)inputWindow[1][2])) &&
		!((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && 
	     ((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}

	if( (((bool)inputWindow[0][1]) || ((bool)inputWindow[1][0])) &&
		 ((bool)inputWindow[0][0]) && ((bool)inputWindow[1][1]) && ((bool)inputWindow[2][2]) &&
	    !((bool)inputWindow[0][2]) && !((bool)inputWindow[1][2]) && !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) ){
		return true;
	}

	if( (((bool)inputWindow[1][0]) || ((bool)inputWindow[2][1])) &&
		 ((bool)inputWindow[0][2]) && ((bool)inputWindow[1][1]) && ((bool)inputWindow[2][0]) &&
	    !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1]) && !((bool)inputWindow[1][2]) && !((bool)inputWindow[2][2]) ){
		return true;
	}

	if( (((bool)inputWindow[1][2]) || ((bool)inputWindow[2][1])) &&
		 ((bool)inputWindow[0][0]) && ((bool)inputWindow[1][1]) && ((bool)inputWindow[2][2]) &&
	    !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) && !((bool)inputWindow[1][0]) && !((bool)inputWindow[2][0]) ){
		return true;
	}

	//Corner Cluster
	if( (bool)inputWindow[0][0]  && (bool)inputWindow[0][1] &&
		(bool)inputWindow[1][0]  && (bool)inputWindow[1][1]    ){	    
		return true;
	}

	//Tee Branch
	if( 							   ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    							  !((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) 							   &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) && !((bool)inputWindow[2][1]) 							      ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) && !((bool)inputWindow[0][1])							   &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) 							      ){
		return true;
	}
	if( 							  !((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    						 	   ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	//.
	if( 							   ((bool)inputWindow[0][1]) 							   &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	     ((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) && !((bool)inputWindow[1][2]) &&
	    						       ((bool)inputWindow[2][1])    						      ){
		return true;
	}
	if( !((bool)inputWindow[0][0]) &&  ((bool)inputWindow[0][1]) && !((bool)inputWindow[0][2]) &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    							   ((bool)inputWindow[2][1]) 							      ){
		return true;
	}
	if(								   ((bool)inputWindow[0][1]) 							   &&
	    !((bool)inputWindow[1][0]) &&  ((bool)inputWindow[1][1]) &&  ((bool)inputWindow[1][2]) &&
	    !((bool)inputWindow[2][0]) &&  ((bool)inputWindow[2][1]) && !((bool)inputWindow[2][2])    ){
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
	//S, 1
	firstPatterns[0] = "001010000";	
	firstPatterns[1] = "100010000";
	firstPatterns[2] = "000010100";
	firstPatterns[3] = "000010001";
	//S, 2
	firstPatterns[4] = "000011000";
	firstPatterns[5] = "010010000";
	firstPatterns[6] = "000110000";
	firstPatterns[7] = "000010010";
	//S, 3
	firstPatterns[8] = "001011000";
	firstPatterns[9] = "011010000";
	firstPatterns[10] = "110010000";
	firstPatterns[11] = "100110000";
	firstPatterns[12] = "000110100";
	firstPatterns[13] = "000010110";
	firstPatterns[14] = "000010011";
	firstPatterns[15] = "000011001";
	//STK, 4
	firstPatterns[16] = "001011001";	
	firstPatterns[17] = "111010000";
	firstPatterns[18] = "100110100";
	firstPatterns[19] = "000010111";
	//ST, 5
	firstPatterns[20] = "110011000";	
	firstPatterns[21] = "010011001";
	firstPatterns[22] = "011110000";
	firstPatterns[23] = "001011010";
	//ST, 5_2
	firstPatterns[24] = "011011000";	
	firstPatterns[25] = "110110000";
	firstPatterns[26] = "000110110";
	firstPatterns[27] = "000011011";
	//ST, 6
	firstPatterns[28] = "110011001";	
	firstPatterns[29] = "011110100";
	//STK, 6
	firstPatterns[30] = "111011000";	
	firstPatterns[31] = "011011001";
	firstPatterns[32] = "111110000";
	firstPatterns[33] = "110110100";
	firstPatterns[34] = "100110110";	
	firstPatterns[35] = "000110111";
	firstPatterns[36] = "000011111";
	firstPatterns[37] = "001011011";
	//STK, 7
	firstPatterns[38] = "111011001";	
	firstPatterns[39] = "111110100";
	firstPatterns[40] = "100110111";
	firstPatterns[41] = "001011111";
	//STK, 8
	firstPatterns[42] = "011011011";	
	firstPatterns[43] = "111111000";
	firstPatterns[44] = "110110110";
	firstPatterns[45] = "000111111";
	//STK, 9
	firstPatterns[46] = "111011011";	
	firstPatterns[47] = "011011111";
	firstPatterns[48] = "111111100";
	firstPatterns[49] = "111111001";
	firstPatterns[50] = "111110110";	
	firstPatterns[51] = "110110111";
	firstPatterns[52] = "100111111";
	firstPatterns[53] = "001111111";
	//STK, 10
	firstPatterns[54] = "111011111";	
	firstPatterns[55] = "111111101";
	firstPatterns[56] = "111110111";
	firstPatterns[57] = "101111111";


}


