#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
void FillArray1(int a[],int n){
	srand(time(NULL));
	for(int i=0;i<n;i++) a[i]=rand()%100+1;
}
void FillArray2(int a[],int n){
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
}
void FillArray3(int a[],int n,int val){
	for(int i=0;i<n;i++) a[i]=val;
}
void FillArray4(int a[],int n,int start,int diff){
	a[0]=start;
	for(int i=1;i<n;i++) a[i]=a[i-1]+diff;
}
void insert(int a[],int *n,int pos,int val){
	if(pos<0||pos>*n) {printf("插入位置无效\n");return;}
	for(int i=*n;i>pos;i--) a[i]=a[i-1];
	a[pos]=val;
	(*n)++;
}
void Delete1(int a[],int *n,int id){
	for(int i=id;i<(*n)-1;i++) a[i]=a[i+1];
	(*n)--;
}
void Delete2(int a[],int *n,int val){
	int temp[*n],count=0;
    for(int i=0;i<*n;i++) if(a[i]!=val) temp[count++]=a[i];
	for(int i=0;i<count;i++) a[i]=temp[i];
	(*n)=count;
}
void DeleteRange(int a[],int *n,int s,int t){
	for(int i=1;i<=t-s+1;i++) for(int j=s;j<*n;j++) a[j]=a[j+1];
	*n=(*n)-(t-s+1);
}
int Search(int a[],int n,int val){
	int i;
	for(i=0;i<n;i++) if(a[i]==val) return i;
	return -1;
}
bool isAsc(int a[],int n){
	for(int i=0;i<n-1;i++) if(a[i]>a[i+1]) return false;
	return true;
}
bool isDesc(int a[],int n){
	for(int i=0;i<n-1;i++) if(a[i]<a[i+1]) return false;
	return true;
}
bool isEqual(int a[],int n){
	for(int i=0;i<n-1;i++) if(a[i]!=a[i+1]) return false;
	return true;
}
int maxIndex(int a[],int n){
	int maxindex=0;
	for(int i=1;i<n;i++) if(a[i]>a[maxindex]) maxindex=i;
	return maxindex;
}
int minIndex(int a[],int n){
	int minindex=0;
	for(int i=1;i<n;i++) if(a[i]<a[minindex]) minindex=i;
	return minindex;
}
float average(int a[],int n){
	float s=0;
	for(int i=0;i<n;i++) s=s+a[i];
	return s/n;
}
void OrderInsert(int a[],int *n,int val){
	int i;
	for(i=(*n)-1;(i>=0)&&(a[i]>val);i--) a[i+1]=a[i];
	a[i+1]=val;
	*n=(*n)+1;
}
void BubbleSort(int a[],int n){
	int i,j;
	for(i=0;i<n-1;i++) for(j=0;j<n-1-i;j++) if(a[j]>a[j+1]){int temp=a[j];a[j]=a[j+1];a[j+1]=temp;}
}
void SelectSort(int a[],int n){
	int i,j,minindex;
	for(i=0;i<n-1;i++){
		minindex=i;
	    for(j=i+1;j<n;j++) if(a[j]<a[minindex]) minindex=j;
	    int temp=a[minindex];a[minindex]=a[i];a[i]=temp;
	}
}
void InsertSort(int a[],int n){
	int i,j,key;
	for(i=1;i<n;i++){
	    key=a[i];
	    j=i-1;
	    while(j>=0&&a[j]>key) {a[j+1]=a[j];j=j-1;}
	    a[j+1]=key;
	}
}
void Reverse(int a[],int n){
	int start=0,end=n-1;
	while(start<end){
		int temp=a[start];a[start]=a[end];a[end]=temp;
	    start++;end--;
	}
}
int BiSearch(int a[],int l,int r,int x){
    if(r>=l){
        int mid=l+(r-l)/2;
        if(a[mid]==x) return mid;
        if(a[mid]>x) return BiSearch(a,l,mid-1,x);
        return BiSearch(a,mid+1,r,x);
    }
    return -1;
}
/*int partition(int a[],int low,int high){
    int pivotkey=a[low],temp;
    while(low<high){
		while(low<high&&a[high]>=pivotkey) high--;
		temp=a[low];a[low]=a[high];a[high]=temp;
		while(low<high&&a[low]<=pivotkey) low++;
		temp=a[low];a[low]=a[high];a[high]=temp;
	}
    return low;
}
void QuickSort(int a[],int low,int high){
    if(low<high){
        int pivotloc=partition(a,low,high);
        QuickSort(a,low,pivotloc-1);
        QuickSort(a,pivotloc+1,high);
    }
}*/int partition(int a[], int low, int high) {
    int pivotkey = a[low];  // 选择第一个元素为基准
    while (low < high) {
        while (low < high && a[high] >= pivotkey) 
            high--;  // 从右向左找到小于pivotkey的元素
        a[low] = a[high];  // 将小的元素移动到左边
        while (low < high && a[low] <= pivotkey) 
            low++;  // 从左向右找到大于pivotkey的元素
        a[high] = a[low];  // 将大的元素移动到右边
    }
    a[low] = pivotkey;  // 最终将pivotkey放到正确位置
    return low;
}

void QuickSort(int a[], int low, int high) {
    if (low < high) {
        int pivotloc = partition(a, low, high);
        QuickSort(a, low, pivotloc - 1);  // 递归左区间
        QuickSort(a, pivotloc + 1, high);  // 递归右区间
    }
}
void merge(int a[],int l,int m,int r){
    int i,j,k,n1=m-l+1,n2=r-m,L[n1],R[n2];
    for(i=0;i<n1;i++) L[i]=a[l+i];
    for(j=0;j<n2;j++) R[j]=a[m+1+j];
    i=0;j=0;k=l;
    while(i<n1&&j<n2){
        if(L[i]<=R[j]) a[k++]=L[i++];
		else a[k++]=R[j++];
    }
    while(i<n1) a[k++]=L[i++];
    while(j<n2) a[k++]=R[j++];
}
void MergeSort(int a[],int l,int r){
    if(l<r){
        int m=l+(r-l)/2;
        MergeSort(a,l,m);
        MergeSort(a,m+1,r);
        merge(a,l,m,r);
    }
}
void  printarr(int *a, int n){
	printf("现数组为：");
	for(int i=0;i<n;i++) printf("%d ",a[i]);
	printf("\n");
}
int main(){
	int s,t,a[100000],n;
	printf("1.随机生成\n2.输入生成\n3.重复生成\n4.等差生成\n");
	printf("请选择生成数组的方式和元素个数：");
	scanf("%d %d",&s,&n);
	switch(s){
		case 1:
			FillArray1(a,n);
			printarr(a,n);
			break;
		case 2:
			FillArray2(a,n);
			printarr(a,n);
			break;
		case 3:
			int val;
			printf("输入元素：");
			scanf("%d",&val);
			FillArray3(a,n,val);
			printarr(a,n);
			break;
		case 4:
			int start,diff;
			printf("输入首项和公差：");
			scanf("%d %d",&start,&diff);
			FillArray4(a,n,start,diff);
			printarr(a,n);
			break;
	}
	printf("0.退出程序\n");
	printf("1.插入数据\n");
	printf("2.删除指定下标的数据\n");
	printf("3.删除指定的所有数据\n");
	printf("4.删除区间\n");
	printf("5.查找数据\n");
	printf("6.判断升序\n");
	printf("7.判断降序\n");
	printf("8.判断恒等\n");
	printf("9.求最大值下标\n");
	printf("10.求最小值下标\n");
	printf("11.求平均值\n");
	printf("12.逆序输出\n");
	printf("以上操作可随时选择\n");
	printf("13.冒泡升序排序\n");
	printf("14.选择升序排序\n");
	printf("15.插入升序排序\n");
	printf("16.快速升序排序\n");
	printf("17.归并升序排序\n");
	printf("以下操作只可在升序排序后才可选择\n");
	printf("18.有序插入数据\n");
	printf("19.二分查找\n");
    while(1){
		printf("请选择要进行的操作：");
		scanf("%d",&t);
		switch (t){
			case 1:
				int pos,val1;
				printf("请输入插入位置和插入数据：");
				scanf("%d %d",&pos,&val1);
				insert(a,&n,pos,val1);
				printarr(a,n);
				break;
			case 2:
				int id;
				printf("请输入要删的下标：");
				scanf("%d",&id);
				Delete1(a,&n,id);
				printarr(a,n);
				break;
			case 3:
				int val2;
				printf("请输入要删的数据：");
				scanf("%d",&val2);
				Delete2(a,&n,val2);
				printarr(a,n);
				break;
			case 4:
				int start,end;
				printf("请输入要删的区间：");
				scanf("%d %d",&start,&end);
				DeleteRange(a,&n,start,end);
				printarr(a,n);
				break;
			case 5:
				int target1;
				printf("请输入查找目标（若目标重复出现则只输出第一个下标）：");
				scanf("%d",&target1);
				if(Search(a,n,target1)!=-1) printf("它的下标为%d\n",Search(a,n,target1));
				if(Search(a,n,target1)==-1) printf("无此数据\n");
				break;
			case 6:
				if(isAsc(a,n)==1) printf("true\n");
				if(isAsc(a,n)==0) printf("false\n");
				break;
			case 7:
				if(isDesc(a,n)==1) printf("true\n");
				if(isDesc(a,n)==0) printf("false\n");
				break;
			case 8:
				if(isEqual(a,n)==1) printf("true\n");
				if(isEqual(a,n)==0) printf("false\n");
				break;
			case 9:
				printf("最大值下标为%d\n",maxIndex(a,n));
				break;
			case 10:
				printf("最小值下标为%d\n",minIndex(a,n));
				break;
			case 11:
				printf("平均值为%f\n",average(a,n));
				break;
			case 12:
				Reverse(a,n);
				printarr(a,n);
				break;
			case 13:
				BubbleSort(a,n);
				printarr(a,n);
				break;
			case 14:
				SelectSort(a,n);
				printarr(a,n);
				break;
			case 15:
				InsertSort(a,n);
				printarr(a,n);
				break;
			case 16:
				QuickSort(a,0,n-1);
				printarr(a,n);
				break;
			case 17:
				MergeSort(a,0,n-1);
				printarr(a,n);
				break;
			case 18:
				int val3;
				printf("请输入插入数据：");
				scanf("%d",&val3);
				OrderInsert(a,&n,val3);
				printarr(a,n);
				break;
			case 19:
				int target2;
				printf("请输入查找目标（若目标重复出现则只输出最“中间”的下标）：");
				scanf("%d",&target2);
				if(BiSearch(a,0,n-1,target2)!=-1) printf("它的下标为%d\n",BiSearch(a,0,n-1,target2));
				if(BiSearch(a,0,n-1,target2)==-1) printf("无此数据\n");
				break;
			case 0:
				return 0;
		}
	}
	return 0;
}
