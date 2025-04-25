/******************
Name: Liam Homay
ID: 333087807
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365

// Menu choices
#define addOne  1
#define addAll  2
#define stats   3
#define print   4
#define insights 5
#define deltas  6
#define done    7

// Arrays for brand and car type names
char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

// Function to print the main menu
void printMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

int main() {
    // 3D array to store sales data
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];

    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }
        }
    }

    int days = 0;   // Counter for the number of recorded days
    int choice;     // User menu selection

    printMenu();
    scanf("%d", &choice);

    while (choice != done) {
        switch (choice) {
            case addOne: {
                // Add sales data for a single brand on the current day
                int index;
                int sales[NUM_OF_TYPES];

                printf("Enter a car brand index (between 0-4) followed by a series of 4 integers, ");
                printf("each representing the daily sales sum for each car type (SUV, Sedan, Coupe, GT):\n");

                scanf("%d %d %d %d %d", &index, &sales[0], &sales[1], &sales[2], &sales[3]);

                if (index < 0 || index >= NUM_OF_BRANDS) {
                    printf("This brand is not valid\n");
                    break;
                }

                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    cube[days][index][i] = sales[i];
                }
                days++;
                break;
            }

            case addAll: {
                // Add sales data for all brands on the same day
                int pending[NUM_OF_BRANDS];
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    pending[i] = 1; // 1 if the brand still needs to be filled
                }

                int completed = 0;

                while (completed < NUM_OF_BRANDS) {
                    printf("No data for brands");
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        if (pending[i])
                            printf(" %s", brands[i]);
                    }
                    printf("\nPlease complete the data\n");

                    int index;
                    int sales[NUM_OF_TYPES];
                    scanf("%d %d %d %d %d", &index, &sales[0], &sales[1], &sales[2], &sales[3]);

                    if (index < 0 || index >= NUM_OF_BRANDS || pending[index] == 0) {
                        printf("This brand is not valid\n");
                        continue;
                    }

                    for (int i = 0; i < NUM_OF_TYPES; i++) {
                        cube[days][index][i] = sales[i];
                    }
                    pending[index] = 0;// switchd to 0 so that the brand will not be printed again
                    completed++;
                }
                days++;
                break;
            }

            case stats: {
                // Provide stats for a specific day
                int n;
                do {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &n);
                    if (n < 1 || n > days)
                        printf("Please enter a valid day.\n");
                } while (n < 1 || n > days);

                int total = 0;
                // Calculate total sales for the day
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        total += cube[n - 1][i][j];
                    }
                }

                // Find the best-selling brand
                int bestBrand = -1;
                int bestBrandSales = -1;
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    int sum = 0;
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        sum += cube[n - 1][i][j];
                    }
                    if (sum > bestBrandSales) {
                        bestBrandSales = sum;
                        bestBrand = i;
                    }
                }

                // Find the best-selling type
                int bestType = -1;
                int bestTypeSales = -1;
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    int sum = 0;
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                        sum += cube[n - 1][j][i];
                    }
                    if (sum > bestTypeSales) {
                        bestTypeSales = sum;
                        bestType = i;
                    }
                }

                printf("In day number %d:\n", n);
                printf("The sales total was %d\n", total);
                printf("The best sold brand with %d sales was %s\n", bestBrandSales, brands[bestBrand]);
                printf("The best sold type with %d sales was %s\n", bestTypeSales, types[bestType]);

                break;
            }

            case print: {
                // Print all stored sales data
                printf("*****************************************\n\n");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("Sales for %s:\n", brands[i]);

                    for (int j = 0; j < days; j++) {
                        int isEmpty = 1;
                        for (int k = 0; k < NUM_OF_TYPES; k++) {
                            if (cube[j][i][k] != -1) {
                                isEmpty = 0;
                                break;
                            }
                        }
                        if (isEmpty) continue;

                        printf("Day %d-", j + 1);
                        for (int k = 0; k < NUM_OF_TYPES; k++) {
                            printf(" %s: %d", types[k], cube[j][i][k]);
                        }
                        printf("\n");
                    }
                }
                printf("\n*****************************************\n");
                break;
            }

            case insights: {

                // Best-selling brand across all days
                int bestBrand = -1;
                int bestBrandSales = -1;
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    int sum = 0;
                    for (int j = 0; j < days; j++) {
                        for (int k = 0; k < NUM_OF_TYPES; k++) {
                            sum += cube[j][i][k];
                        }
                    }
                    if (sum > bestBrandSales) {
                        bestBrandSales = sum;
                        bestBrand = i;
                    }
                }

                // Best-selling type across all days
                int bestType = -1;
                int bestTypeSales = -1;
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    int sum = 0;
                    for (int j = 0; j < days; j++) {
                        for (int k = 0; k < NUM_OF_BRANDS; k++) {
                            sum += cube[j][k][i];
                        }
                    }
                    if (sum > bestTypeSales) {
                        bestTypeSales = sum;
                        bestType = i;
                    }
                }

                // Best-selling day
                int bestDay = -1;
                int bestDaySales = -1;
                for (int i = 0; i < days; i++) {
                    int sum = 0;
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                        for (int k = 0; k < NUM_OF_TYPES; k++) {
                            sum += cube[i][j][k];
                        }
                    }
                    if (sum > bestDaySales) {
                        bestDaySales = sum;
                        bestDay = i;
                    }
                }

                printf("The best-selling brand overall is %s: %d$\n", brands[bestBrand], bestBrandSales);
                printf("The best-selling type of car is %s: %d$\n", types[bestType], bestTypeSales);
                printf("The most profitable day was day number %d: %d$\n", bestDay + 1, bestDaySales);
                break;
            }

            case deltas: {
                // Show average delta per brand from first to last day
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    float total = 0;
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        total += cube[days - 1][i][j] - cube[0][i][j];
                    }
                    float delta = total / (days - 1);
                    printf("Brand: %s, Average Delta: %f\n", brands[i], delta);
                }
                break;
            }

            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }

    printf("Goodbye!\n");
    return 0;
}
