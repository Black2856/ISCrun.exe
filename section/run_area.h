#ifndef RUN_AREA_H
#include "settings.h"
#include "stdint.h"
#include "section.h"

class Section99 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const uint16_t section = 99;
};

class Section00 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const uint16_t section = 0;
};

class Section01 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const uint16_t section = 1;
};

class Section02 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const uint16_t section = 2;
};

class Section03 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const uint16_t section = 3;
};

class Section04 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const uint16_t section = 4;
};

#define RUN_AREA_H
#endif