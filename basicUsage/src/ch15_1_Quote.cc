#include "ch15_1_Quote.h"

double print_total(std::ostream& os, const Quote& quote, size_t num) {
    double ret = quote.net_price(num);
    os << "isbn is " << quote.get_isbn() << std::endl;
    os << "sold is " << num << " total price is " << ret << std::endl;
    return ret;
}

double BulkQuote::net_price(size_t num) const {
    if (num >= min_qty_) {
        return num * (1 - discount_) * price_;
    } else {
        return num * price_;
    }
}