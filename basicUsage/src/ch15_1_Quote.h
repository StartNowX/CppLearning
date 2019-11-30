#ifndef CH15_1_QUOTE_H_
#define CH15_1_QUOTE_H_

#include <iostream>
#include <string>

class Quote {
   public:
    // if parameter Quote is not reference, derived class will not print right, as there're not type converation between base/derived objects(base class object cannot handle with member in derived class, thus some members in derived class are sliced down)
    friend double print_total(std::ostream& os, const Quote& quote, size_t num);

   public:
    Quote() = default;
    Quote(const std::string& book_no, double price) : book_no_(book_no), price_(price){};
    virtual ~Quote() = default;
    std::string get_isbn() const { return book_no_; }
    virtual double net_price_base(size_t num) const final { return num * price_; }
    virtual double net_price(size_t num) const { return num * price_; }

   private:
    std::string book_no_;

   protected:
    double price_;
};

class BulkQuote : public Quote {
   public:
    BulkQuote() = default;
    BulkQuote(const std::string& book_no, double price, double discount, size_t min_qty)
        : Quote(book_no, price), discount_(discount), min_qty_(min_qty) {}

    // override just used in declaration
    // virtual can be ignored in devived class
    double net_price(size_t n) const override;

   private:
    double discount_;
    size_t min_qty_;
};

// need declare friend function 
double print_total(std::ostream& os, const Quote& quote, size_t num);

#endif