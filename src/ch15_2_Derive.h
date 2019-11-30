#ifndef CH15_2_DERIVE_H_
#define CH15_2_DERIVE_H_

#include <iostream>

class Base {
   public:
    void PublicMem(void) const { std::cout << "this is base public mem" << std::endl; }

   protected:
    void ProtectedMem(void) const { std::cout << "this is base protected mem" << std::endl; }

   private:
    void PrivateMem(void) const { std::cout << "this is base privete mem" << std::endl; }
};

class DerivedPublicFromBase : public Base {
   public:
    // error, 派生类的成员函数或友元只能通过派生类对象访问基类的受保护成员
    // void UseMem(const Base& base) { base.ProtectedMem(); }
    void UseMem(const DerivedPublicFromBase& derived) { derived.ProtectedMem(); }

    void UseMem(const Base& base) { base.PublicMem(); }
};

class DerivedProtectedFromBase : protected Base {
   public:
    void UseMem(const DerivedProtectedFromBase& derived) { derived.ProtectedMem(); }
};

class DerivedPublicFromDerived : public DerivedPublicFromBase{
    
};

#endif  // CH15_2_DERIVE_H_