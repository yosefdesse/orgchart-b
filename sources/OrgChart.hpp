#include <map>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace ariel
{
    class OrgChart
    {
        private:
            

            class Node
            {
                public:
                string emp_name;
                int employee_rank;
                vector<Node *> children;
                Node *parent;

                Node(const string &name , int rank)
                {
                    this->emp_name=name;
                    this->employee_rank=rank;
                    this->parent=nullptr;
                }
                ~Node();
            };
            class Iterator
            {
                private:
                    Node *curr;
                    OrgChart *orgchart;
                    vector<Node *> for_order;
                    unsigned curr_rank;
                    // std::string type_order="";

                public:
                Iterator(OrgChart &org , Node *ptr = nullptr , string const &type ="") 
                {
                    if(ptr==nullptr)
                    {
                        this->curr=ptr;
                    }else{

                    
                    this->orgchart=&org;
                    // this->curr=ptr;
                    this->curr_rank=0;
                    if(type=="level_order")
                    {
                        level_order();
                    }
                    else if(type=="reverse_order")
                    {
                        reverse_order();
                    }
                    else
                    {
                        if(type=="preorder")
                        {
                            preorder();
                        }
                    }
                    this->curr=this->for_order.front();
                    this->for_order.erase(for_order.begin());
                    }

                }

                string &operator*() const
                {
                    return curr->emp_name;
                }

                string* operator->() const
                {
                    return &(curr->emp_name);
                }

                Iterator &operator++()
                {
                
                    if(!this->for_order.empty())
                    {
                        curr=for_order.front();
                        this->for_order.erase(for_order.begin());

                    }else{
                        this->curr=nullptr;
                    }
                //     if (!nodeList.empty())
                // {
                //     _cur = nodeList.front();
                //     nodeList.pop_front();
                // }
                // else
                // {
                //     _cur = nullptr;
                // }
                // return *this;
                    return *this;
                }

                Iterator operator++(int)
                {
                    Iterator it = *this;
                    ++(*this);
                    return it;
                }

                bool operator==(const Iterator &emp) const
                {
                    if(this->curr==emp.curr)
                    {
                        return true;
                    }
                    return false;
                }

                bool operator!=(const Iterator &emp) const
                {
                    if(this->curr==emp.curr)
                    {
                        return false;
                    }
                    return true;
                }

                void level_order()
                {
                   
                    for(auto  level : this->orgchart->get_map_order())
                    {
                        for(Node *temp_e : level.second)
                        {
                            
                                this->for_order.push_back(temp_e);
                        
                        }
                    }
                   

                    // cout<< "Hello Level"<< endl;
                    // for(auto node:for_order){
                    //     cout << node->emp_name<< endl;
                    // }
                }

                void reverse_order()
                {
                    vector<Node *> vec;
                    for(auto level : this->orgchart->get_map_order())
                    {
                        for(Node *temp_e : level.second)
                        {
                            
                                vec.push_back(temp_e);
                            
                        }
                    }
                    unsigned int size = vec.size();
                    for(unsigned int i=size ; i>0 ; i--)
                    {
                        if(vec.at(i-1) != nullptr)
                        {
                            // v.insert(v.begin(), 5);
                            this->for_order.insert(for_order.begin(),vec.front());
                            vec.erase(vec.begin());                        
                        }                      
                    }
                }

                void preorder()
                {
                    vector<Node *> vec;
                    vec.push_back(this->orgchart->root);
                    while(!vec.empty())
                    {
                        curr=vec.front();
                        vec.erase(vec.begin());
                        this->for_order.push_back(this->curr);
                        for (unsigned int i = this->curr->children.size() ; i > 0 ; i--)
                        {
                            vec.push_back(this->curr->children[i - 1]);
                        }
                    }
                    
             
                }


                
            };
            Node *root;
            int num_of_employees;
            

        
        public: 
            map<int , vector<Node *>> map_order;
            OrgChart();
            ~OrgChart();
            OrgChart(OrgChart& ) = default;
            OrgChart(OrgChart&& ) = default;
            OrgChart& add_root(const string &new_root);
            OrgChart& add_sub(const string &emp1 , const string &emp2);
            Iterator begin_level_order();
            Iterator end_level_order();

            Iterator begin_reverse_order();
            Iterator reverse_order();

            Iterator begin_preorder();
            Iterator end_preorder();

            Iterator begin();
            Iterator end();
            Node &get_root();
            void if_employee_exist(Node *employee ,const string &emp ,const string &emp2) ;
            int get_num_of_employees()const;
            map<int , vector<Node *>> get_map_order();
            friend ostream &operator << ( ostream &os, const OrgChart &orgC);            
        
         
            
                             
    };
}
