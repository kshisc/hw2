#include "product.h"

class Book : public Product {
public:
    Book(const std::string name, const std::string author, const std::string isbn, double price, int qty);
    ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    // bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;

  private:
    std::string author_;
    std::string isbn_;
};
