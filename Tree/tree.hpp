
#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

namespace tree {

std::pair<std::string, float> _make_data(std::string alg_move, float q_value);

struct Node {
    
    public:
    std::vector<Node*> children;
    Node* parent_node;
    std::pair< std::string, float> data;


    Node();
    Node (Node* parent_node_p, std::pair< std::string, float> data_p);

    ~Node();
};

class Tree{

    private:
    Node* root_node_ptr;
    Node* head_node_ptr;
    std::string tree_file_path;
    int _add_node(std::string alg_move_p, float q_value_p, Node* parent_node_ptr_p);

    std::string _get_str_segment(std::string string, int start, int end = -1);

    std::pair<std::string, float> _parse_helper (std::string str_p);

    public:
    

    Tree();

    // tree maker functions

    void make_move(int move_loc_p); //moves the header node to child node

    void unmake_move(); // moves the header node back to parent node

    int add_child (std::string alg_move_p, float q_value_p); //add child node under current the header node 

    // iofile opperations

    std::string __format_node(Node* node_p); // create a string to save

    void print(Node* node_ptr = NULL); // prints the tree

    void save_tree(); // saves tree to dst file

    void parse_text(std::string data); // parses text to load

    void load_tree(std::string file_source = "weights.trf"); // loads tree from dst file

    // read and write opperations

    std::pair<std::string, float> get_head_data(); // returns data of the header node

    std::vector<std::pair< std::string, float>> get_children_data(); // returns data of the header's children

    void multiply_node(float x); // multiplies q_value inside the header node by a float 

    void add_node(float x); // adds q_value inside the header node by a float

    //memory opporations

    void rm_node(); // calls recursive removal of a node and its children

    
};
}

#endif