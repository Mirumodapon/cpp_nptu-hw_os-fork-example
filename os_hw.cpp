#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif

bool isPrime(unsigned long long n) {
	for (int i=2;i<n;++i) {
		if (n%i == 0) return false;
	}
	return true;
}

void prime(unsigned long long start, unsigned long long end) {
	for (int i=start;i<=end;i++) {
		if (isPrime(i)) cout<<i<<endl;
	}
}
int main() {
	pid_t pid_1, pid_2, pid_3;
	int status;
	unsigned long long number;
	cin>> number;

	pid_1 = fork();
	pid_2 = fork();
	pid_3 = fork();

	if (pid_1 == 0) {
		if (pid_2 == 0) {
			if (pid_3 == 0) {
				// children 7
				prime(((unsigned long long)number/7)+5,number);
			} else {
				// children 2
				prime(((unsigned long long)number/7),((unsigned long long)number/7)+1);
			}
		} else {
			if (pid_3 == 0) {
				// children 6
				prime(((unsigned long long)number/7)+4,((unsigned long long)number/7)+5);
			} else {
				// children 1
				prime(2,((unsigned long long)number/7));
			}
		}
	} else {
		if (pid_2 == 0) {
			if (pid_3 ==0) {
				// children 5
				prime(((unsigned long long)number/7)+3,((unsigned long long)number/7)+4);
			} else {
				// children 3
				prime(((unsigned long long)number/7)+1,((unsigned long long)number/7)+2);
			}
		} else {
			if (pid_3 == 0) {
				// children 4
				prime(((unsigned long long)number/7)+3,((unsigned long long)number/7)+3);
			} else {
				wait(NULL);
			}
		}
	}
	if (pid_1 != 0) wait(NULL);
	if (pid_2 != 0) wait(NULL);
	if (pid_3 != 0) wait(NULL);
	return EXIT_SUCCESS;
}
