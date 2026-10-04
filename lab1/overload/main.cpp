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
            std::cin >> m1;                                     // Выкарыстанне перагружанага operator>>.

            std::cout << "Enter elements for Matrix 2:\n";
            std::cin >> m2;

            std::cout << "\nFirst Matrix:\n";
            std::cout << m1;                                    // Выкарыстанне перагружанага operator<<.

            std::cout << "\nSecond Matrix:\n";
            std::cout << m2;

            //m1(0, 0) = 999;                                     // Доступ да элемента праз перагружаны operator().
            //std::cout << "\nFirst Matrix after m1(0, 0) = 999:\n";
            //std::cout << m1;

            Matrix copy(m1);                                    // Праверка канструктара капіявання.
            Matrix result = copy * m2;                          // Перагружаная аперацыя множання.

            std::cout << "\nMultiplication Result:\n";
            std::cout << result;
        }

        std::cout << "\nContinue? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
