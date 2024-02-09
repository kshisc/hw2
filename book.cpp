#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string name, const std::string author, const std::string isbn, double price, int qty):
  Product("book",name,price,qty),
  author_(author),
  isbn_(isbn)
{
}

Book::~Book(){
}

set<string> Book::keywords() const{
  set<string> kws;
  
  set<string> name=parseStringToWords(getName());
  kws.insert(name.begin(),name.end());
  set<string> author=parseStringToWords(author_);
  kws.insert(author.begin(),author.end());
  set<string> isbn=parseStringToWords(isbn_);
  kws.insert(isbn.begin(),isbn.end());

  return kws;
}

string Book::displayString() const{
  string display(name_ + "\n" + "Author: " + author_ + " " + 
  "ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(getQty()) + " left.");

  return display;
}

void Book::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << getQty() << "\n" <<
  isbn_ << "\n" << author_;
}
