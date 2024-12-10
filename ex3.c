/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

#define B_TOYOGA    0
#define B_HYUN_NI   1
#define B_MAZDUH    2
#define B_NAZI      3
#define B_KEYYUH    4


#define SUV   0
#define SEDAN 1
#define COUPE 2
#define GT    3

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

int FindMaxIdx(int arr[], int size);

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
        "1.Enter Daily Data For A Brand\n"
        "2.Populate A Day Of Sales For All Brands\n"
        "3.Provide Daily Stats\n"
        "4.Print All Data\n"
        "5.Provide Overall (simple) Insights\n"
        "6.Provide Average Delta Metrics\n"
        "7.exit\n");
}

void FuncAddOne(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES], int filledBrandsArr[]);
void FuncAddAll(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void PrintAllSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysFilled);
void typePrinter(int type);
void brandprinter(int brand);

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    // int days[NUM_OF_BRANDS] = {0};
    int choice = addOne;
    int day = 0;
    // int sumOfBrnds[NUM_OF_BRANDS];
    // int sumOfTypes[4];
    //Initialize all cube with -1
    for (int d = 0 ; d < DAYS_IN_YEAR ; d++)
    {
        for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
        {
            for(int t = 0 ; t < NUM_OF_TYPES ; t++)
            {
                cube[d][b][t] = -1;
            }
        }
    }

    while(choice != done){
        printMenu();
        scanf("%d", &choice);
        switch(choice){
            case addOne:{
                    int filledArr[NUM_OF_BRANDS] = {0};
                    FuncAddOne(cube[day], filledArr);
                    day++;
                }
                break;
            case addAll:{
                    FuncAddAll(cube, day);
                    day++;
                }
                break;
            case stats:{
                // int brand,suv, sedan, coupe, gt,sum = 0;
                // scanf(" %d %d %d %d %d", &brand, &suv, &sedan, &coupe, &gt);
                // sum = suv + sedan + coupe + gt;
                // int whatday,sum = 0,k = 0;
                // printf("What day would you like to analyze?\n");
                // scanf(" %d", &whatday);
                // for(int j = 0; j < 5;j++){
                //     for(int i = 0; i < 4;i++){
                //         sum = sum + cube[whatday][j][i];
                //     }
                // }
                // printf("The sales total was %d\n" ,sum); //finding the most salaing barnd
                // for(int i = 0;i < 5;i++){
                //     sum = 0;
                //     for(int j = 0; j < 4;j++){
                //         sum = sum + cube[whatday][i][j];
                //     }
                //     sumOfBrnds[i] = sum;
                // }
                // int maxOfBrands = FindMaxIdx(sumOfBrnds ,NUM_OF_BRANDS);
                // brandprinter(maxOfBrands);

                // for(int i = 0;i < 4;i++){
                //     sum = 0;
                //     for(int j = 0; j < 5;j++){
                //         sum = sum + cube[whatday][j][i];
                //     }
                //     sumOfTypes[i] = sum;
                // }
                // int maxOfTypes = FindMaxIdx(sumOfTypes ,NUM_OF_TYPES);
                // brandprinter(maxOfTypes);

                }
                break;

            case print:{
                    PrintAllSales(cube, day);
                }
                break;
            case insights:{

                }
                break;
            case deltas:{

                }
                break;
            case done:
                break;
            default:
                printf("Invalid input\n");
        }
    }
    printf("Goodbye!\n");
    return 0;
}



int FindMaxIdx(int arr[], int size)
{
    int i_max = 0;

    for(int i = 0 ; i < size ; i++)
    {
        if(arr[i_max] < arr[i])
        {
            i_max = i;
        }
    }

    return i_max;
}

int FindMaxVal(int arr[], int size)
{
    int maxIndex = FindMaxIdx(arr, size);
    return arr[maxIndex];
}

int FindMinIdx(int arr[], int size)
{
    int i_min = 0;

    for(int i = 0 ; i < size ; i++)
    {
        if(arr[i_min] > arr[i])
        {
            i_min = i;
        }
    }

    return i_min;
}

int FindMinVal(int arr[], int size)
{
    int minIndex = FindMinIdx(arr, size);
    return arr[minIndex];
}

void FuncAddOne(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES], int filledBrandsArr[])
{
    int brand,suvSales, sedanSales, coupeSales, gtSales;
    scanf(" %d", &brand);

    if(brand < NUM_OF_BRANDS && brand >= 0 && filledBrandsArr[brand] == 0){
        scanf(" %d %d %d %d", &suvSales, &sedanSales, &coupeSales, &gtSales);
        singleDayArr[brand][SUV] = suvSales;
        singleDayArr[brand][SEDAN] = sedanSales;
        singleDayArr[brand][COUPE] = coupeSales;
        singleDayArr[brand][GT] = gtSales;
        //Notify that we have filled this brand already.
        filledBrandsArr[brand] = 1;
    }
    else
    {
        printf("This brand is not valid\n");
    }
}

void FuncAddAll(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{

    int filledArr[NUM_OF_BRANDS] = {0};
    int finished = 0;

    while(finished == 0)
    {
        //printf("No data for brands Toyoga, Mazduh, FolksVegan, Key-Yuh.\n");
        printf("No data for brands");
        for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
        {
            if(filledArr[b] == 0)
            {
                printf(" %s",brands[b]);
            }
        }
        printf("\n");
        printf("Please complete the data.\n");

        FuncAddOne(cube[day], filledArr);

        finished = FindMinVal(filledArr, NUM_OF_BRANDS);
    }
}

void PrintAllSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysFilled)
{
    printf("*****************************************\n\n");

    for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
    {
        printf("Sales for %s:\n", brands[b]);
        for(int d = 0 ; d < daysFilled ; d++)
        {
            printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n", d+1, cube[d][b][SUV], cube[d][b][SEDAN], cube[d][b][COUPE], cube[d][b][GT]);
        }
    }

    printf("\n*****************************************\n");
}

// void typePrinter(int type)
// {
//     switch (type){
//         case 0:
//             printf("SUV\n");
//             break;
//         case 1:
//             printf("Sedan\n");
//             break;
//         case 2:
//             printf("Coupe\n");
//             break;
//         case 3:
//             printf("GT\n");
//             break;
//     }
// }

// void brandprinter(int brand)
// {
//         switch (brand){
//         case 0:
//             printf("Toyoga\n");
//             break;
//         case 1:
//             printf("HyunNight\n");
//             break;
//         case 2:
//             printf("Mazduh\n");
//             break;
//         case 3:
//             printf("FolksVegan\n"); //also known as "nazi car"
//             break;
//         case 4:
//             printf("Key-Yuh\n");
//             break;
  
//     }
// }
