#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>


//wrapper class for huffman tree and operations
class huffman {

    //keep track of node data
    struct node {

        char data;

        int freq;

        node* left;
        node* right;
        node(char data, size_t freq) : data(data),
            freq(freq),
            left(NULL),
            right(NULL) {
            }~node() {
        }
    };

    struct compare {
        bool operator()(node* l, node* r) {
            return (l->freq > r->freq);
        }
    };

    node* top;

    //utility function to dump the huffman code table
    void code_to_file(node* root, std::string str) {
        std::ofstream redirect_file;
        redirect_file.open("codetable.txt", std::ofstream::out | std::ofstream::app);

        if (root == NULL)
            return;

        if (root->data == '$') {
            code_to_file(root->left, str + "0");
            code_to_file(root->right, str + "1");
        }

        if (root->data != '$') {
            redirect_file << root->data << " : " << str << "\n";
            code_to_file(root->left, str + "0");
            code_to_file(root->right, str + "1");
        }
    }

public:
    
    //main huffman algo
    //build huffman tree using minheap
    void huffman_tree(std::vector <char> & data, std::vector<int> & freq, int size) {

        node* left;

        node* right;
        std::priority_queue <node*, std::vector <node*>, compare> min_heap;
        
        for (int i = 0; i < size - 1; i++) {
            min_heap.push(new node(data[i], freq[i]));
        }
        while (min_heap.size() != 1) {
            left = min_heap.top();
            min_heap.pop();

            right = min_heap.top();
            min_heap.pop();

            top = new node('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            min_heap.push(top);
        }

        code_to_file(min_heap.top(), "");
    }

    //utility function to split lines
    std::vector<std::string> split(std::string str, char delimiter) {

       std::vector<std::string> internal;
        std::stringstream ss(str); 
        std::string tok;

        while (std::getline(ss, tok, delimiter)) {
            internal.push_back(tok);
        }

        return internal;
    }

};

int main() {

    huffman h;
    std::vector <char> data;
    std::vector <int> freq;

    std::ifstream file_name("freq.txt");
    std::string line;

    while (std::getline(file_name, line)) {

        std::vector<std::string> temp = h.split(line, ' ');
        int i = std::stoi(temp[1]);
        freq.insert(freq.end(), i );
        data.insert(data.end(), temp[0][0]);
    }

    file_name.close();
    int size = data.size();
    h.huffman_tree(data, freq, size);

    return 0;
}