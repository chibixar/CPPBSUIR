#include "mystring.h"
#include <iostream>

int main()
{
    MyString A("BSUIR");                                                    // Пачатковая ініцыялізацыя радкоў.
    MyString B("FKSIS");
    MyString C("KS");
    
    int choice;
    
    do
    {
        std::cout << "\nMENU:\n";
        std::cout << "Current Strings:\n";
        std::cout << "A = " << A << "\n";
        std::cout << "B = " << B << "\n";
        std::cout << "C = " << C << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << "1. Input new strings (A, B, C)\n";
        std::cout << "2. Test Addition (+)\n";
        std::cout << "3. Test Subtraction (-)\n";
        std::cout << "4. Test Compound Assignment (+=)\n";
        std::cout << "5. Test Increment / Decrement (++, --)\n";
        std::cout << "6. Test Comparisons (<, >, <=, >=)\n";
        std::cout << "7. Test Index [] and Substring ()\n";
        std::cout << "8. Test Complex Math Expression\n";
        std::cout << "0. Exit\n";
        std::cout << "Select operation: ";
        
        std::cin >> choice;
        std::cin.ignore(1000, '\n');                                        // Ачыстка буфера пасля лікавага ўводу (абавязкова для getline).

        switch (choice)
        {
            case 1:
                std::cout << "Enter String A: ";
                std::cin >> A;
                std::cout << "Enter String B: ";
                std::cin >> B;
                std::cout << "Enter String C: ";
                std::cin >> C;
                break;
                
            case 2:
                std::cout << "\nA + B = " << A + B << "\n";
                std::cout << "\"Prefix_\" + A = " << "Prefix_" + A << "\n"; // Дэманстрацыя працы friend функцыі (const + obj).
                std::cout << "B + \"_Suffix\" = " << B + "_Suffix" << "\n";
                break;
                
            case 3:
                std::cout << "\nA - B = " << A - B << "\n";                 // Выдаленне падстарокі B з радка A.
                std::cout << "A - C = " << A - C << "\n";
                break;
                
            case 4:
                std::cout << "\nA += B...\n";
                A += B;
                std::cout << "New A = " << A << "\n";
                break;
                
            case 5:
                std::cout << "\nOriginal A = " << A << "\n";
                A++;
                std::cout << "After A++ = " << A << "\n";
                --A;
                std::cout << "After --A = " << A << "\n";
                break;
                
            case 6:
                std::cout << "\nComparing A and B:\n";
                if (A < B) std::cout << "A is LESS than B\n";
                if (A > B) std::cout << "A is GREATER than B\n";
                if (A <= B) std::cout << "A is LESS OR EQUAL to B\n";
                if (A >= B) std::cout << "A is GREATER OR EQUAL to B\n";
                break;
                
            case 7:
            {
                int index, start, len;
                std::cout << "\nEnter index to view A[i]: ";
                std::cin >> index;
                try
                {
                    std::cout << "A[" << index << "] = " << A[index] << "\n";
                }
                catch (const std::exception& e)
                {
                    std::cout << "Exception: " << e.what() << "\n";         // Апрацоўка памылкі выхаду за межы масіва.
                }
                
                std::cout << "Enter start and length for Substring A(start, len): ";
                std::cin >> start >> len;
                std::cout << "A(" << start << ", " << len << ") = " << A(start, len) << "\n";
                break;
            }
                
            case 8:
            {
                std::cout << "\nExecuting: D = \"HELLO_\" + A + B - C\n";
                MyString D;
                D = "HELLO_" + A + B - C;                                   // Ланцужок шматлікіх перагружаных аперацый.
                std::cout << "Result D = " << D << "\n";
                break;
            }
                
            case 0:
                std::cout << "Exiting program...\n";
                break;
                
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
        
    } while (choice != 0);

    return 0;
}