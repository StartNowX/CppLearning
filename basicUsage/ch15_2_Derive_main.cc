#include <iostream>

#include "ch15_2_Derive.h"


int main(int argc, char* argv[]) {
    Base base;
    DerivedPublicFromBase derive_public;
    DerivedProtectedFromBase derive_protected;

    base.PublicMem();
    derive_public.PublicMem();
    // derive_public.ProtectedMem();  // error, inaccessible

    // derive_protected.PublicMem(); // error, inaccessible

    // convert derived class to base
    DerivedPublicFromDerived derive_from_public;
    Base *p = &derive_public;
    // p = &derive_protected; // error
    p = &derive_from_public; // only public derived 

    return 0;
}