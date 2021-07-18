#include <iostream>
#include <math.h>
#include <fstream>
#include <chrono>
#include <thread>

#define INT_MAX 2147483647

int main()
{
    std::ofstream out;
    remove("primeri.txt");
    out.open("primeri.txt");

    double rezultat = 0.0;
    double i = 0, j = 0, k = 0, n = 0, pom = 1, a = 1, b = 1, c = 1, inc = 1, br = 0, o = 1, d = 1, f = 1, g = 1, h = 1;
    int m = 0;
    std::cout << "Unesite vrednost n=? i m=?" << std::endl;
    std::cin >> m >> n;

    switch (m)
    {
    case 1:
        std::cout << "Molimo vas unesite vrednost vecu od 1" << std::endl;
        break;

    case 2:
        for (i = 1; i <= n; i++)
        {
            for (j = inc; j <= n; j++)
            {
                rezultat = sqrt(i * i + j * j);
                if (rezultat - (int)rezultat == 0)
                {
                    std::cout << i << ", " << j << " = " << (int)rezultat << std::endl;
                    out << i << " " << j << " " << rezultat << std::endl;
                }
            }
            inc++;
            br++;
        }
        break;

    case 3:
        for (i = 1; i <= n; i++)
        {
            a = b = i;
            for (j = a; j <= n; j++)
            {
                for (k = b; k <= n; k++)
                {
                    rezultat = cbrt(i * i * i + j * j * j + k * k * k);
                    if (rezultat - (int)rezultat == 0)
                    {
                        std::cout << i << "^3 + " << j << "^3 + " << k << "^3 "
                                  << " = " << (int)rezultat << std::endl;
                        out << i << " " << j << " " << k << " " << std::endl;
                    }
                }
                b++;
            }
            a++;
        }
        break;

    case 4:
        for (i = 1; i <= n; i++)
        {
            a = b = c = i;
            for (j = a; j <= n; j++)
            {
                b = c = j;
                for (k = b; k <= n; k++)
                {
                    c = k;
                    for (o = c; o <= n; o++)
                    {
                        rezultat = pow(i * i * i * i + j * j * j * j + k * k * k * k + o * o * o * o, 0.25);
                        if (rezultat - (int)rezultat == 0)
                        {
                            std::cout << i << "^4 + " << j << "^4 + " << k << "^4 + " << o << "^4 = " << rezultat << std::endl;
                            out << i << " " << j << " " << k << " " << o << std::endl;
                        }
                    }
                    c++;
                }
                b++;
            }
            a++;
        }
        break;

    case 5:
        for (i = 1; i <= n; i++)
        {
            a = b = c = f = i;
            for (j = a; j <= n; j++)
            {
                b = c = f = j;
                for (k = b; k <= n; k++)
                {
                    c = f = k;
                    for (o = c; o <= n; o++)
                    {
                        f = o;
                        for (d = f; d <= n; d++)
                        {
                            rezultat = pow(i * i * i * i * i + j * j * j * j * j + k * k * k * k * k + o * o * o * o * o + d * d * d * d * d, 0.2);
                            if (rezultat - (int)rezultat == 0)
                            {
                                std::cout << i << "^5 + " << j << "^5 + " << k << "^5 + " << o << "^5 + " << d << "^5"
                                          << " = " << rezultat << std::endl;
                                out << i << " " << j << " " << k << " " << o << " " << d << std::endl;
                            }
                        }
                        d++;
                    }
                    c++;
                }
                b++;
            }
            a++;
        }
        break;

    case 6:
        for (i = 1; i <= n; i++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            a = b = c = f = h = i;
            for (j = a; j <= n; j++)
            {
                b = c = f = h = j;
                for (k = b; k <= n; k++)
                {
                    c = f = h = k;
                    for (o = c; o <= n; o++)
                    {
                        f = h = o;
                        for (d = f; d <= n; d++)
                        {
                            h = d;
                            for (g = h; g <= n; g++)
                            {
                                // rezultat = pow(i * i * i * i * i * i + j * j * j * j * j * j + k * k * k * k * k * k + o * o * o * o * o * o + d * d * d * d * d * d + g * g * g * g * g * g, 6);
                                // if (rezultat - (int)rezultat == 0)
                                // {
                                //     std::cout << i << "^6 + " << j << "^6 + " << k << "^6 + " << o << "^6 + " << d << "^6 + " << g << "^6 "
                                //               << " = " << rezultat << std::endl;
                                //     out << i << " " << j << " " << k << " " << o << " " << d << " " << g << std::endl;
                                // }
                                if (i == j && j == k && k ==o && o == d && d==g)
                                    continue;
                                else
                                    out << "{" << i << "," << j << "," << k << "," << o << "," << d << "," << g << "}," << std::endl;
                            }
                            g++;
                        }
                        d++;
                    }
                    c++;
                }
                b++;
            }
            a++;
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "Odradjena je " << i << "-ta iteracija za " << duration.count() << " milisekundi" << std::endl;
        }
        break;

    case 7:
    {
        auto start = std::chrono::high_resolution_clock::now();
        a = 5376767751082385640407296.0;
        b = pow(a, 1.0 / 8.0);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Pow Root je odradjen za " << duration.count() << " milisekundi" << std::endl;
        std::cout << b << std::endl;
    }
    break;

    default:
        std::cout << "Unesite drugu vrednost za n!" << std::endl;
        break;
    }
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // std::cout << duration.count() << std::endl;
    getchar();
    out.close();
    return 0;
}

int makeEqualLength(std::string &str1, std::string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0; i < len2 - len1; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0; i < len1 - len2; i++)
            str2 = '0' + str2;
    }
    return len1;
}

std::string addBitStrings(std::string first, std::string second)
{
    std::string result;

    int length = makeEqualLength(first, second);
    int carry = 0;

    // Add all bits one by one
    for (int i = length - 1; i >= 0; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';

        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry) + '0';

        result = (char)sum + result;

        // boolean expression for 3-bit addition
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }

    // if overflow, then add a leading 1
    if (carry)
        result = '1' + result;

    return result;
}

// A utility function to multiply single bits of strings a and b
int multiplyiSingleBit(std::string a, std::string b)
{
    return (a[0] - '0') * (b[0] - '0');
}

// The main function that multiplies two bit strings X and Y and returns
// result as long integer
long int multiply(std::string X, std::string Y)
{
    // Find the maximum of lengths of x and Y and make length
    // of smaller string same as that of larger string
    int n = makeEqualLength(X, Y);

    // Base cases
    if (n == 0)
        return 0;
    if (n == 1)
        return multiplyiSingleBit(X, Y);

    int fh = n / 2;    // First half of string, floor(n/2)
    int sh = (n - fh); // Second half of string, ceil(n/2)

    // Find the first half and second half of first string.
    // Refer http://goo.gl/lLmgn for substr method
    std::string Xl = X.substr(0, fh);
    std::string Xr = X.substr(fh, sh);

    // Find the first half and second half of second std::string
    std::string Yl = Y.substr(0, fh);
    std::string Yr = Y.substr(fh, sh);

    // Recursively calculate the three products of inputs of size n/2
    long int P1 = multiply(Xl, Yl);
    long int P2 = multiply(Xr, Yr);
    long int P3 = multiply(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr));

    // Combine the three products to get the final result.
    return P1 * (1 << (2 * sh)) + (P3 - P1 - P2) * (1 << sh) + P2;
}