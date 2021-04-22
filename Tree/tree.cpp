#include "tree.hpp"


// Helper Functions

std::pair<std::string, float> _make_data(std::string alg_move_p, float q_value_p) {  //creates the data pair of a node containing a q_value and a (temporary) aglibric move
        std::pair<std::string, float> data(alg_move_p, q_value_p);
        return data;
    }

//Node Definition

Node::Node(): children(), parent_node(nullptr), data(_make_data("", 0)) {};
Node::Node (Node* parent_node_p, std::pair<std::string, float> data_p): children(), parent_node(parent_node_p), data(data_p) {};

Node::~Node(){
    // std::cout << "Node: " << this->data.first << " Was Destroyed" << std::endl;
}


// Tree Definition

Tree::Tree(): root_node_ptr(new Node( nullptr, _make_data("", 0.0))), head_node_ptr(root_node_ptr), tree_file_path("weights.trf") {
    std::ifstream tree_file;
    tree_file.open(tree_file_path);
    if(tree_file.is_open()){
        std::cout << "Tree File Exists" << std::endl;
    }
    tree_file.close();
}


int Tree::_add_node(std::string alg_move_p, float q_value_p, Node* parent_node_ptr_p) { //adds new node to heap
    Node* h_node  = new Node(parent_node_ptr_p, _make_data(alg_move_p, q_value_p));
    int size = parent_node_ptr_p->children.size();
    parent_node_ptr_p->children.push_back(h_node);
    return size;
}

std::pair<std::string, float> Tree::_parse_helper (std::string str_p){
    std::string move;
    std::string value_str;
    
    int where_start;
    int where_mid;
    int where_end;

    int i = 0;
    for(size_t i = 0; i < str_p.size(); i++) {
        char c = str_p[i];
        
        if (c == '['){
            where_start = i;
        }

        else if (c == ','){
            where_mid = i;
        }

        else if (c == ']'){
            where_end = i;
        }
    }
    std::string::size_type sz;

    move = _get_str_segment(str_p, where_start + 1, where_mid);
    value_str = _get_str_segment(str_p, where_mid + 1, where_end - 1);

    float value = stof(value_str);

    std::pair<std::string, float> data(move, value);

    return data;
}

std::string Tree::_get_str_segment(std::string string_p, int start_p, int end_p){

    int start, end;

    if (start_p < 0){start = 0;}
    else{start = start_p;}

    if (end_p < 0){end = string_p.size();}
    else{end = end_p;}

    std::string final_str(string_p.begin()+start, string_p.begin()+end);

    return final_str;
}

void Tree::make_move(int move_loc_p){ //Make child node the root node
    Node* node_ptr = head_node_ptr->children[move_loc_p];
    // std::cout << node_ptr->parent_node->data.first << std::endl;
    this->head_node_ptr = node_ptr;
}


void Tree::unmake_move(){ //Make parent of the root node the root node
    Node* node_ptr = head_node_ptr->parent_node;
    // std::cout << node_ptr->data.first << std::endl;
    this->head_node_ptr = node_ptr;
    
}

int Tree::add_child(std::string alg_move_p, float q_value_p){
    int size = _add_node(alg_move_p, q_value_p, this->head_node_ptr);
    return size;
}

std::string Tree::format_node(Node* node_ptr_p){   // Recursive string formating

    
    auto format = [](auto data){return std::string("[") + std::string(data.first) + std::string(",") + std::to_string(data.second)+ std::string("]");};

    if (node_ptr_p->children.size() == 0){ //If the node in at the end it returns only it data
        return format(node_ptr_p->data);
    }

    else { //Else it returns the node data including the children
        std::string node_str = format(node_ptr_p->data);
        std::string children_str = ":(";

        for (std::vector<Node*>::iterator it = node_ptr_p->children.begin() ; it != node_ptr_p->children.end(); ++it){
            children_str += format_node(*it);
        }

        children_str += std::string(")");

        return node_str + children_str;

    }
}

void Tree::print(Node*  node_ptr){
    if (node_ptr != NULL){
        std::cout << format_node(node_ptr) << std::endl;
    }
    else{
        std::cout << format_node(this->root_node_ptr) << std::endl;
    }
}

void Tree::save_tree(){
    std::string payload = format_node(this->root_node_ptr);
    std::ofstream tree_file;
    tree_file.open(this->tree_file_path);
    tree_file << payload;
    tree_file.close();
}


void Tree::parse_text(std::string data_p){

    //Get data of the node
    std::string to_parse_str = data_p;

    // std::cout<< "curent string: " << to_parse_str << std::endl;

    int start = -1;
    int end = -1;

    int size = to_parse_str.size();
    int i = 0;

    do {
        char c = to_parse_str[i];
        if (c == (char)'['){start = i;}

        if (c == (char)']'){end = i;}

        if (start >= 0 and end >= 0 and end >= start){break;}

        ++i;
        } while(i < size);
    
    std::string parsed_text(_get_str_segment(to_parse_str, start, end+1));   
    std::pair<std::string, float> data = _parse_helper(parsed_text); //Final Data
    
    int place = 0;

    //Make Node
    this->print();
    if (data.first != ""){
        int place = this->add_child(data.first, data.second);
    }
    
    
    //Test for Children
    
    if (end != size-1){
        
        int end_of_children = end+3;

        if (to_parse_str.at(end+1) == (char)':'){
            // std::cout << "this node has child" << std::endl;

            int depth = 1;


            do{
                char c = to_parse_str[end_of_children];

                if (c == (char)'('){
                    depth ++;
                }

                if (c == (char)')'){
                    depth += -1;
                }

                end_of_children++;
            }while (depth != 0);

            std::string parsed_text(_get_str_segment(to_parse_str, end+3, end_of_children-1));
            // std::cout <<parsed_text<< std::endl;
            //Add Children
            this->make_move(place);
            parse_text(parsed_text);
            this->unmake_move();
        }
    
    
    // Test for siblings
    
        if (to_parse_str.at(end_of_children) == (char)'[') {
            // std::cout << "this node has silblings" << std::endl;
            std::string parsed_text(_get_str_segment(to_parse_str, end_of_children, -1 ));
            // std::cout <<parsed_text<< std::endl;

            //Make Siblings
            parse_text(parsed_text);

        }

        if (to_parse_str.at(end+1) == (char)'['){
            // std::cout << "this node has silblings" << std::endl;
            std::string parsed_text(_get_str_segment(to_parse_str, end+1, -1 ));
            // std::cout <<parsed_text<< std::endl;

            //Make Siblings
            parse_text(parsed_text);
        }
    }
}



void Tree::load_tree(std::string file_source){
    std::ifstream tree_file("weights.trf");

    std::string to_parse_str;

    tree_file >> to_parse_str;
    int start = -1;
    int end = -1;

    int size = to_parse_str.size();
    int i = 0;

    do {
        char c = to_parse_str[i];
        if (c == (char)'['){start = i;}

        if (c == (char)']'){end = i;}

        if (start >= 0 and end >= 0 and end >= start){break;}

        ++i;
        } while(i < size);
    
    std::string parsed_text(_get_str_segment(to_parse_str, start, end+1));   
    std::pair<std::string, float> data = _parse_helper(parsed_text); //start

    if (data.first == ""){
        int end_root = end + 2;
        int depth = 1;
        do{
               char c = to_parse_str[end_root];
               if (c == (char)'('){
                   depth ++;
               }

               if (c == (char)')'){
                   depth += -1;
               }

               end_root++;

           }while (depth != 0);

        std::string string_data = _get_str_segment(to_parse_str,end, end_root);
        parse_text(string_data);
    }

    else{
        parse_text(to_parse_str);
    }
}



