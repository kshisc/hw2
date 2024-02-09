#include <map>
#include <queue>
#include "datastore.h"

class MyDataStore : public DataStore {
	public:
		MyDataStore();
    ~MyDataStore();

   /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void addtoCart(std::string user, int index, std::vector<Product*> hits);
    void viewCart(std::string user);
    void buyCart(std::string user);

    private:
		std::set<Product*> products;
    std::map<std::string,std::set<Product*>> prodMap; //maps keyword to products
		// std::set<User*> users;
    std::map<std::string,User*> userMap;
    std::map<std::string,std::queue<Product*>> cartMap; //maps user to cart
};