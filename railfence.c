#include<stdio.h>
#include<string.h>
int main(){
	int i,j=0;
	int count=0,len=0,rail=0;
	char str[100],code[100][100];
	printf("Enetr Depth : ");
	scanf("%d",&rail);
	printf("Enter string : ");
	scanf("%s",&str);
	len=strlen(str);
	while(j<len){
		if(count%2==0){
			for(i=0;i<rail;i++){
				code[i][j]=str[j];
				j++;
			}
		}
		else{
			for(i=rail-2;i>0;i--){
				code[i][j]=str[j];
				j++;
			}
		}
		count++;
	}
	for(i=0;i<rail;i++){
		for(j=0;j<len;j++){
			printf("%c ",code[i][j]);
		}
	}
}

