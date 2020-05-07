#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <unistd.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------
void insertion_sort(vector<int> &v)
{
    for(int i=0; i<v.size()-1; i++)
    {
        int key=v[i+1];
        int j=i;
        while(j>=0 && v[j]>key)
        {
            v[j+1]=v[j--];
        }
        v[j+1]=key;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
int Partition(vector<int> &vec,int start_index,int end_index)
{
    int x=start_index + (rand()%(end_index - start_index +1));
    swap(vec[x],vec[end_index]);
    int pivot=end_index;
    int low=start_index-1;

    for(int i=start_index; i<end_index; i++)
    {
        if(vec[i]<vec[pivot])
        {
            low++;
            swap(vec[low],vec[i]);
        }
    }
    swap(vec[low+1],vec[pivot]);
    return low+1;
}
void QuickSort(vector<int>&vec,int start_index,int end_index)
{
    if(start_index<end_index)
    {
        int partition_index=Partition(vec,start_index,end_index);
        QuickSort(vec,start_index,partition_index-1);
        QuickSort(vec,partition_index+1,end_index);
    }

}
//--------------------------------------------------------------------------------------------------------------------------------------------
void Merge(vector<int>&vec,int start_index,int mid,int end_index)
{
    int n1=mid-start_index+1;
    int n2=end_index-mid;
    vector<int>left;
    vector<int>right;
    for(int i=0; i<n1; i++)
    {
        left.push_back(vec[start_index+i]);
    }
    for(int i=0; i<n2; i++)
    {
        right.push_back(vec[i+1+mid]);
    }
    int i=0,j=0,k=start_index;
    while(i<n1 && j<n2)
    {
        if(left[i]<=right[j])
        {
            vec[k]=left[i];
            i++;
        }
        else
        {
            vec[k]=right[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        vec[k]=left[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        vec[k]=right[j];
        j++;
        k++;
    }

}
void MergeSort(vector<int>&vec,int start_index,int end_index)
{
    if(start_index<end_index)
    {
        int mid=start_index+(end_index-start_index)/2;
        MergeSort(vec,start_index,mid);
        MergeSort(vec,mid+1,end_index);
        Merge(vec,start_index,mid,end_index);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void Heapify(vector<int> &vec,int vec_size,int i)
{
    int max_index=i;
    int ch1=(2*i)+1;
    int ch2=(2*i)+2;

    if(ch1<vec_size && vec[max_index]<vec[ch1])
    {
        max_index=ch1;
    }
    if(ch2<vec_size && vec[max_index]<vec[ch2])
    {
        max_index=ch2;
    }
    if(max_index!=i)
    {
        swap(vec[max_index],vec[i]);
        Heapify(vec,vec_size,max_index);
    }
}
void HeapSort(vector<int> &vec)
{
    int start_index=(vec.size()/2)-1;
    for(int i=start_index; i>=0; i--)
    {
        Heapify(vec,vec.size(),i);
    }
    int z=vec.size();
    for(int i=0; i<vec.size(); i++)
    {
        z--;
        swap(vec[0],vec[z]);
        Heapify(vec,z,0);

    }

}

void fill_vec(vector<int> &v,int n)
{
    for(int i=0;i<n;i++){
        v.push_back(rand()%n);
    }
}



int main()
{
    vector<int> vec1,vec2,tvec1,tvec2;
    ifstream file;
    char filename1[50],filename2[50];
    cout<<"Enter first file name: ";
    cin.getline(filename1,50);
    file.open(filename1);
    if(!file.is_open())
    {
        cout<<"Error occurred while reading file!"<<endl;
        exit(EXIT_FAILURE);
    }
    int num=0;

    while(file.good())
    {
        file>>num;
        vec1.push_back(num);
    }
    cout<<"First file read successfully!"<<endl;
    cout<<"Enter second file name: ";
    cin.getline(filename2,50);
    file.close();
    file.open(filename2);
    if(!file.is_open())
    {
        cout<<"Error occurred while reading file!"<<endl;
        exit(EXIT_FAILURE);
    }
    while(file.good())
    {
        file>>num;
        vec2.push_back(num);
    }
    cout<<"Second file read successfully!"<<endl;
    file.close();

    fill_vec(vec1,10000);
    fill_vec(vec2,10000);
    tvec1=vec1;
    tvec2=vec1;

    int end_index_v1=vec1.size()-1;
    int end_index_v2=vec2.size()-1;



    auto start= high_resolution_clock::now();
    insertion_sort(vec1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();

    cout<<"\nRunning time for O(n^2) is "<<duration<<"ms"<<endl;




    auto start1= high_resolution_clock::now();
    QuickSort(vec1,0,end_index_v1);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1).count();

    cout<<"\nRunning time for O(nlogn) is "<<duration1<<"ms"<<endl;



    auto start2= high_resolution_clock::now();
    HeapSort(tvec2);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2).count();

    cout<<"\nRunning time for O(nlogn) is "<<duration2<<"ms"<<endl;

    if(vec1==vec2)
        cout<<"2 files are identical";
    else
        cout<<"2 files are NOT identical";



    return 0;
}
