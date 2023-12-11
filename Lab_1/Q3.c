#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    char binaryInput[32];
    printf("Enter sequence of binary strings: ");
    scanf("%s", binaryInput);
    int len = strlen(binaryInput);
    int binary2s[32], PosorNeg = 0;
    //negative if first digit is 1
    if(binaryInput[0]=='1')
        PosorNeg = 1;
    for(int i=31;i>=0;i--) {
        if(31-i<len) {
            binary2s[i] = (int)(binaryInput[i-(31-len)-1]-48);
        } else {
            binary2s[i] = PosorNeg;
        }
    }
    for(int i=0;i<8;i++) {
        for(int j=0;j<4;j++) {
            printf("%d", binary2s[4*i+j]);
        }
        printf(" ");
    }
    //Convert to decimal
    int decimal = 0;
    if(PosorNeg==0) {
        for(int i=0;i<len;i++) {
            decimal += pow(2, i)*((int)(binaryInput[len-i-1])-48);
        }
        printf("\nEquivalent decimal number: %d", decimal);
    }
    else {
        int firstOne = 0;
        for(int i=len-1;i>=0;i--) {
            if(binaryInput[i]=='0') {
                if(firstOne==1)
                    binaryInput[i]='1';
            } else {
                if(firstOne==1)
                    binaryInput[i]='0';
                else
                    firstOne=1;
            }            
        }
        for(int i=0;i<len;i++) {
            decimal += pow(2, i)*((int)(binaryInput[len-i-1])-48);
        }
        printf("\nEquivalent decimal number: -%d", decimal);
    }    
}