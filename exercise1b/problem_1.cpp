#include <iostream>
#include <cmath>

using namespace std;

void fooSort(int a[], int n) {
    unsigned arraySize = static_cast<unsigned>(pow(2, 32)) - 1;
    unsigned* freqCount = new unsigned[arraySize];

    unsigned max_value = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max_value) {
            max_value = a[i];
        }
    }

    // Now you can increment freqCount[a[i]] inside your loop
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


}

int main() {

    int a[] = {3, 4, 6, 4, 3, 1, 4, 1, 10};
    int n = sizeof(a) / sizeof(a[0]);

    fooSort(a,n);

    for (int i = 0; i < n; ++i) cout<<a[i]<<endl;
}
