#include <cstdio>
#include <cstdlib>
#include<malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
using namespace std;
void mergeInPlace(int *a, int lo, int m, int hi) {
	int lo2 = m ;
	if (a[lo2] <= a[m-1])
		return;
	while ((lo < m) && (lo2 < hi)) {
		if (a[lo] > a[lo2]) {
			int tmp = a[lo2];
			int index = lo2;
			while (lo < index) {
				a[index] = a[index - 1];
				index--;

			}
			a[lo] = tmp;
			lo++;
			m++;
			lo2++;
		}
		else
			lo++;
	}
}
long *merge(long left[],long len_left, long right[],long len_right) {
	long *result = (long *)malloc(sizeof(long) *(len_left+len_right));
	long i = 0;
	long index_l = 0, index_r = 0;
	while ((i<len_left+len_right)&&(index_l<len_left)) {
		if ((left[index_l] <= right[index_r])||(index_r>=len_right)) {
			result[i] = left[index_l];
			i++;
			index_l++;
		}
		else {
			result[i] = right[index_r];
			i++;
			index_r++;
		}
	}
	while ((i<len_left+len_right)&&(index_r<len_right)) {
		result[i] = right[index_r];
		i++;
		index_r++;
	}
	return result;

}
long *mergeSort(long a[], long lo, long hi) {
	long *left;
	long *right;
	if (lo >= hi-1) {
		return &(a[lo]);
	}
	else{
		long m = (lo + hi) >> 1;
		left = mergeSort(a, lo, m);
		right = mergeSort(a, m, hi);
		return merge(left,(m-lo), right,(hi-m));
	}
	
}


void mergeSortInPlace(int *a, int lo, int hi) {
	if (lo < hi-1) {
		int m = (lo + hi) >> 1;
		mergeSortInPlace(a, lo, m);
		mergeSortInPlace(a, m , hi);
		mergeInPlace(a, lo, m, hi);
		
	}
}


long binSearch(long a[], long key, long lo, long hi) {
	while (lo < hi) {
		int m = (lo + hi) >> 1;
		if (key < a[m])
			hi = m;
		else
			lo = m + 1;
	}
	return --lo;

}

long rangeSearch(long *a,long upper,long down, long lo, long hi) {
	long down_rank=-1, upper_rank=-1;
	long num;
	down_rank=binSearch(a, down, lo, hi);
	upper_rank=binSearch(a, upper, down_rank, hi);
	if ((num = upper_rank - down_rank) < 0)
		num = 0;
	if (down == a[down_rank])
		num++;

	return num;
		
}
int main() {
	long range, num;
	scanf("%ld%ld\n",&range,&num);
	//int a[100] = {0};
	long *a = (long *)malloc(range * sizeof(long));
	for (long i = 0; i < range; i++) {
		scanf("%ld", &a[i]);
	}
	long lo = 0, hi = range;
	//mergeSortInPlace(a, lo, hi);
	long *sorted;
	sorted = mergeSort(a, lo, hi);
	long upper, down;
	//for (int i = 0; i < range; i++) {
		//printf("%d ", a[i]);
		//printf("%d ", sorted[i]);
	//}
	for (long i = 0; i < num; i++) {
		scanf("\n%ld%ld", &down, &upper);
		//printf("%d\n", rangeSearch(a, upper, down, lo, hi));
		printf("%ld\n", rangeSearch(sorted, upper, down, lo, hi));
		
	}
	free(a);
	free(sorted);
	return 0;
}

