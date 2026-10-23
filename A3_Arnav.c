#include <stdio.h>

struct student{
    int marks;
    int rollnumber;
};

void display(struct student a[10]){
        printf("Array after sort:\n");

    for(int i = 0; i < 10; i++){
        printf("Roll Number: %d  marks: %d\n",
                a[i].rollnumber, a[i].marks);}
}


int linsearch(struct student a[10], int t){
    int i, flag = -1;

    for(i = 0; i < 10; i++){
        if(a[i].marks == t){
            flag = i;
            break;
        }
    }

    return flag;

}



int binsearch(struct student a[10], int t){
    int low = 0;
    int high = 9;
    int mid;
    int ret = -10;

    while(low <= high){

        mid = (low + high) / 2;

        if(a[mid].marks == t){
            int ret = mid;
            return ret;
        }

        else if(t < a[mid].marks){
            high = mid - 1;
        }

        else{
            low = mid + 1;
        }
    }

    printf("Student not found\n");
}


void selection(struct student a[10]){
    int i, j, min, temp;

    for(i = 0; i < 10; i++){
        min = i;

        for(j = i + 1; j < 10; j++){
            if(a[j].marks < a[min].marks){
                min = j;
            }
        }

        temp = a[i].marks;
        a[i].marks = a[min].marks;
        a[min].marks = temp;

        temp = a[i].rollnumber;
        a[i].rollnumber = a[min].rollnumber;
        a[min].rollnumber = temp;
    }

    printf("Array after sort:\n");

    display(a);
}


void insertion(struct student a[10]){
    int i, j, temp;

    for(i = 1; i < 10; i++){

        temp = a[i].marks;
        j = i - 1;

        while(j >= 0 && a[j].marks > temp){

            a[j + 1].marks = a[j].marks;
            a[j + 1].rollnumber = a[j].rollnumber;

            j--;
        }

        a[j + 1].marks = temp;


    }
    display(a);
}


void shell(struct student a[10]){
    int i, temp, gap = 10/2;
    int swapped;

    do{
        swapped = 1;

        do{
            swapped = 0;

            for(i=0; i<10-gap; i++){
                if(a[i].marks > a[i+gap].marks){
                    temp = a[i].marks;
                    a[i].marks = a[i+gap].marks;
                    a[i+gap].marks = temp;

                    swapped = 1;
                }
            }

        }while(swapped == 1);

        gap = gap/2;

    }while(gap >= 1);

    display(a);
}

int main(){

    struct student a[10];

    printf("Enter details of 10 students:\n");

    for(int i = 0; i < 10; i++){

        printf("Enter roll number: ");
        scanf("%d", &a[i].rollnumber);

        printf("Enter marks: ");
        scanf("%d", &a[i].marks);
    }

    printf("Enter target marks: ");
    int t;
    scanf("%d", &t);

    printf("Enter operation:");
    printf("1. Linear Search\n");
    printf("2. Bubble Sort\n");
    printf("3. Binary Search\n");
    printf("4. Selection Sort\n");
    printf("5. Insertion Sort\n");
    printf("6. Shell Sort\n");

    int option;
    scanf("%d", &option);

    switch(option){

        case 1:
            int flag = linsearch(a, t);
                if(flag != -1){
        printf("Student found at position: %d", flag + 1);
        printf("\n Roll Number: %d", a[flag].rollnumber);
        printf("Marks: %d", a[flag].marks);
    }
    else{
        printf("Student not found.");
    }
            break;

        case 2:
            
            break;

        case 3:
            selection(a);
            int ret = binsearch(a, t);
            if (ret>=0){
            printf("Student found at position: %d\n", ret + 1);
            printf("Roll Number: %d\n", a[ret].rollnumber);
            printf("Marks: %d\n", a[ret].marks);}
            break;

        case 4:
            selection(a);
            break;

        case 5:
            insertion(a);
            break;

        case 6:
            shell(a);
            break;

        default:
            printf("Invalid option");
            break;
    }

    return 0;
}