#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore(){
}


MyDataStore::~MyDataStore(){
  for(Product* p: products){
    delete p;
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
  for(string k: keys){
    prodMap[k].insert(p);
  }
}


void MyDataStore::addUser(User* u){
  userMap.insert(make_pair(u->getName(),u));
}


vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  set<Product*> s1;
  set<Product*> s2;

  if(type==0){ //AND search
    for(size_t i=0; i<terms.size(); i++){ //iterate through terms
      map<string,set<Product*>>::iterator prodIt = prodMap.find(terms[i]);
      if(prodIt!=prodMap.end()){ //term in map
        s1=prodIt->second; //get set of products for keyword
        s2=setIntersection(s1,s2);
      }
		}
  }

  else{ //OR search
    for(size_t i=0; i<terms.size(); i++){ //iterate through terms
      map<string,set<Product*>>::iterator prodIt = prodMap.find(terms[i]);
      if(prodIt!=prodMap.end()){ //keyword in map
        s1=prodIt->second; //get set of products for keyword
        s2=setUnion(s1,s2);
      }
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
	if(userMap.find(user)!=userMap.end() && index<int(hits.size())){
		cartMap[user].push_back(hits[index]);
	}
	else{
		cout << "Invalid request" << endl;
	}
}


void MyDataStore::viewCart(string user){
  map<string,vector<Product*>>::iterator cartIt = cartMap.find(user);
  if(cartIt==cartMap.end()){
    cout << "Invalid username" << endl;
  }

  else{
    vector<Product*> cart=cartIt->second;
    size_t i=0;
    while(i<cart.size()){
      cout << "Item " << i+1 << "\n" << cart[i]->displayString() << endl;
      i++;
		}
  }
}


void MyDataStore::buyCart(string user){
  map<string,vector<Product*>>::iterator cartIt = cartMap.find(user);
  if(cartIt==cartMap.end()){
    cout << "Invalid username" << endl;
  }

  else{
    map<string,User*>::iterator userIt = userMap.find(user);
    User* u = userIt->second;

    vector<Product*> &cart=cartIt->second;
    size_t i=0;
    while(i<cart.size()){ //iterate through cart
      Product* p = cart[i];
      if((p->getQty() > 0) && (p->getPrice() < u->getBalance())){ //enough stock and funds
        u->deductAmount(p->getPrice());
        p->subtractQty(1);
      }
      i++;
		}

    set<Product*> cartSet(cart.begin(),cart.end()); //remove duplicates
    cart.assign(cartSet.begin(),cartSet.end());
  }
}