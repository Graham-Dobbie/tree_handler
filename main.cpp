#include "tree.hpp"

using namespace std;


int main(){

    tree::Tree TreeHandler;

    TreeHandler.add_child("e2e4", 0.1);

    TreeHandler.add_child("e2e3", 0.3);

    TreeHandler.make_move(0);

    TreeHandler.add_child("e4e5", -0.05);

    TreeHandler.save_tree();

    TreeHandler.print();
    
    return 0;
}
