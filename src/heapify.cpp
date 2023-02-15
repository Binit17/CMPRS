#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cmath>
#include <cassert>

const int MODULO = 255;
struct symbol_id
{
    std::size_t frequency=0;
    char sym;
};

class Symbol_manager
{
    private:
        std::vector<symbol_id> list;
        std::array<symbol_id, 255> initial_list;
        std::size_t list_SIZE;//when item is deleted from heap, this size = no. of elements in the heap
    public:
        Symbol_manager(): list(255){}
        void frequency_counter(std::string_view input_string)
        {
            for(auto i: input_string)
            {
                uint32_t j = (static_cast<uint>(i)%MODULO);
                if(initial_list.at(j).frequency == 0)    initial_list.at(j).sym = i;
                initial_list.at(j).frequency++;
            }
            create_final_list();
        }
        void create_final_list()
        {
            uint32_t j = 0;
            for(auto i: initial_list)
            {
                if(i.frequency != 0) list.at(j++) = i;
            }
            list.resize(j);
            list.shrink_to_fit();
            list_SIZE = list.size();
            heapify(0);
        }
       
        void heapify(size_t index)
        {
            if(index * 2 + 1 >= list_SIZE)
            {
                return;
            }
            heapify(index+1);
            min_heapify(index);
        }
        void min_heapify(size_t index)
        {
            size_t left_index = 2*index +1;
            size_t right_index{};

            if(left_index >= list_SIZE)
            {
                return;
            }
            // assert(index*2+2 < list.size() && "out of bounds of the LIST");
            size_t left_value = list.at(left_index).frequency;
            size_t right_value{};

            size_t minimum_child_index{};
            size_t minimum_child_value{};


            //to cover the condition when there is no right child
            if(left_index+1 >= list_SIZE)
            {
                minimum_child_index = left_index;
                minimum_child_value = left_value;
            }
            else
            {
                right_index = left_index+1;
                right_value = list.at(right_index).frequency;
                minimum_child_value = (left_value < right_value)?left_value:right_value;
                minimum_child_index = (minimum_child_value == left_value)?left_index:right_index;
            }

            if(list.at(index).frequency > minimum_child_value)
            {
                //swap operation- any better way?
                symbol_id temp = list.at(index);
                list.at(index) = list.at(minimum_child_index);
                list.at(minimum_child_index) = temp;
                min_heapify(minimum_child_index);
            }
        }
        void display_heaped()
        {
            std::cout <<std::endl;

            for(auto i : list)
            {
                std::cout << i.frequency <<'\t';
            }
        }
};
int main()
{
    std::string test = "https://chat.openai.com/chat/b71743f4-aae0-4908-b52b-79e916f162e4";
    Symbol_manager huff;
    huff.frequency_counter(test);
    huff.display_heaped();
    return 0;
}