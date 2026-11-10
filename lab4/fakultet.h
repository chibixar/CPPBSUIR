/*5. Распрацаваць клас Fakultet, які спараджае клас Student. Клас
Fakultet уключае кампаненты-дадзеныя: найменне факультэта. Клас
Student уключае кампаненты-дадзеныя: Ф.І.Б. студэнта, год нараджэння,
вынікі здачы апошняй сесіі.
*/

#pragma once

#include <string>

class Fakultet
{
private:
    std::string faculty_name;

public:
    Fakultet(const std::string& name);
    virtual ~Fakultet();

    const std::string& get_faculty_name() const;
    void set_faculty_name(const std::string& name);

    virtual void print() const;
    virtual void input() = 0;
};
