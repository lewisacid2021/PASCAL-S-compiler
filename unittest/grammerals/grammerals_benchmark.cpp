#include<benchmark/benchmark.h>
#include<bits/stdc++.h>

#define n 20000
using namespace std;
void merge(int arr[],int start,int mid,int end)
{
    int * tmp=new int[end-start+1];
    int k=0; 
    int i=start;
    int j=mid+1;

    while(i<=mid&&j<=end)
    {
        if(arr[i]<=arr[j])
        {
            tmp[k]=arr[i];
            i++;k++;
        }
        else {
            tmp[k]=arr[j];
            j++;k++;
        }
    }

    while(i<=mid)
    {
        tmp[k]=arr[i];
        i++;k++;
    }

    while(j<=end)
    {
        tmp[k]=arr[j];
        j++;k++;
    }
    
    memcpy(arr+start,tmp,(end-start+1)*sizeof(int));
    delete []tmp;
}

void merge_sort(int arr[],int len)
{
    int seg,start,mid,end;

    for(seg=1; seg<len; seg*=2)
    {
        for(start=0; start<len-1;start+=2*seg)
        {
            mid=min(start+seg-1,len-1);
            end=min(start+2*seg-1,len-1);
            merge(arr,start,mid,end);
        }
    }
}

void quick_sort(int arr[], int begin, int end)
{
    if (end-begin>1)
    {
        int tmp = arr[begin];
        int i = begin+1, j = end-1;

        while (i<j)
        {
            if (arr[i] < tmp)  ++i;
            else if (arr[j] > tmp) --j;
            else
            {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }

        if (tmp > arr[j])
        {
            arr[begin] = arr[j];
            arr[j] = tmp;
        }

        quick_sort(arr, begin, j);
        quick_sort(arr, j, end);
    }
}

mt19937 rng{random_device{}()};

int * generateArray()
{
    int *tmp=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) tmp[i]=rng();
    return tmp;
}

static void test1_benchmark(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    int * arr=generateArray();
    merge_sort(arr,n);
    free(arr);
  }
}
// Register the function as a benchmark
BENCHMARK(test1_benchmark);

static void test2_benchmark(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    int * arr=generateArray();
    quick_sort(arr,0,n-1);
    free(arr);
  }
}
// Register the function as a benchmark
BENCHMARK(test2_benchmark);

BENCHMARK_MAIN();