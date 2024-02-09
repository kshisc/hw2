#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string name, const std::string genre, const std::string rating, double price, int qty):
  Product("movie",name,price,qty),
  genre_(genre),
  rating_(rating)
{
}

Movie::~Movie(){
}

set<string> Movie::keywords() const{
  set<string> kws;
  
  set<string> name=parseStringToWords(getName());
  kws.insert(name.begin(),name.end());
  set<string> genre=parseStringToWords(genre_);
  kws.insert(genre.begin(),genre.end());

  return kws;
}

string Movie::displayString() const{
  string display(name_ + "\n" + "Genre: " + genre_ + " " + 
  "Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(getQty()) + " left.");

  return display;
}


void Movie::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << getQty() << "\n" <<
  genre_ << "\n" << rating_;
}