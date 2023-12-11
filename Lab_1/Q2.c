#include <stdio.h>

int main () {
    int decimalNum, binary[32], firstOne = 0;
    printf("Enter number: ");
    scanf("%d", &decimalNum);
    //Decimal to binary
    int quotient = decimalNum;
    if(decimalNum<0)
        quotient = decimalNum*-1;
    for(int i=31;i>=0;i--) {
        binary[i] = quotient%2;
        if(decimalNum<0) {
            if(binary[i]==0) {
                if(firstOne==1)
                    binary[i]=1;
            } else {
                if(firstOne==1)
                    binary[i]=0;
                else
                    firstOne=1;
            }
        }
        quotient /= 2;
    }
    printf("2's complement representation of %d is:  ", decimalNum);
    for(int i=0;i<8;i++) {
        for(int j=0;j<4;j++) {
            printf("%d", binary[4*i+j]);
        }
        printf(" ");
    }
    return 0;
}