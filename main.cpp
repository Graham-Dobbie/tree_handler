#include <tree.hpp>

using namespace std;


int main(){

    Tree TreeHandler;

    // TreeHandler.add_child("e2e4", 0.1);

    // TreeHandler.add_child("e2e3", 0.3);

    // TreeHandler.make_move(0);

    // TreeHandler.add_child("e4e5", -0.05);

    // TreeHandler.print();

    // TreeHandler.save_tree();

    ifstream tree_file("weights.trf");

    if(!tree_file.is_open()) {
        cerr << "failed to open file" << endl;
        return 1;
        }

    string to_parse_str;

    tree_file >> to_parse_str;


    TreeHandler.parse_text(to_parse_str);

    TreeHandler.print();



    return 0;
}
