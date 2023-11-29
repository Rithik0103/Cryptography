#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
	char pt[100], ct[100];
int key,i,length;
printf("Enter the plain text:");
scanf("%s", pt);
printf("\nEnter the key value:");
scanf("%d", &key);
printf("\nPLAIN TEXT: %s",pt);
printf("\nENCRYPTED TEXT: ");
for(i = 0, length = strlen(pt); i < length; i++)
{
ct[i]=pt[i] + key;
if (isupper(pt[i]) && (ct[i] > 'Z'))
ct[i] = ct[i] - 26;
if (islower(pt[i]) && (ct[i] > 'z'))
ct[i] = ct[i] - 26;
printf("%c", ct[i]);
}
printf("\nAFTER DECRYPTION : ");
for(i=0;i<length;i++)
{
pt[i]=ct[i]-key;
if(isupper(ct[i])&&(pt[i]<'A'))
pt[i]=pt[i]+26;
if(islower(ct[i])&&(pt[i]<'a'))
pt[i]=pt[i]+26;
printf("%c",pt[i]);
	}
	
}

