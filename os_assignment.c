#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
 int fd1[2];
 int fd2[2];
 char input_str[100];
 pid_t  p;

 if(pipe(fd1)==-1)
 {
    fprintf(stderr,"Pipe Failed");
    return 1;
 }
 if(pipe(fd2)==-1)
 {
    fprintf(stderr,"Pipe Failed");
 }
 printf("Enter String:\n");
 scanf("%[^\n]",input_str);
 p=fork();
 if(p<0)
 {
    fprintf(stderr,"Fork Failed");
    return 1;
 }
 else if(p>0)
 {
   char  conver_str[100];
   close(fd1[0]);
   write(fd1[1],input_str,strlen(input_str)+1);
   close(fd1[1]);


   wait(NULL);

   close(fd2[1]);

   read(fd2[0],conver_str,100);
   printf("Final String:%s\n\n",conver_str);
   close(fd2[0]);
 }
 else
 {
   int i;
   close(fd1[1]);
   char conver_str[100];
   read(fd1[0],conver_str,100);
   for(i=0;i<=strlen(conver_str);i++)
   {
     if(conver_str[i]>=97 && conver_str[i]<=122)
     {
        conver_str[i]=conver_str[i]-32;
     }
   }
   conver_str[i]='\0';
   close(fd1[0]);
   close(fd2[0]);
   write(fd2[1],conver_str,strlen(conver_str)+1);
   close(fd2[1]);
   exit(0);
 }
}
