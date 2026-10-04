#include "matrix.h"
#include <iostream>

int main()
{
    char choice;

    do
    {
        int r1, c1, r2, c2;

        std::cout << "Enter rows and cols for Matrix 1: ";
        std::cin >> r1 >> c1;

        std::cout << "Enter rows and cols for Matrix 2: ";
        std::cin >> r2 >> c2;

        if (c1 != r2)                                           // Множанне магчыма, толькі калі c1 == r2.
        {
            std::cout << "Error: Matrices cannot be multiplied.\n";
        }
        else
        {
            Matrix m1(r1, c1);
            Matrix m2(r2, c2);

            std::cout << "Enter elements for Matrix 1:\n";
            m1.input();

            std::cout << "Enter elements for Matrix 2:\n";
            m2.input();

            std::cout << "\nFirst Matrix:\n";
            m1.print();

            std::cout << "\nSecond Matrix:\n";
            m2.print();

            Matrix copy(m1);                                    // Праверка канструктара капіявання.
            Matrix result(r1, c2);                              // Памер выніку: r1 x c2.
            copy.multiply(m2, result);

            std::cout << "\nMultiplication Result:\n";
            result.print();
        }

        std::cout << "\nContinue? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
