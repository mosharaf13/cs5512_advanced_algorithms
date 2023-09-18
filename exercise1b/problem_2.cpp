#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;
int randomArray[100000000];
int leftRightStack[100000000];

void fooSort(int a[], int n) {
    unsigned arraySize = static_cast<unsigned>(pow(2, 32)) - 1;
    unsigned* freqCount = new unsigned[arraySize];

    unsigned max_value = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max_value) {
            max_value = a[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        freqCount[a[i]]++;
    }

    // Step 2: For each non-zero value in 'freqCount', move it back into 'a'
    int index = 0;

    for (int i = 0; i <= max_value; ++i) {
        while (freqCount[i] > 0) {
            a[index] = i;
            index++;
            freqCount[i]--;
        }
    }

    delete[] freqCount;
}

void nonRecursiveQuickSortUsingRandomPivot(int list[], long long length) {
    long long left = 0, right = length - 1;

    int stackTop = -1;
    leftRightStack[++stackTop] = left;
    leftRightStack[++stackTop] = right;
    while (stackTop >= 0) {
        right = leftRightStack[stackTop--];
        left = leftRightStack[stackTop--];
        if (left < right) {
            long long randomIndex = left + rand() % (right - left + 1);
            int pivot = list[randomIndex];
            list[randomIndex] = list[left];
            list[left] = pivot;

            long long lastsmall = left;
            for (long long i = left + 1; i <= right; i++) {
                if (list[i] < pivot) {
                    lastsmall++;
                    int foo = list[i];
                    list[i] = list[lastsmall];
                    list[lastsmall] = foo;
                }
            }
            int foo = list[left];
            list[left] = list[lastsmall];
            list[lastsmall] = foo;

            leftRightStack[++stackTop] = left;
            leftRightStack[++stackTop] = lastsmall - 1;

            leftRightStack[++stackTop] = lastsmall + 1;
            leftRightStack[++stackTop] = right;
        }
    }
}

int main() {

    int listSizes[] = {10000, 100000, 1000000, 10000000, 100000000};

    for (int listSizeIndex = 0; listSizeIndex < 5; listSizeIndex++) {
        int listSize = listSizes[listSizeIndex];
        for (long long i = 0; i < listSize; i++) {
            int value = rand() % 100;
            randomArray[i] = value;
        }

        cout<< "Array size ";
        cout<< listSize <<endl;

        // Timing for mergeSort (random array)
        clock_t start = clock();
        fooSort(randomArray, listSize);
        clock_t end = clock();
        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        cout << fixed << setprecision(8) << "Time taken by Foosort (random array): " << time_taken << " seconds" << endl;


        // Timing for nonRecursiveQuickSortUsingFirstElement (random array)
        start = clock();
        nonRecursiveQuickSortUsingRandomPivot(randomArray, listSize);
        end = clock();
        time_taken = double(end - start) / CLOCKS_PER_SEC;
        cout << fixed << setprecision(8) << "Time taken by nonRecursiveQuickSortUsingRandomPivot (random array): " << time_taken << " seconds" << endl;

    }

    return 0;
}
