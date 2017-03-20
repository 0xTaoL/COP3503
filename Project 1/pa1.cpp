#include <iostream>
#include <iomanip>

using namespace std;

int isValid(int size);
int** newSquare(int size);
void squareGen(int size, int **square);
int** rotateSquare(int size, int **square);
void printSquare(int size, int **square);
void checkSum(int size, int **square);

int main() {

    int size;
    cout << "Enter the size of a magic square:";
    cin >> size;

    //checks if input is within range and odd number, ask again if not
    int verifiedSize = isValid(size);

    //creates square, prints, and verifies
    int** square1 = newSquare(verifiedSize);
    squareGen(verifiedSize,square1);
    cout << "Magic Square #1 is: \n\n";
    printSquare(verifiedSize,square1);
    checkSum(verifiedSize, square1);
    int** square2 = rotateSquare(verifiedSize, square1);
    cout << "\nMagic Square #2 is: \n\n";
    printSquare(verifiedSize,square2);
    checkSum(verifiedSize, square2);
    int** square3 = rotateSquare(verifiedSize, square2);
    cout << "\nMagic Square #3 is: \n\n";
    printSquare(verifiedSize,square3);
    checkSum(verifiedSize, square3);
    int** square4 = rotateSquare(verifiedSize, square3);
    cout << "\nMagic Square #4 is: \n\n";
    printSquare(verifiedSize,square4);
    checkSum(verifiedSize, square4);

    return 0;
}

int isValid(int size){

    int validNumber = size;
    int invalidNumber;

    if(size % 2 == 0 || size < 3 || size > 15){
        cout << "Error: Number is not odd number between 3 and 15.\nPlease Enter a Valid Number: ";
        cin >> invalidNumber;
        validNumber = isValid(invalidNumber);
    }

    return validNumber;
}

int** newSquare(int size){

    //creates new 2d array
    int** square = new int*[size];
    for (int i = 0; i < size; i++) {
        square[i] = new int[size];
    }

    //set all elements in array to 0
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            square[i][j] = 0;
        }
    }

    return square;
}

void squareGen(int size, int **square){

    //generates magic square using the siamese method
    int row = 0, col = size/2;

    for (int i = 1; i <= size*size; i++) {
        square[row][col] = i;
        row--;
        col++;

        if ((row >= 0 && col >= 0 && row < size && col < size && square[row][col] != 0) ||
            (row < 0 && col == size)) {
            row += 2;
            col--;
        }

        if (row < 0) {
            row = size-1;
        }

        if (col == size) {
            col = 0;
        }
    }
}

int** rotateSquare(int size, int **square){

    //creates new 2d array
    int** rotatedSquare = new int*[size];
    for (int i = 0; i < size; i++) {
        rotatedSquare[i] = new int[size];
    }

    //rotates 90 degrees by transposing and reversing each row
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            rotatedSquare[i][j] = square[size - j - 1][i];
        }
    }

    return rotatedSquare;
}

void printSquare(int size, int **square){

    //prints the square
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(5) << square[i][j];
        }
        cout << "\n";
    }
}

void checkSum(int size, int **square){

    //calculates the sum of rows, columns and diagonals
    cout << "\nChecking the sums of every row:     ";
    for (int i = 0; i < size; i++) {
        int rowSum = 0;
        for(int j = 0; j < size; j++) {
            rowSum += square[i][j];
        }
        cout << setw(5) << rowSum;
    }
    cout << "\n";

    cout << "Checking the sums of every column:  ";
    for (int j = 0; j < size; j++) {
        int colSum = 0;
        for(int i = 0; i < size; i++) {
            colSum += square[i][j];
        }
        cout << setw(5) << colSum;
    }
    cout << "\n";

    cout << "Checking the sums of every diagonal:";
    int diagSum = 0;
    for (int i = 0; i < size; i++) {
        diagSum += square[i][i];
    }
    cout << setw(5) << diagSum;

    diagSum = 0;
    for (int i = 0; i < size; i++) {
        diagSum += square[i][size-1 - i];
    }
    cout << setw(5) << diagSum;
    cout << "\n";
}