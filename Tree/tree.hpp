#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

std::pair<std::string, float> _make_data(std::string alg_move, float q_value);

struct Node {
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
    
    void make_move(int move_loc_p);

    void unmake_move();

    int add_child (std::string alg_move_p, float q_value_p);

    std::string format_node(Node* node_p);

    void print(Node*  node_ptr = NULL);

    void save_tree();

    void save_tree_from_node(Node* node_ptr);

    void parse_text(std::string data);

    void load_tree(std::string file_source = "weights.trf");
};

#endif

