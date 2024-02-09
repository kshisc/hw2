#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore(){
}


MyDataStore::~MyDataStore(){
	set<Product*>::iterator prodIt;
	for(prodIt=products.begin(); prodIt!=products.end(); ++prodIt){
		delete *prodIt;
	}
  
	map<string,User*>::iterator userIt;
	for(userIt=userMap.begin(); userIt!=userMap.end(); ++userIt){
		delete (userIt->second);
	}
}


void MyDataStore::addProduct(Product* p){
	products.insert(p);

  //map keyword -> products
  set<string> keys = p->keywords();
  set<string>::iterator setIt;
  for(setIt=keys.begin(); setIt!=keys.end(); ++setIt){ //iterate through keywords
    map<string,set<Product*>>::iterator mapIt = prodMap.find(*setIt); //search for keyword in map
    if(mapIt==prodMap.end()){ //keyword not in map
      set<Product*> s; //create new set
      s.insert(p);
      prodMap.insert(make_pair(*setIt,s));
    }
    else{
      (mapIt->second).insert(p);
    }
  }
}


void MyDataStore::addUser(User* u){
  userMap.insert(make_pair(u->getName(),u));
}


vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  set<Product*> s1;
  set<Product*> s2;

  if(type==0){ //AND search
    for(size_t i=0; i<terms.size(); i++){ //iterate through vector
      map<string,set<Product*>>::iterator mapIt = prodMap.find(terms[i]); //search for keyword in map
      if(mapIt!=prodMap.end()){ //keyword exists
        s1=mapIt->second;
      }
      s2=setIntersection(s1,s2);
		}
  }

  else{ //OR search
    for(size_t i=0; i<terms.size(); i++){ //iterate through vector
      map<string,set<Product*>>::iterator mapIt = prodMap.find(terms[i]); //search for keyword in map
      if(mapIt!=prodMap.end()){ //keyword exists
        s1=mapIt->second;
      }
      s2=setUnion(s1,s2);
    }
  }

  vector<Product*> v_match(s2.begin(),s2.end());
  return v_match;
}


void MyDataStore::dump(ostream& ofile){
	ofile << "<products>" << endl;
  for(Product* p: products){
    p->dump(ofile);
  }
	ofile << "</products>" << endl;

	ofile << "<users>" << endl;
  map<string,User*>::iterator userIt;
	for(userIt=userMap.begin(); userIt!=userMap.end(); ++userIt){
		(userIt->second)->dump(ofile);
	}
	ofile << "</users>" << endl;
}


void MyDataStore::addtoCart(string user, int index, vector<Product*> hits){
  queue<Product*> cart;

  map<string,User*>::iterator userIt = userMap.find(user);
  if(userIt==userMap.end() || index>int(hits.size())){
    cout << "Invalid request" << endl;
  }

  map<string,queue<Product*>>::iterator cartIt = cartMap.find(user);
  if(cartIt==cartMap.end()){ //no cart yet
    cart.push(hits[index]);
    cartMap.insert(make_pair(user,cart));
  }
  else{
    cart=cartIt->second;
    cart.push(hits[index]);
  }
}


void MyDataStore::viewCart(string user){
  map<string,queue<Product*>>::iterator cartIt = cartMap.find(user);
  if(cartIt==cartMap.end()){
    cout << "Invalid username" << endl;
  }

  else{
    queue<Product*> cart=cartIt->second;
    size_t i=0;
    while(i<cart.size()){
      cout << i << " ";
      cart.front()->displayString();
      cout << endl;
      i++;
		}
  }
}


void MyDataStore::buyCart(string user){
  map<string,queue<Product*>>::iterator cartIt = cartMap.find(user);
  if(cartIt==cartMap.end()){
    cout << "Invalid username" << endl;
  }

  else{
    map<string,User*>::iterator userIt = userMap.find(user);
    User* u = userIt->second;

    queue<Product*> cart=cartIt->second;
    size_t i=0;
    while(i<cart.size()){ //iterate through cart
      Product* p = cart.front();
      if((p->getQty() > 0) && (p->getPrice() < u->getBalance())){
        u->deductAmount(p->getPrice());
        p->subtractQty(1);
      }
      i++;
		}
  }
}

