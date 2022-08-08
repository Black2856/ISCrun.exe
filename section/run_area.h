#ifndef RUN_AREA_H
#include "settings.h"
#include "stdint.h"
#include "section.h"
#include "sectionList.h"

class Section99 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section99;
};

class Section00 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section00;
};

class Section01 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section01;
};

class Section02 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section02;
};

class Section03 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section03;
};

class Section04 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section04;
};

class Section05 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section05;
};

class Section06 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section06;
};

class Section07 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section07;
};

class Section08 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section08;
};

class Section20 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section20;
};

class Section21 : public Section{
public:
    void main() override;
    void entry() override;
    void condition() override;
private:
    static const SectionList section = SectionList::Section21;
};

#define RUN_AREA_H
#endif