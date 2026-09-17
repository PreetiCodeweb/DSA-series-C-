#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    cout << arr[0] << endl;
    cout << arr[2] << endl;
    cout << arr[4] << endl;

    return 0;
}


/*
Without an array:
int m1, m2, m3, m4, m5;
This becomes difficult to manage.
With an array:
int marks[100];
You can access the marks using an index:
marks[0]   // First student's marks
marks[1]   // Second student's marks
marks[99]  // Hundredth student's marks
Arrays allow you to:
Store many values under one name.
Process values using loops.
Search for elements.
Sort data.
Find maximum and minimum values.
Perform mathematical operations.
Solve DSA problems efficiently. 
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[100];

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Array elements: ";

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}

/*
Enter number of elements: 5
Enter elements: 10 20 30 40 50

Array elements: 10 20 30 40 50
*/

