#include <omp.h>
#include <iostream>
using namespace std;
void Test()  {
#pragma omp critical
{ 
cout <<"Hello from thread " << omp_get_thread_num() << ". \n";
cout <<"This is Jon Feige's first parallel program\n";
cout <<"There are currently "<<omp_get_num_threads() <<" threads running\n\n";
}
}
int main() {
#pragma omp parallel num_threads(12)
Test();
}