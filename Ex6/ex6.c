/*
Johnny Li
COP4600
Ex6: Bitwise Manipulation
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
* Inputs are seperate lines.
*/
void main(){
	//Variables
    char cmd;   //command
    uint32_t x; //Hex
    uint32_t m; //Hex
	int n;	//Dec

    while(1){
        //Read command
        scanf(" %c", &cmd);

		//Quit if Q
		if(cmd=='Q'){
			exit(0);
		}

	//Read hex
        scanf("%X", &x);

	//Read hex/dec
        if(cmd=='M'){	//read hex if M
		    scanf("%X", &m);
        }
        else{	//All other cases are dec
            scanf("%d", &n);
        }

		switch(cmd){
			case 'C': 	//Clear bit
				//Get bit position and clear bit
				x &= ~(1 << n);
				//Print
				printf("%x\n",x);
				break;
			case 'M':	//Mask bits
				//AND operation
				x = x&m;
				//Print
				printf("%x\n",x);
				break;
			case 'S':	//Set bit
				//Get bit position and set bit
				x |= 1 << n;
				//Print
				printf("%x\n",x);
				break;
			case 'V':	//Read bit
				//Shift hex to bit position and AND it wo see value
				x = (x >> n)&1;
				//Print
				printf("%x\n",x);
				break;
		}
    }
}
