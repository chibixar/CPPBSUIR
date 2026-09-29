#include "matrix.h"
#include <iostream>

int main()
{
    try                                                                     // Блок try-catch для апрацоўкі памылак памераў.
    {
        int r, c;
        
        std::cout << "--- Matrix 1 ---\n";
        std::cout << "Enter rows and cols: ";
        std::cin >> r >> c;
        Matrix m1(r, c);
        std::cout << "Enter elements:\n";
        std::cin >> m1;                                                     // Выкарыстанне перагружанага operator>>.
        
        std::cout << "\n--- Matrix 2 ---\n";
        std::cout << "Enter rows and cols: ";
        std::cin >> r >> c;
        Matrix m2(r, c);
        std::cout << "Enter elements:\n";
        std::cin >> m2;
        
        std::cout << "\n--- Matrix 1 Data ---\n" << m1;                     // Выкарыстанне перагружанага operator<<.
        std::cout << "\n--- Matrix 2 Data ---\n" << m2;
        
        // Дэманстрацыя дадання элементаў праз аператар ()
        std::cout << "\nModifying top-left element of Matrix 1 to 999...\n";
        m1(0, 0) = 999;                                                     // Выкарыстанне перагружанага operator().
        std::cout << "\n--- Modified Matrix 1 ---\n" << m1;

        // Дэманстрацыя арыфметычных аператараў
        std::cout << "\n--- Trying Matrix Addition (m1 + m2) ---\n";
        Matrix sum = m1 + m2;                                               // Выкарыстанне перагружанага operator+.
        std::cout << sum;
        
        std::cout << "\n--- Trying Matrix Multiplication (m1 * m2) ---\n";
        Matrix prod = m1 * m2;                                              // Выкарыстанне перагружанага operator*.
        std::cout << prod;
    }
    catch (const std::exception& e)                                         // Перахоп выключэнняў (напрыклад, няроўныя памеры).
    {
        std::cout << "\nERROR: " << e.what() << "\n";
    }

    return 0;
}