#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string name, const std::string size, const std::string brand, double price, int qty):
  Product("clothing",name,price,qty),
  size_(size),
  brand_(brand)
{
}

Clothing::~Clothing(){
}

set<string> Clothing::keywords() const{
  set<string> kws;
  
  set<string> name=parseStringToWords(getName());
  kws.insert(name.begin(),name.end());
  set<string> brand=parseStringToWords(brand_);
  kws.insert(brand.begin(),brand.end());

  return kws;
}

string Clothing::displayString() const{
  string display(name_ + "\n" + "Size: " + size_ + " " + 
  "Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(getQty()) + " left.");

  return display;
}

void Clothing::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << getQty() << "\n" <<
  size_ << "\n" << brand_;
}

