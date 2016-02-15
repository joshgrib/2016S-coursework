#include <iostream>
using namespace std;

int mystery1(int a, int b) {
    int c = a - b,
        d = (c >> 7) & 1,
        mystery = a - c * d;
    return mystery;
}

void mystery2(int values[], int i, int j) {
    values[i] = values[i] ^ values[j];
    values[j] = values[i] ^ values[j];
    values[i] = values[i] ^ values[j];
}

int mystery3(int x, int y) {
    int s, c;
    s = x ^ y;
    c = x & y;
    while (c != 0) {
        c = c << 1;
        x = s;
        y = c;
        s = x ^ y;
        c = x & y;
    }
    return s;
}

int main(){
    cout << mystery1(7, 7) << endl;
    cout << mystery1(2, 80) << endl;
    return 0;
}
