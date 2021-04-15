/* client.c */

#include "head.h"
#include <netdb.h>
#include <errno.h>
#include <crypt.h>

char yastik[500],aim[14],salt[3];
int sock;
int i=0,j=0,k=0;
int limit,bulundu;

void* search(void *t)
{
	FILE * pFile , * p;
  	pFile = fopen ("myfile.txt","w");
  	p = fopen ("ara.txt","w");
	int size=strlen(yastik);
	char buldu[7]="";
	
	for(k=0;k<limit;k++){
		for(j=0;j<94;j++){
			for(i=0;i<94;i++)
			{	
				if(yastik[size-1]==126){
					yastik[size-1]=33; break;}		
				yastik[size-1]=yastik[size-1]+1;
				char * ptr=(char*)crypt(yastik,salt);
								
				if(strcmp(ptr,aim)==0){
					write(sock,yastik,strlen(yastik)); bulundu=1;  close(sock);return;}	
			
			}
			if(yastik[size-2]==126){
					yastik[size-2]=33; break;}	
			yastik[size-2]=yastik[size-2]+1;				

	       }
		if(yastik[size-3]==126){
					printf("sonzusda\n");yastik[size-3]=33; break;}	
		yastik[size-3]=yastik[size-3]+1;
		fprintf(pFile,"burda...\n");
		fprintf (p, "%s\n",yastik);
	}
}

char* take_encrypt(char encrypt[])
{
	read(sock,encrypt,13);
	encrypt[13]='\0';
	return encrypt;
}
char *take_salt(char encrypt[],char salt[])
{	
	salt[2]='\0';
	salt[0]=encrypt[0];
	salt[1]=encrypt[1];
	return salt;
}

int main(int argc,char ** argv)
{
	char encrypt[14];
      	int t=0;   
	pthread_t thr;
        struct sockaddr_in sunucu;
	struct hostent *s_bilgi;

	
	while(1){

		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		    perror("Socket");
		    exit(1);
		}
		s_bilgi = gethostbyname(argv[1]);
		sunucu.sin_family = s_bilgi->h_addrtype;
		memcpy(&sunucu.sin_addr, s_bilgi->h_addr, s_bilgi->h_length);
		sunucu.sin_port = htons(atoi(argv[2]));


		if((connect(sock,(struct sockaddr *)&sunucu, sizeof sunucu))< 0){
  			printf("Connect\n");
  			exit(1);
  		}

		
		take_encrypt(encrypt);
		take_salt(encrypt,salt);
		strcpy(aim,encrypt);
		read(sock,yastik,100);
		int s=strlen(yastik);	
		yastik[s]='\0';	
		int thread_number=atoi(argv[3]);
		limit=(95/thread_number)+1;
		int h;
		for(h=0;h<thread_number;h++)
		{
			pthread_create(&thr, NULL, search, (void*)t);
			if(bulundu==1)
				break;
			pthread_join(thr,NULL);	
		}
		
	}
	close(sock);
	return 0;
}

