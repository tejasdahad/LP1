#include<iostream>
#include<omp.h>
#include<time.h>
using namespace std;
int c1[3];
int binary_search(int a[],int low,int high,int key){
	int loc = -1;
	int mid;
	while(low<=high){
		mid = (high + low )/2;
		if (a[mid] == key) {
			loc = mid;
			break;
		}
		else {
			#pragma omp parallel sections
			{
				cout<<"Thread num:"<<omp_get_thread_num()<<endl;
				#pragma omp section
				{
					if(a[mid]<key){
						low = mid+1;
					}
				}
				#pragma omp section
				{
					cout<<"Thread num:"<<omp_get_thread_num()<<endl;
					if(a[mid]>key){
						high = mid-1;
					}
				}
			}
		}
	}
	return loc;
}
int main(){
	int th = omp_get_max_threads();
	cout<<"Max Threads : "<<th<<endl;
	omp_set_num_threads(2);
	c1[1]=0;
	c1[2]=0;
	int a[100000];
	
	clock_t t1,t2;
	int key = 0;
	int loc,i;
	for (int i = 0; i < 100000; i++) {
		a[i] = i;
	}
	key = 10001;
	t1 = clock();
	double start = omp_get_wtime();
	loc = binary_search(a,0,100000,key);
	t2 = clock();
	double end = omp_get_wtime();
	if (loc == -1) {
		cout<<"Not Found"<<endl;
	} else {
		cout<<"Found at "<<loc<<endl;
		//cout<<"By Thread "<<omp_get_thread_num()<<endl;
	}
	 double cpu_time_used = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	 cout<<end-start<<endl;
	return 0 ;
}
