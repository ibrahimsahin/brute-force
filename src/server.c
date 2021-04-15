/* server.c */

#include "head.h"
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
int  bytes_recieved,baglan,sock,result=0;
char yastik[20];
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
char psw[7]="!!!!";


char* string_change(char str[])
{	
	int i,changed=0;
	if(strlen(str)==4)
	{
		str[0]=str[0]+1;
		return str;
	}
	if(strlen(str)==5)
	{
		if(str[1]==126){
			for(i=1;i<5;i++)
			{
				str[i]=33;
			}
			str[0]=str[0]+1;
			return str;
		}
		str[1]=str[1]+1;
		return str;	
	}
	if(strlen(str)==6)
	{
		
		if(str[1]==126){
			for(i=1;i<6;i++)
			{
				str[i]=33;
			}
			str[0]=str[0]+1;		
			return str;		
		}		
		if(str[2]==126){
			for(i=2;i<6;i++)
			{
				str[i]=33;
			}
			str[1]=str[1]+1;
			return str;		
		}
		str[2]=str[2]+1;
		return str;	
	}
}

void *program(void * t)
{
	int i;
	char find[500];
        if(result==0){
		printf("\n SEND : ");
		write(baglan,psw,strlen(psw));
		pthread_mutex_lock(&mutex1);		
		string_change(psw);	
		if(psw[0]==126){
			if(strlen(psw)==6){
				printf("sonuc bulunamadı...");
				result=1;			
			}						
			if(strlen(psw)==5){
				for(i=0;i<6;i++)
				{
					psw[i]=33;
				}			
			}
			if(strlen(psw)==4){
				for(i=0;i<5;i++)
				{
					psw[i]=33;
				}		 			
			}
			
		}
		printf("%s\n",psw);
		pthread_mutex_unlock(&mutex1);
		read(baglan,find,500);
		if(strlen(find)==4||strlen(find)==5||strlen(find)==6){
			find[strlen(find)]='\0';
			printf("password=%s",find);
			result=1;
		 }
		close(baglan);
	}
}
int main(int argc,char ** argv)
{

	int t=0;   
	pthread_t thr;
	int true = 1;  
     	int connected;
	char sifre[14];
	strcpy(sifre,argv[1]);
	sifre[13]='\0';
	printf("sifre=%s\n",sifre);        
	struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(atoi(argv[2]));     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 5) == -1) {
            perror("Listen");
            exit(1);
        }
		
	printf("\nTCPServer Waiting for client on port 5000");
        fflush(stdout);
	
        while(1)
        {
		sin_size = sizeof(struct sockaddr_in);
                connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
	        baglan=connected;            
	        printf("\n I got a connection from (%s , %d)",
                inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	    	printf("result:%d\n",result);
		write(baglan,sifre,strlen(sifre));
		if(result==1){
			break;		
		}		 
	    	pthread_create(&thr, NULL, program , (void*)t);
	}
 	close(sock);
      	return 0;
} 

