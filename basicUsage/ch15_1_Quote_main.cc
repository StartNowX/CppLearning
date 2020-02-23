#include <iostream>
#include <string>

#include "ch15_1_Quote.h"


int main(int argc, char* argv[]) { 
    Quote quote1("Caption Jack", 128);
    BulkQuote bulk_quote1("Three Days to See", 256.0, 0.5, 5);

    print_total(std::cout, quote1, 3);
    print_total(std::cout, bulk_quote1, 10);

    return 0;
}