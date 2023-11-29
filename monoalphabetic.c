#include<stdio.h>
#include<string.h>
int main(){
	char al[]="abcdefghijklmnopqrstuvwxyz",key[]="zyxwvutsrqponmlkjihgfedcba",pt[100],ct[100];
	int m=0,in[100],i,j;
	printf("Enter plain text :");
	scanf("%s",&pt);
	for(i=0;i<strlen(pt);i++)
	{
		pt[i]=tolower(pt[i]);
	}
	for(i=0;i<strlen(pt);i++){
		for(j=0;j<strlen(al);j++){
			if(pt[i]==al[j]){
				in[m]=j;
				m++;
			}
		}
	}
	printf("\ncipher text: ");
	for(i=0;i<strlen(pt);i++){
		ct[i]=key[in[i]];
		printf("%c",ct[i]);
	}
	printf("\nplain text : ");
	for(i=0;i<strlen(pt);i++){
		pt[i]=al[in[i]];
		printf("%c",pt[i]);
	}	
		
}

