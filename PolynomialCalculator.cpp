

#include <iostream>
#include <vector>

using namespace std;

constexpr int CHOICE_QUIT = 11;
constexpr int MAX_DEGREE = 1000;

using RationalNumber = pair<int,int>;


void addPolynomials();
void subtractPolynomials();
void multiplyPolynomials();
void dividePolynomials();
void multiplyPolynomialByScalar();
void findValueAtNumber();
void findGCDOfTwoPolynomials();
void displayVieta();
void representInPowers();
void factorAndFindRoots();
vector<RationalNumber> readPolynomial();
void printPolynomial(vector<RationalNumber> polynomial);
RationalNumber readRationalNumber();
int gcdNums(int a, int b);
int minNumber(int a, int b);
int lcmNums(int a, int b);
void printRational(RationalNumber num)
{
    int numerator = num.first;
    int denominator = num.second;
    if (numerator == 0)
    {
        cout << "0";
        return;
    }
    if (denominator == 1)
    {
        cout << numerator;
        return;
    }

    cout << numerator << "/" << denominator;
}
vector<RationalNumber> returnMultipliedPolynomialByScalar(vector<RationalNumber> P, RationalNumber scalar);

int main()
{
    cout << "Welcome to Polynomial Calculator - a mini project intended to work with polynomials with rational coefficients \nChoose one of the following functionalities:\n";
    cout << "1) Add polynomials \n2) Subtract polynomials \n3) Multiply polynomials \n4) Divide polynomials \n5) Multiply polynomial by scalar) \n6) Find value of polynomial at a given number \n7) Find GCD of two polynomials \n8) Display Vieta's formulas for a given polynomial \n9) Represent a polynomial in powers of (x+a) \n10) Factor polynomial and find its rational roots \n11) Quit program \n";
    cout << "Enter your option here>> ";
    int choice=0;
    while (choice != CHOICE_QUIT)
    {
        cin >> choice;
        switch (choice)
        {
        case 1: addPolynomials();break;
        case 2: subtractPolynomials();break;
        case 3: multiplyPolynomials();break;
        case 4: dividePolynomials(); break;
        case 5: multiplyPolynomialByScalar();break;
        case 6: findValueAtNumber();break;
        case 7: findGCDOfTwoPolynomials();break;
        case 8: displayVieta();break;
        case 9: representInPowers();break;
        case 10: factorAndFindRoots();break;
        case CHOICE_QUIT: break;
        default: cout << "The number you need to choose is between 1 and 11!" << endl;
            break;
        }
    }
   
}

RationalNumber readRationalNumber() {
    int numerator, denominator = 1; // Default denominator is 1
    char slash; // To check for the '/' character

    cin >> numerator; // First, read the numerator or plain integer

    if (cin.peek() == '/') { // Check the next character in the input stream
        cin >> slash >> denominator; // If '/' is found, read the denominator
        if (denominator == 0) {
            cout << "Error: Division by zero is not allowed!" << endl;
            denominator = 1; // Default safe value
        }
    }

    return { numerator, denominator };
}

vector<RationalNumber> readPolynomial()
{
    int degree;
    cout << "Enter degree of your polynomial>> ";
    cin >> degree;

    vector<RationalNumber> polynomial;
    RationalNumber currentNum;

    for (int i = degree;i >= 0;i--)
    {
        cout << "Enter coefficient before x^" << i << ">> ";
        currentNum = readRationalNumber();
        polynomial.push_back(currentNum);
    }

  
    return polynomial;
}

void printPolynomial(vector<RationalNumber> polynomial)
{
    int size = polynomial.size();
    if (size == 0)
    {
        // HANDLE EXCEPTION
        cout << "Polynomial is empty" << endl;
        return;
    }

    // Start with the highest degree term
    int degree = size - 1;
    bool firstTerm = true;  // To avoid printing "+" at the beginning

    // Traverse each term of the polynomial
    for (int i = 0; i < size; i++)
    {
        RationalNumber currentNum = polynomial[i];
        int numerator = currentNum.first;
        int denominator = currentNum.second;

        // Skip zero coefficients
        if (numerator == 0)
        {
            degree--;
            continue;
        }

        // If it's not the first term, print "+" for positive coefficients
        if (!firstTerm && numerator > 0)
        {
            cout << "+";
        }

        // Handle the case when the coefficient is 1 or -1 (don't print the 1 or -1)
        if (numerator == 1 && denominator == 1)
        {
            if (degree == 0)
            {
                cout << "1";
            }
            else if(degree==1)
            {
                cout << "x";
            }
            else {
                cout << "x^" << degree;
            }
        }
        else if (numerator == -1 && denominator == 1)
        {
            if (degree == 0)
            {
                cout << "-1";
            }
            else if(degree==1)
            {
                cout << "-x";
            }
            else {
                cout << "-x^" << degree;
            }
        }
        else
        {
            // Print the numerator if it's not 1 or -1
            if (numerator != 1 || denominator != 1)
            {
                cout << numerator;
            }

            // Print the denominator if necessary
            if (denominator != 1)
            {
                cout << "/" << denominator;
            }

            // Print the power of x part (skip for degree 0)
            if (degree >= 2)
            {
                cout << "x^" << degree;
            }
            else if (degree == 1)
            {
                cout << "x";
            }
        }

        // Mark that it's no longer the first term
        firstTerm = false;

        // Decrease degree for the next term
        degree--;
    }

    cout << endl;
}

int minNumber(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    return a;
}

int abs(int a)
{
    if (a > 0)
    {
        return a;
    }
    return -a;
}

int gcdNums(int a, int b)
{
    if (a == 0 || b == 0)
    {
        return 1;
    }

    a = abs(a);
    b = abs(b);

    // Find Minimum of a and b
    int res = minNumber(a, b);

    // Testing divisiblity with all numbers starting from
  // min(a, b) to 1

    while (res > 1) {

        // If any number divide both a and b, so we
        // got the answer
        if (a % res == 0 && b % res == 0)
            break;
        res--;
    }
    return res;
}

int lcmNums(int a, int b)
{

    return a * b / gcdNums(a, b);
}

bool isZeroPolynomial(vector<RationalNumber> P)
{
    int size = P.size();
    int numerator;
    for (int i = 0;i < size;i++)
    {
        numerator = P[i].first;

        if (numerator != 0)
        {
            return false;
        }
    }
    return true;
}
bool isConstantPolynomial(vector<RationalNumber> P)
{
    int endIndex = P.size()-1;
    int numerator;

    //We loop till we reach the second to last element
    for (int i = 0;i < endIndex;i++)
    {
        numerator = P[i].first;

        if (numerator != 0)
        {
            return false;
        }
    }
    
    return true;
}

vector<RationalNumber> addDegree(vector<RationalNumber> P, int degree)
{
    //since we have increased the degree,the new P will be of type old P * x^degree + 0x^0 + ... 0x^1 + ... + 0x^degree-1  
    RationalNumber zeroCoefficient = { 0,1 };
    for (int i = 0;i < degree;i++)
    {
        P.push_back(zeroCoefficient);
    }

    return P;
}

vector<RationalNumber> resizePolynomial(vector<RationalNumber> P)
{
    vector<RationalNumber> result;
     
    
    int size = P.size();
    int numerator;
    bool hasPredecessor = false;

    for (int i = 0;i < size;i++)
    {
        numerator = P[i].first;

        if (numerator != 0 || hasPredecessor)
        {
            hasPredecessor = true;
            result.push_back(P[i]);
        }
    }



    return result;
}

vector<RationalNumber> copyVector(vector<RationalNumber> P)
{
    vector<RationalNumber> result;
    
    int size = P.size();
    for (int i = 0;i < size;i++)
    {
        result.push_back(P[i]);
    }

    return result;
}

RationalNumber ReturnSumOfRationalNums(RationalNumber elP, RationalNumber elQ)
{
    RationalNumber numRes;
    int numeratorP, denominatorP, numeratorQ, denominatorQ;
    
    numeratorP = elP.first;
    denominatorP = elP.second;
    numeratorQ = elQ.first;
    denominatorQ = elQ.second;

    //each number is presented in this format : {numerator} / { denominator }
    // in order to find the sum of the elements they need to have matching denominators
    
    if (denominatorP != denominatorQ)
    {
        // we find the lcm of the denominators and then multiply the numerators with the ( lcm / denominator ) 
        int lcmDenominators = lcmNums(denominatorP, denominatorQ);

        numeratorP *= lcmDenominators / denominatorP;
        numeratorQ *= lcmDenominators / denominatorQ;
        denominatorP = lcmDenominators;
        denominatorQ = lcmDenominators;
    }

    //when the denominators are equal, we can find the sum of their numerators
    numRes.first = numeratorP + numeratorQ;
    numRes.second = denominatorP;

    return numRes;
}

RationalNumber ReturnMultiplicationRationalNums(RationalNumber elP, RationalNumber elQ)
{
    RationalNumber res;

    int numeratorP = elP.first;
    int denominatorP = elP.second;
    int numeratorQ = elQ.first;
    int denominatorQ = elQ.second;

     numeratorP *= numeratorQ;
     denominatorP *= denominatorQ;

    // we find the gcd of the new numeratorP and new denominatorP 
    int gcd = gcdNums(numeratorP, denominatorP);

    //Now we abbreviate the fractions

    numeratorP /= gcd;
    denominatorP /= gcd;

    res = { numeratorP,denominatorP };

    return res;
}

RationalNumber ReturnDivisionOfRationalNums(RationalNumber elP, RationalNumber elQ)
{
    RationalNumber result;

    // Example : 2/3 / ( 4 / 5) = 2/3 * 5/4 = 10/12  = 5/6

    int numeratorP, denominatorP, numeratorQ, denominatorQ, numeratorResult, denominatorResult;

    numeratorP = elP.first;
    denominatorP = elP.second;
    numeratorQ = elQ.first;
    denominatorQ = elQ.second;

    //we flip the second rational
    numeratorResult = numeratorP * denominatorQ; 
    denominatorResult = numeratorQ * denominatorP;
     
    //now we make sure that it is simplified
    int gcd = gcdNums(numeratorResult, denominatorResult);
    numeratorResult /= gcd;
    denominatorResult /= gcd;

    result = { numeratorResult, denominatorResult };
   
    return result;
}

vector<RationalNumber> returnSumOfPolynomials(vector<RationalNumber> P, vector<RationalNumber> Q)
{
    //resulting vector
    vector<RationalNumber> R;

    int sizeP = P.size();
    int sizeQ = Q.size();

    // if either one contains elements from higher degree, then we just pass them to the resulting polynomial R

    int indexP = 0;
    int indexQ = 0;

    if (sizeP > sizeQ)
    {
        int difference = sizeP - sizeQ;
        while (indexP != difference)
        {
            R.push_back(P[indexP++]);
        }
    }
    else if (sizeQ > sizeP)
    {
        int difference = sizeQ - sizeP;
        while (indexQ != difference)
        {
            R.push_back(Q[indexQ++]);
        }
    }

    RationalNumber elementR;
    while (indexP != sizeP && indexQ != sizeQ)
    {
        elementR = ReturnSumOfRationalNums(P[indexP], Q[indexQ]);
        R.push_back(elementR);

        indexP++;
        indexQ++;
    }

    return R;
}

vector<RationalNumber> returnSubtractionOfPolynomials(vector<RationalNumber> P, vector<RationalNumber> Q)
{
    //We will use the following rule : a + b = a + (-b) and since we already have the function for sum of two polynomials we just need to multiply the second polynomial by -1
   //So we will first write the function for multiplying polynomial by scalar
    RationalNumber coefficient = { -1,1 }; // this is exactly the number -1 
    Q = returnMultipliedPolynomialByScalar(Q, coefficient);

    //R will be the result of the subtraction
    vector<RationalNumber> R = returnSumOfPolynomials(P, Q);

    return R;
}

vector<RationalNumber> returnMultipliedPolynomialByScalar(vector<RationalNumber> P, RationalNumber scalar)
{
    int size = P.size();
    int gcd = 0; 

    for (int i = 0;i < size;i++)
    {
        P[i] = ReturnMultiplicationRationalNums(P[i], scalar);
    }

    return P;
}

vector<RationalNumber> returnMultiplicationOfPolynomials(vector<RationalNumber> P, vector<RationalNumber> Q)
{
    //Multiplication of two polynomials P(x) and Q(x).
    //Let's assume P(x) is 5x^3 + 3x^2 + 1 and Q(x) is x^2 + 3
    // Then P(x) * Q(x) = P(x) * x^2 + P(x) * 3 which is sum of polynomials multiplied by scalar and and x of some degree.

    //Resulting polynomial
    vector<RationalNumber> R;
    
    int sizeQ = Q.size();
    vector<RationalNumber> multipliedPolynomial;
    int degree = sizeQ - 1;

    for (int i = 0;i < sizeQ;i++)
    {
        //First we calculate the new coefficients
        multipliedPolynomial = returnMultipliedPolynomialByScalar(P, Q[i]);

        //Now we adjust the degree
        multipliedPolynomial = addDegree(multipliedPolynomial, degree);

        if (i == 0)
        {
            R = multipliedPolynomial;
        }
        else {
            R = returnSumOfPolynomials(R, multipliedPolynomial);
        }
        degree--;
    }


 
    return R;
}

vector<RationalNumber> returnDivisionOfPolynomials(vector<RationalNumber> & P, vector<RationalNumber> Q)
{
    // the division of two polynomials can be solved using subtraction of two polynomials and multiplication of polynomial by a number
    // example : P(x) = 5x^5 - 4x^4 + 3x^3 + x^2 + x + 1
    // Q(x) = x^3 - 5
    //we need to find a coefficient, which will remove the element of highest degree in P(x). We do this until the highest degree in P(x) < highest degree in Q(x)
    
    vector<RationalNumber> Quotient;


    int degreeDifference = P.size() - Q.size();

    int indexP = 0; 
    int indexQ = 0;


    RationalNumber coefficient;
    RationalNumber zero = { 0,1 };
    vector<RationalNumber> tempPolynomial;
    


    while (degreeDifference>=0)
    {
        if (P[indexP].first == 0)
        {
            indexP++; 
            degreeDifference--;
            Quotient.push_back(zero);
            continue;
        }
        //We find the coefficient that Q needs to by multiplied by in order to remove the highest degree of P(x) 
        coefficient = ReturnDivisionOfRationalNums(P[indexP], Q[indexQ]);
        //Now we multiply Q by coefficient and subtract it from P
        tempPolynomial = returnMultipliedPolynomialByScalar(Q, coefficient);
        //Now we increase the degree of the polynomial
        tempPolynomial = addDegree(tempPolynomial, degreeDifference);
        //now we subtract P and the tempPolynomial
        P = returnSubtractionOfPolynomials(P, tempPolynomial);
        //We add the coefficient to the Quotient polynomial
        Quotient.push_back(coefficient);
        degreeDifference--; indexP++;
    }

    //At the end, our P(x) will have become the remainder
    //We resize P
    P = resizePolynomial(P);

    return Quotient;

}

vector<RationalNumber> returnRemainderOfPolynomials(vector<RationalNumber> P, vector<RationalNumber> Q)
{
    // the division of two polynomials can be solved using subtraction of two polynomials and multiplication of polynomial by a number
    // example : P(x) = 5x^5 - 4x^4 + 3x^3 + x^2 + x + 1
    // Q(x) = x^3 - 5
    //we need to find a coefficient, which will remove the element of highest degree in P(x). We do this until the highest degree in P(x) < highest degree in Q(x)

    vector<RationalNumber> Quotient;


    int degreeDifference = P.size() - Q.size();

    int indexP = 0;
    int indexQ = 0;


    RationalNumber coefficient;
    RationalNumber zero = { 0,1 };
    vector<RationalNumber> tempPolynomial;



    while (degreeDifference >= 0)
    {
        if (P[indexP].first == 0)
        {
            indexP++;
            degreeDifference--;
            Quotient.push_back(zero);
            continue;
        }
        //We find the coefficient that Q needs to by multiplied by in order to remove the highest degree of P(x) 
        coefficient = ReturnDivisionOfRationalNums(P[indexP], Q[indexQ]);
        //Now we multiply Q by coefficient and subtract it from P
        tempPolynomial = returnMultipliedPolynomialByScalar(Q, coefficient);
        //Now we increase the degree of the polynomial
        tempPolynomial = addDegree(tempPolynomial, degreeDifference);
        //now we subtract P and the tempPolynomial
        P = returnSubtractionOfPolynomials(P, tempPolynomial);
        //We add the coefficient to the Quotient polynomial
        Quotient.push_back(coefficient);
        degreeDifference--; indexP++;
    }

    //At the end, our P(x) will have become the remainder
    //We resize it and return the remainder

    P = resizePolynomial(P);
    return P;

}

RationalNumber returnValueAtNumber(vector<RationalNumber> P, RationalNumber num)
{
    RationalNumber result = { 0,1 }; // result is 0 at the start

    //we will start iterating from the last element
    int index = P.size() - 1;

    RationalNumber x = { 1,1 }; // at the beginning our x is of degree 0, so its equal to 1 ( {1,1}, as a rational) 
    RationalNumber currentElement; 
    for (int i = index;i >= 0;i--)
    {
        //Each time we enter the for cycle, we will sum the result with the value for x * coefficient before x
        //Example P(x) = 2x^2 + 1/2x.   P(2) = 1/2 * 2 ^ 1 + 2 * 2 ^ 2
        currentElement = ReturnMultiplicationRationalNums(P[i], x);
        
        //We add the current element to the overall result
        result = ReturnSumOfRationalNums(result, currentElement);

        //We multiply x by num, as the next degree will be the current degree + 1
        x = ReturnMultiplicationRationalNums(x, num);
    }

    return result;
}

vector<RationalNumber> returnGcdOfPolynomials(vector<RationalNumber> P, vector<RationalNumber> Q)
{
    //The algorithm consists of four steps
    //Step 1 : Divide P(x) by Q(x)
    //Step 2 : Check if the remainder is Q(x)
    //Step 3 : If the remainder is non-zero, replace P(x) with Q(x) and Q(x) with the remainder
    //Step 4 : Repeat until the remainder becomes zero


    vector<RationalNumber> remainderPolynomial;

    while (true)
    {
        remainderPolynomial = returnRemainderOfPolynomials(P, Q);
        
        if (isZeroPolynomial(remainderPolynomial))
        {
            break;
        }

        P = Q;
        Q = remainderPolynomial;

    }

    return Q;
}

void addPolynomials() {
    cout << "Enter polynomial P(x)" << endl;
    vector<RationalNumber> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter polynomial Q(x)" << endl;
    vector<RationalNumber> Q = readPolynomial();
    cout << "Q(X) = ";
    printPolynomial(Q);


    vector<RationalNumber> R = returnSumOfPolynomials(P, Q);

    
    cout << "P(X) + Q(X) = ";
    printPolynomial(R);
}

void subtractPolynomials() {
    cout << "Enter polynomial P(x)" << endl;
    vector<RationalNumber> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter polynomial Q(x)" << endl;
    vector<RationalNumber> Q = readPolynomial();
    cout << "Q(X) = ";
    printPolynomial(Q);


    vector<RationalNumber> R = returnSubtractionOfPolynomials(P, Q);
    cout << "P(x) - Q(x) = ";
    printPolynomial(R);
   
   
}

void multiplyPolynomials() {
 
   
    cout << "Enter polynomial P(x)" << endl;
    vector<RationalNumber> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter polynomial Q(x)" << endl;
    vector<RationalNumber> Q = readPolynomial();
    cout << "Q(X) = ";
    printPolynomial(Q);


    vector<RationalNumber> R = returnMultiplicationOfPolynomials(P, Q);


    cout << "P(X) * Q(X) = ";
    printPolynomial(R);
}

void dividePolynomials() {
    cout << "Enter polynomial A(x)" << endl;
    vector<RationalNumber> A = readPolynomial();
    cout << "A(X) = ";
    printPolynomial(A);

    cout << "Enter polynomial B(x)" << endl;
    vector<RationalNumber> B = readPolynomial();
    cout << "B(X) = ";
    printPolynomial(B);


    //R will be the result of the division
    vector<RationalNumber> Quotient = returnDivisionOfPolynomials(A, B);
    cout << "Quotient Q(x)=";
    printPolynomial(Quotient);
    cout << "Remainder R(x)=";
    printPolynomial(A);
}

void multiplyPolynomialByScalar() {

    cout << "Enter polynomial P(x)" << endl;
    vector<RationalNumber> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter rational number>> ";
    RationalNumber scalar = readRationalNumber();

    P = returnMultipliedPolynomialByScalar(P, scalar);
    cout << "Result: ";
    printPolynomial(P);

}

void findValueAtNumber() {
    cout << "Enter polynomial P(x)" << endl;
    vector<RationalNumber> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter rational number>> ";
    RationalNumber num = readRationalNumber();

    RationalNumber result = returnValueAtNumber(P, num);
    cout << "P("; 
    printRational(num);
    cout << ") = ";
    printRational(result);
    cout << endl;
}

void findGCDOfTwoPolynomials() {
    cout << "Enter polynomial P(x)" << endl;
    vector<RationalNumber> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter polynomial Q(x)" << endl;
    vector<RationalNumber> Q = readPolynomial();
    cout << "Q(X) = ";
    printPolynomial(Q);


    vector<RationalNumber> R = returnGcdOfPolynomials(P, Q);


    cout << "gcd(P(x), Q(x)) = ";
    printPolynomial(R);
}

void displayVieta() {
    cout << "displayVieta() is not implemented yet.\n";
}

void representInPowers() {
    cout << "representInPowers() is not implemented yet.\n";
}

void factorAndFindRoots() {
    cout << "factorAndFindRoots() is not implemented yet.\n";
} 

