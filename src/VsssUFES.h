#ifndef _VSSSUFES_H_
#define _VSSSUFES_H_

#include <string>
#include <algorithm>

#if defined(DLL_EXPORT)
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC
#endif


class DECLSPEC VsssUFES {
public:
    VsssUFES(std::string name_) : name(name_) {};
    VsssUFES() : name("World") {};
    void greet();
    int getNameLength();
private:
    std::string name;
};

#endif