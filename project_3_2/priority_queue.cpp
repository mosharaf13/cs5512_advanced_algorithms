#include <iostream>
#include <vector>

int H[50];
int sizee = -1;

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return ((2 * i) + 1);
}

int rightChild(int i) {
    return ((2 * i) + 2);
}

void shiftUp(int i) {
    while (i > 0 && H[parent(i)] < H[i]) {
        std::swap(H[parent(i)], H[i]);
        i = parent(i);
    }
}

void shiftDown(int i) {
    int maxIndex = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l <= sizee && H[l] > H[maxIndex]) {
        maxIndex = l;
    }

    if (r <= sizee && H[r] > H[maxIndex]) {
        maxIndex = r;
    }

    if (i != maxIndex) {
        std::swap(H[i], H[maxIndex]);
        shiftDown(maxIndex);
    }
}

void insert(int p) {
    sizee = sizee + 1;
    H[sizee] = p;
    shiftUp(sizee);
}

int extractMax() {
    int result = H[0];
    H[0] = H[sizee];
    sizee = sizee - 1;
    shiftDown(0);
    return result;
}

void changePriority(int i, int p) {
    int oldp = H[i];
    H[i] = p;

    if (p > oldp) {
        shiftUp(i);
    } else {
        shiftDown(i);
    }
}

int getMax() {
    return H[0];
}

void remove(int i) {
    H[i] = getMax() + 1;
    shiftUp(i);
    extractMax();
}

int main() {
//    int expected[] = {45, 31, 20, 14, 13, 11, 7, 7, 12}; // Predefined array for validation
    int expectedAfterInsert[] = {45, 31, 14, 13, 20, 7, 11, 12, 7};
    insert(45);
    insert(20);
    insert(14);
    insert(12);
    insert(31);
    insert(7);
    insert(11);
    insert(13);
    insert(7);

    int i = 0;
    bool insertionValid = true;

    std::cout << "Priority Queue : ";
    while (i <= sizee) {
        std::cout << H[i] << " ";

        // Check if inserted values match the expected values
        if (H[i] != expectedAfterInsert[i]) {
            insertionValid = false;
        }
        i++;
    }

    std::cout << "\n";

    if (insertionValid) {
        std::cout << "Insertion test: PASSED\n";
    } else {
        std::cout << "Insertion test: FAILED\n";
    }

    std::cout << "Node with maximum priority : " << extractMax() << "\n";

    std::cout << "Priority queue after extracting maximum : ";
    int j = 0;
    bool extractionValid = true;
    int expectedAfterExtract[] = {31, 20, 14, 13, 7, 7, 11, 12};

    while (j <= sizee) {
        std::cout << H[j] << " ";

        // Check if extracted values match the expected values
        if (H[j] != expectedAfterExtract[j]) {
            extractionValid = false;
        }
        j++;
    }

    std::cout << "\n";

    if (extractionValid) {
        std::cout << "Extraction test: PASSED\n";
    } else {
        std::cout << "Extraction test: FAILED\n";
    }

    changePriority(2, 49);

    std::cout << "Priority queue after priority change : ";
    int k = 0;
    bool changePriorityValid = true;
    int expectedAfterPriorityChange[] = {49, 20, 31, 13, 7, 7, 11, 12};

    while (k <= sizee) {
        std::cout << H[k] << " ";

        // Check if modified values match the expected values
        if (H[k] != expectedAfterPriorityChange[k]) {
            changePriorityValid = false;
        }
        k++;
    }

    std::cout << "\n";

    if (changePriorityValid) {
        std::cout << "Change Priority test: PASSED\n";
    } else {
        std::cout << "Change Priority test: FAILED\n";
    }

    remove(3);
    std::cout << "Priority queue after removing the element : ";
    int l = 0;
    bool removeValid = true;
    int expectedAfterElementRemoval[] = {49, 20, 31, 12, 7, 7, 11};

    while (l <= sizee) {
        std::cout << H[l] << " ";

        // Check if values after removal match the expected values
        if (H[l] != expectedAfterElementRemoval[l]) {
            removeValid = false;
        }
        l++;
    }

    std::cout << "\n";

    if (removeValid) {
        std::cout << "Remove test: PASSED\n";
    } else {
        std::cout << "Remove test: FAILED\n";
    }

    return 0;
}
