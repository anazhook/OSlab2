#include <iostream>
#include <windows.h>
using namespace std;

int ArraySize;
int* Array;
int Min = 0, Max = 0, avg;

HANDLE hMinMax, hAverage;

void min_max() {
    for (int i = 1; i < ArraySize; i++)
    {
        if (Array[i] > Array[Max])
            Max = i;
        Sleep(7);
        if (Array[i] < Array[Min])
            Min = i;
        Sleep(7);
    }
    cout << "Min and max values are: " << Array[Min] << " " << Array[Max] << endl;
}

void average() {
    int sum = 0;
    for (int i = 0; i < ArraySize; i++)
    {
        sum += Array[i];
        Sleep(12);
    }
    avg = sum / ArraySize;
    cout << "Average value is " << avg << endl;
}

int main() {
    cout << "enter array size and elements: \n";
    cin >> ArraySize;
    Array = new int[ArraySize];
    for (int i = 0; i < ArraySize; i++)
        cin >> Array[i];
    
    HANDLE hThread;
    DWORD IDThread;

    hMinMax = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)min_max, NULL, 0, &IDThread);
    if (hMinMax == NULL)
        return GetLastError();

    hAverage = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)average, NULL, 0, &IDThread);
    if (hMinMax == NULL)
        return GetLastError();

    // Wait for threads to finish
    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);
    int min = Array[Min];
    int max = Array[Max];
    // Replace min and max with average
    for (int i = 0; i < ArraySize; i++)
    {
        if (Array[i] == min || Array[i] == max)
            Array[i] = avg;
    }
    //Array[Max] = avg;
    //Array[Min] = avg;
    // Output result
    cout << "New array: \n";
    for (int i = 0; i < ArraySize; i++) {
        cout << Array[i] << " ";
    }
    cout << endl;

    // Clean up
    delete[] Array;
    CloseHandle(hMinMax);
    CloseHandle(hAverage);
    return 0;
}