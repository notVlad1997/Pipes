#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>

int low;
int high;
int i;
int sentValue = -1;
char* filename[] = { "1001to100000.txt","100001to200000.txt","200001to300000.txt","300001to400000.txt","400001to500000.txt","500001to600000.txt","600001to700000.txt","700001to800000.txt","800001to900000.txt","900001to1000000.txt" };
int mypipe[10][2];
//prime number function 
int primeNum(int low, int high, int* fd) {
	int i;
	int flag;
	char buffer[20];

	while (low < high)
	{
		flag = 0;

		for (i = 2; i <= low/2; ++i)
		{
			if (low % i == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{

			write(fd[1], &low, sizeof(low)); //write to the pipe

		}
		++low;




	}
	write(fd[1], &sentValue, sizeof(sentValue)); //write the sentinel value to the pipe
}


//calculate to 2 to 1000 
int firstprime(int low, int high) {
	int i;
	int flag;
	char buffer[20];

	while (low < high)
	{
		flag = 0;

		for (i = 2; i <= low/2; ++i)
		{
			if (low % i == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{

			printf("%d\n", low);

		}
		++low;




	}

}



//global variables


int main() {


	pid_t pid;
	FILE* fd;
	int name;

	firstprime(2, 1000);
	fflush(stdout); //makes sure it does not write the numbers 10 times to buffer
	//create the pipe
	for (i = 0; i < 10; i++) {
		if (pipe(mypipe[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}


	for (i = 0; i < 10; i++)
	{
		//create child process
		pid = fork();
		if (pid == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{

			close(mypipe[i][0]); //closes the input end of the pipe	


			if (i == 0)
			{

				primeNum(1001, 100000, mypipe[i]);

				close(mypipe[i][1]); //once done closes output end of pipe 
				//printf("exit child\n");
				exit(EXIT_SUCCESS);

			}
			else
			{

				primeNum(i * 100000 + 1, (i + 1) * 100000, mypipe[i]); //calculate the rest of the intervals	

				close(mypipe[i][1]);
				//printf("exit child\n");
				exit(EXIT_SUCCESS);
			}
		}


	}
	//parent process		 
	for (i = 0; i < 10; i++) {
		int buffer;
		name = open(filename[i], O_RDWR | O_CREAT, S_IRWXU); //creates txt files to output prime numbers

		char output[20];
		while (1) {
			read(mypipe[i][0], &buffer, sizeof(buffer)); //Reads through the prime numbers from the pipe

			if (buffer == sentValue) {  //break out of the loop if buffer is -1
				break;
			}
			sprintf(output, "%d\n\0", buffer); //convert characters to strings  
			write(name, output, strlen(output)); //write the output to files
			printf("%d\n\0", buffer);


		}
		close(name);
		close(mypipe[i][0]);
		//exit(EXIT_SUCCESS);
	}


}


