#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
double mean,median,sd;
int *num,count;
void *calc_mean(void *param){
    double sum=0;
    for(int i=0;i<count;i++) sum+=num[i];
    mean=sum/count;
    pthread_exit(0);
}
int compare(const void *a,const void *b){
    return (*(int*)a-*(int*)b);
}
void *calc_median(void *param){
    int *local_num=(int*)malloc(sizeof(int)*count);
    for(int i=0;i<count;i++) local_num[i]=num[i];
    qsort(local_num,count,sizeof(int),compare);
    if(count%2==0){
        median=(local_num[count/2-1]+local_num[count/2])/2.0;
    }else{
        median=local_num[count/2];
    }
    free(local_num);
    pthread_exit(0);
}
void *calc_sd(void *param){
    double sum=0;
    for(int i=0;i<count;i++) sum+=num[i];
    double local_mean=sum/count;
    double sum_sqdiff=0;
    for(int i=0;i<count;i++) sum_sqdiff+=pow((num[i]-local_mean),2);
    sd=sqrt(sum_sqdiff/count);
    pthread_exit(0);
}
int main(int argc,char* argv[]){
    if(argc<2){
        printf("The usage is ./threads numbers...\n");
        return 1;
    }
    count=argc-1;
    num=malloc(sizeof(int)*count);
    for(int i=1;i<=count;i++) num[i-1]=atoi(argv[i]);
    pthread_t tid_mean,tid_median,tid_sd;
    pthread_create(&tid_mean,NULL,calc_mean,NULL);
    pthread_create(&tid_median,NULL,calc_median,NULL);
    pthread_create(&tid_sd,NULL,calc_sd,NULL);
    pthread_join(tid_mean,NULL);
    pthread_join(tid_median,NULL);
    pthread_join(tid_sd,NULL);
    printf("The average value is %.2f\n", mean);
    printf("The median value is %.2f\n", median);
    printf("The standard deviation is %.2f\n", sd);
    free(num);
    return 0;
}
