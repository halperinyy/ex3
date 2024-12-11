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

//Those are the types. We do not buy the people's wagen!!
#define B_TOYOGA    0
#define B_HYUN_NI   1
#define B_MAZDUH    2
//for a clarificaiton about this name, please open wikipidia
#define B_NAZI      3
#define B_KEYYUH    4

//The types
#define SUV   0
#define SEDAN 1
#define COUPE 2
#define GT    3

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

//My helpful functions!
int FindMaxIdx(int arr[], int size);
int FindMaxVal(int arr[], int size);
int FindMinIdx(int arr[], int size);
int FindMinVal(int arr[], int size);
int GetArrSum(int arr[], int size);

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
void FuncStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void PrintAllSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysFilled);

void PrintAllBrandSum(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES]);
void PrintBestSoldBrand(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES]);
void PrintBestSoldType(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES]);

void PrintAllTimeBestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void PrintAllTimeBestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void PrintBestDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);

void PrintDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);

int main()
{
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int choice = addOne;
    int day = 0;
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

    while(choice != done)
    {
        printMenu();
        //Get the choice for the menu
        scanf("%d", &choice);
        switch(choice){
            //This case is not really used, but we stil put it here
            case addOne:
                {
                    int filledArr[NUM_OF_BRANDS] = {0};
                    FuncAddOne(cube[day], filledArr);
                    day++;
                }
                break;
            case addAll:
                FuncAddAll(cube, day);
                day++;
                break;

            case stats:
                FuncStats(cube, day);
                break;

            case print:
                PrintAllSales(cube, day);
                break;
            case insights:
                PrintAllTimeBestBrand(cube, day);
                PrintAllTimeBestType(cube, day);
                PrintBestDay(cube, day);
                break;
            case deltas:
                PrintDeltaMetrics(cube, day);
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


//This function returns the index of the maximum value of a one dimensional array
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

//This function returns the maximum value of a one dimensional array
int FindMaxVal(int arr[], int size)
{
    int maxIndex = FindMaxIdx(arr, size);
    return arr[maxIndex];
}

//This function returns the index of the minimum value of a one dimensional array
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

//This function returns the minimum value of a one dimensional array
int FindMinVal(int arr[], int size)
{
    int minIndex = FindMinIdx(arr, size);
    return arr[minIndex];
}

//This function returns the sum of a one dimensional array
int GetArrSum(int arr[], int size)
{
    int sum = 0;
    for(int i = 0 ; i < size ; i++)
    {
        sum += arr[i];
    }
    return sum;
}

void FuncAddOne(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES], int filledBrandsArr[])
{
    int brand,suvSales, sedanSales, coupeSales, gtSales;
    scanf(" %d", &brand);

    if(brand < NUM_OF_BRANDS && brand >= 0 && filledBrandsArr[brand] == 0)
    {
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

    //As long as we are missing some brand, wait for its input
    while(finished == 0)
    {
        //Print the missing brands
        printf("No data for brands");
        for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
        {
            if(filledArr[b] == 0)
            {
                printf(" %s",brands[b]);
            }
        }
        printf("\n");
        printf("Please complete the data\n");
        //This function inserts some brand and update the filledArr
        FuncAddOne(cube[day], filledArr);
        //We check with "FindMinVal" if there are missing brands (a filled brand will be marked with 1 in the filledArr array).
        finished = FindMinVal(filledArr, NUM_OF_BRANDS);
    }
}

void FuncStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int wantedDay = DAYS_IN_YEAR;  

    //As long as the day invalid, continue to expect some valid day.
    while(wantedDay < 0 || wantedDay > day)
    {
        printf("What day would you like to analyze?\n");
        scanf(" %d", &wantedDay);
        //The input day format is 1-365 (although the exercise stated that it should be 0-364), so we substract the day by one in oder to access the corect day from  the array.
        if(0 < wantedDay && wantedDay <= day)
        {
            printf("In day number %d:\n", wantedDay);
            PrintAllBrandSum(cube[wantedDay-1]);
            PrintBestSoldBrand(cube[wantedDay-1]);
            PrintBestSoldType(cube[wantedDay-1]);
            return;
        }
        else
        {
            printf("Please enter a valid day.\n");
        }
    }
}

int GetDayTotalSales(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int brandSalesArr[NUM_OF_BRANDS] = {0};
    
    for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
    {
        brandSalesArr[b] = GetArrSum(singleDayArr[b], NUM_OF_TYPES);
    }

    return GetArrSum(brandSalesArr, NUM_OF_BRANDS);
}

void PrintAllBrandSum(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES])
{
    printf("The sales total was %d\n", GetDayTotalSales(singleDayArr));
}

void PrintBestSoldBrand(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int brandSalesArr[NUM_OF_BRANDS] = {0};

    for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
    {
        brandSalesArr[b] = GetArrSum(singleDayArr[b], NUM_OF_TYPES);
    }  

    int bestBrand = FindMaxIdx(brandSalesArr, NUM_OF_BRANDS);
    int bestBrandSales = brandSalesArr[bestBrand];
    printf("The best sold brand with %d sales was %s\n", bestBrandSales, brands[bestBrand]);
}

void PrintBestSoldType(int singleDayArr[NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int typeSalesArr[NUM_OF_TYPES] = {0};
    int sum = 0;
    for(int i = 0 ; i < NUM_OF_TYPES; i++)
    {
        for(int j = 0 ; j < NUM_OF_BRANDS; j++)
        {
            sum += singleDayArr[j][i];
        }
        typeSalesArr[i] = sum;
        sum = 0;
    }
    int bestType = FindMaxIdx(typeSalesArr, NUM_OF_TYPES);
    int bestTypeSales = typeSalesArr[bestType];
    printf("The best sold type with %d sales was %s\n", bestTypeSales, types[bestType]);
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

int arry[NUM_OF_BRANDS] = {0};

void  PrintAllTimeBestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int brandTotalSalesArr[NUM_OF_BRANDS] = {0};

    //We calculate an array of total sales per brand
    for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
    {
        //Get the total sales for a brand, for a day, and add it to the brand's sales sum
        for(int d = 0; d < day ; d++)
        {
            brandTotalSalesArr[b] += GetArrSum(cube[d][b], NUM_OF_TYPES);
        }
    }

    //The maximal entry in the brandTotalSalesArr is the brand that was the most profitable in all the days.
    int bestBrand = FindMaxIdx(brandTotalSalesArr, NUM_OF_BRANDS);
    int bestBrandSales = brandTotalSalesArr[bestBrand];
    printf("The best-selling brand overall is %s: %d$\n", brands[bestBrand], bestBrandSales);
}

void PrintAllTimeBestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int typeSalesArray[NUM_OF_TYPES] = {0};

    //We calculate an array of total sales per type, for all days
    for(int t = 0 ; t < NUM_OF_TYPES ; t++)
    {
        for(int d = 0 ; d < day ; d++)
        {
            for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
            {
                typeSalesArray[t] += cube[d][b][t];
            }
        }
    }

    //The maximal entry in the typeSalesArray is the type that was the most profitable in all the days.
    int bestType = FindMaxIdx(typeSalesArray, NUM_OF_TYPES);
    int bestTypeSales = typeSalesArray[bestType];
    printf("The best-selling type of car is %s: %d$\n", types[bestType], bestTypeSales);
}


void PrintBestDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int bestDayArr[DAYS_IN_YEAR] = {0};
    
    //Calculate each day profit
    for(int d = 0 ; d < day ; d++)
    {
        bestDayArr[d] = GetDayTotalSales(cube[d]);
    }

    //Get the best day and its sales
    int bestDay = FindMaxIdx(bestDayArr, DAYS_IN_YEAR);
    int bestDaySales = bestDayArr[bestDay];
    printf("The most profitable day was day number %d: %d$\n", bestDay+1, bestDaySales);
}

void PrintDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    //We need at least 2 days for this function
    if(day<=1)
    {
        return;
    }

    for(int b = 0 ; b < NUM_OF_BRANDS ; b++)
    {
        int firstDaySales = GetArrSum(cube[0][b], NUM_OF_TYPES);
        int lastDaySales = GetArrSum(cube[day-1][b], NUM_OF_TYPES);

        //The delta metrics is the last day sales minus the first day sales, dividing by days minus 1
        float averageDelta = (float)(lastDaySales - firstDaySales) / (float)(day - 1);
        
        printf("Brand: %s, Average Delta: %f\n", brands[b], averageDelta);
    }
}