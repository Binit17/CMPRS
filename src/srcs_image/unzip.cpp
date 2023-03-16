#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cmath>
#include <cassert>
#include <fstream>
#include <cstdint>

//FILE DECOMPRESS PART
struct Tree_Node
{
    Tree_Node* left=nullptr;
    Tree_Node* right=nullptr;
    char symbol;
};
struct encoding_scheme
{
    char symbol;
    std::string encoding_bits;
};
class Decompress
{
    private:
        std::string file_content;
        Tree_Node* root_node;
        size_t number_of_bits;
        uint8_t number_of_unique_symbols;
        std::string compressed_string;
        std::vector<encoding_scheme> map_of_symbols;
        std::string decoded_string;

    private:
        std::size_t d_size;
        std::size_t traverse_in;
    public:
    Decompress(): map_of_symbols(256){}
    void read_compressed_file(std::string file_name)
    {
        // std::string file_content;
        std::ifstream input_file{file_name, std::ios::binary};
        if (input_file.is_open())
        {
            input_file.seekg(0, std::ios::end);
            size_t length_of_file = input_file.tellg();
            input_file.seekg(0, std::ios::beg);
            file_content.resize(length_of_file);
            input_file.read(&file_content[0], length_of_file);
            input_file.close();
        }
        else
        {
            std::cout<<"FILE NOT FOUND";
            std::exit;
        }
    }
    
    void decode_file_structure()
    {
        size_t traverse_index=0;
        number_of_bits = *reinterpret_cast<size_t*>(file_content.substr(0,sizeof(size_t)).data());
        traverse_index = sizeof(size_t);

        number_of_unique_symbols = static_cast<uint8_t>(file_content.at(traverse_index++));

        //Read symbol and their encoding
    
        for(int i=0;  i< static_cast<int>(number_of_unique_symbols)+1 ; i++)
        {
            map_of_symbols.at(i).symbol = file_content.at(traverse_index++);
            uint8_t length_of_bits = file_content.at(traverse_index++);
            size_t length_of_byte = ceil((float)length_of_bits/8.0);
            std::string encoded_text = file_content.substr(traverse_index,length_of_byte);
            traverse_index += length_of_byte;
            convert_bits_to_bytes(encoded_text, map_of_symbols.at(i).encoding_bits, length_of_bits, length_of_byte);
            // std::cout << length_of_byte;
        }
        map_of_symbols.resize(static_cast<size_t>(number_of_unique_symbols)+1);
        create_tree();
        // read encoded stuff to byte representation for each bit and store in comprressed string
        size_t length_of_byte = ceil((float)number_of_bits/8.0);
        std::string encoded_text = file_content.substr(traverse_index,length_of_byte);
        
        // give back space taken by file_content string
        file_content.clear();

        efficient_decode(encoded_text);
        //convert_bits_to_bytes(encoded_text,  compressed_string, number_of_bits, length_of_byte);
    }

    void efficient_decode(std::string_view encoded_text)
    {
        //this is for keeping track of how many bits have been decoded
        constexpr std::uint8_t mask7{1 << 7}; //1000 0000
        Tree_Node* traverse_ptr = root_node;

        size_t length_of_byte = ceil((float)number_of_bits/8.0);
        
        for(size_t i =0; i < length_of_byte; i++)
        {
            uint8_t temp = encoded_text[i];
            for(int j=0;  j< 8; j++)
            {
                if(!traverse_ptr->left && !traverse_ptr->right)
                {
                    decoded_string += traverse_ptr->symbol;
                    traverse_ptr = root_node;
                }
                if(i*8 + j == number_of_bits)
                {
                    break;
                }


                if( temp & mask7)
                {
                    traverse_ptr= traverse_ptr->right;
                }
                else
                {
                    traverse_ptr= traverse_ptr->left;
                    
                }
                temp <<= 1;
            }
        }
    }
    void convert_bits_to_bytes(std::string_view encoded_text, std::string& encoded_text_in_byte, size_t length_of_bits, size_t length_of_byte)
    {
        constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000

        for(size_t i = 0 ; i < length_of_byte ; i++)
        {
            uint8_t temp = encoded_text[i];
            for(int j=0;  j< 8; j++)
            {
                if(i*8 + j == length_of_bits)
                {
                    break;//after break i increase becomes equal to length_oof_byte and this operation ceases
                }
                if( temp & mask7)
                {
                    encoded_text_in_byte += '1';
                }
                else
                {
                    encoded_text_in_byte += '0';
                }
                temp <<= 1;
                
            }
        }
    }
    

    void create_tree()
    {
        root_node = new Tree_Node;
        for(auto i : map_of_symbols)
        {
            insert_node(root_node, i.encoding_bits,0, i.symbol);
        }
    }
    void insert_node(Tree_Node* node, std::string_view path, size_t index, char sym)
    {
        if(index == path.size())
        {
            node->symbol = sym;
            return;
        }
        if(path.at(index) == '0')
        {
            if(node->left == nullptr) node->left = new Tree_Node;
            insert_node(node->left, path, index + 1, sym);
        }
        else
        {
            if(node->right == nullptr) node->right = new Tree_Node;
            insert_node(node->right, path, index + 1, sym);
        }
    }
    
    
    void save_unzipped_file(std::string file_name)
    {
        std::ofstream output_file(file_name, std::ios::binary);
        if(output_file.is_open())
        {
            output_file.write(decoded_string.c_str(),decoded_string.size());
            output_file.close();
        }
    }
    void display()
    {
        for(auto i: map_of_symbols)
        {
            std::cout << "\n" << i.symbol << "==" << i.encoding_bits<<"\n";
        }
        std::cout << compressed_string;
    }
};

int main(int argc , char* argv[])
{
    if(argc != 2)
    {
        std::cout <<"\n Please provide file to compress\n";
        return -2;
    }
    std::string file_name{argv[1]};
    // std::string file_name{"hello.txt"};
    
    Decompress decom;

    decom.read_compressed_file(file_name);
    decom.decode_file_structure();
    decom.create_tree();
    decom.save_unzipped_file(file_name);
    // decom.display();
    return 0;
}