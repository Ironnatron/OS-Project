#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
 int fd1[2];                                                 //first pipe
 int fd2[2];                                                 //second pipe
 char input_str[100];                                        //input string
 pid_t  p;                                                   //variable for pid

 if(pipe(fd1)==-1)                                    //pipe only takes two values 0(read) and 1(write)
 {                                                    //For first pipe
    fprintf(stderr,"Pipe Failed");
    return 1;
 }
 if(pipe(fd2)==-1)                                    //For second pipe
 {
    fprintf(stderr,"Pipe Failed");
 }
 printf("Enter String:\n");
 scanf("%[^\n]",input_str);                           //taking  input for string form user
 p=fork();                                            //fork() system call called for process
 if(p<0)                                              //if a process is a parent process always returns 1 if no process is created the it return -1
 {
    fprintf(stderr,"Fork Failed");
    return 1;
 }
 else if(p>0)                                         //Since the value returned is 1 which is greater than 0 hence a parent process is created
 {
   char  conver_str[100],
   close(fd1[0]);                                    //reading end of the pipe 1 is closed
   write(fd1[1],input_str,strlen(input_str)+1);     //string taken from the user is  passed at writing end of pipe1
   close(fd1[1]);                                   //writing end of pipe 1 is closed


   wait(NULL);                                       //Wait() system call parent process will wait until child is completely executed

   close(fd2[1]);                                    //writing end of pipe 2 is closed

   read(fd2[0],conver_str,100);                      //reading end of pipe 2 is closed
   printf("Final String:%s\n\n",conver_str);           //Final Uppercased String sent by child process
   close(fd2[0]);                                      //reading end of pipe2 closed
 }
 else                                               //child process created
 {
   int i;
   close(fd1[1]);                                   //writing end of pipe1
   char conver_str[100];
   read(fd1[0],conver_str,100);                      //String sent by parent process is read at reading end of pipe1 by child process

   for(i=0;i<=strlen(conver_str);i++)
   {
     if(conver_str[i]>=97 && conver_str[i]<=122)   //lowercase alphabets have ASCII value between 97 to 122 
     {
        conver_str[i]=conver_str[i]-32;            //when lowercase alphabet is encountered then it is subtracted by 32
     }
   }
   conver_str[i]='\0';
   close(fd1[0]);                                  //reading end of pipe1 closed
   close(fd2[0]);                                  //reading end of pipe2 closed
   write(fd2[1],conver_str,strlen(conver_str)+1);   //Writing uppercased string at writing end of pipe2 back to parent process
   close(fd2[1]);                                  //writing end of pipe 2 is closed
   exit(0);
 }
}
