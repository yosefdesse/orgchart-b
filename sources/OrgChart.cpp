
#include "OrgChart.hpp"
using namespace ariel;


namespace ariel
{
    OrgChart::OrgChart() : root(nullptr) , num_of_employees(0)
    {
        this->root=nullptr;
        this->num_of_employees=0;
    }

    OrgChart::~OrgChart()
    {

    }

    OrgChart& OrgChart::add_root(const string &new_root)
    {
        if(this->root==nullptr)
        {
            this->root=new Node(new_root , 0);
            this->num_of_employees++;
            this->map_order[0].push_back(this->root);
        }
        else{
            this->map_order[0].pop_back();
            this->root->emp_name=new_root;
            this->map_order[0].push_back(this->root);
        }

        return *this;

    }

    void OrgChart::if_employee_exist(Node *employee ,const string &emp ,const string &emp2)
    {
        Node *new_employee=nullptr;
     
        for(auto const  &level : this->get_map_order())
        {
            for(Node *temp_e : level.second)
            {
                if(temp_e->emp_name==emp)
                {
                    Node *temp_emp=new Node(emp2 , temp_e->employee_rank+1);
                    temp_e->children.push_back(temp_emp);
                    temp_emp->parent=temp_e;
                    map_order[temp_e->employee_rank].push_back(temp_emp);
                    this->num_of_employees++;               
                }

            }

        }
     
    }

    OrgChart& OrgChart::add_sub(const string &emp1 ,const string &emp2)
    {
        int size=this->num_of_employees;
        if(emp1.empty()||emp2.empty())
        {
            throw invalid_argument("all the employees mast have a name");
   
        }
        if(this->root==nullptr)
        {
            throw("the root doesn't exist");
        }
        if(this->get_root().emp_name==emp1)
        {
            Node *new_employee = new Node(emp2 , this->get_root().employee_rank+1);
            this->get_root().children.push_back(new_employee);
            this->map_order[new_employee->employee_rank].push_back(new_employee);
            this->num_of_employees++;

        }
        else{
          
            if_employee_exist(&this->get_root(),emp1 ,emp2);
          
        }
        if(size==this->get_num_of_employees())
        {

            throw("the employee doesn't exist  111");
        }
        return *this;
    }
    OrgChart::Iterator OrgChart::begin_level_order()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , root ,"level_order");
    }
    OrgChart::Iterator OrgChart::end_level_order()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , nullptr , "level_order");
    }

    OrgChart::Iterator OrgChart::begin_reverse_order()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , root , "reverse_order");
    }
    OrgChart::Iterator OrgChart::reverse_order()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , nullptr, "reverse_order");
    }

    OrgChart::Iterator OrgChart::begin_preorder()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , root , "preorder");
    }
    OrgChart::Iterator OrgChart::end_preorder()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , root , "preorder");
    }

    OrgChart::Iterator OrgChart::begin()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , root , "level_order");
    }
    OrgChart::Iterator OrgChart::end()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exis");
        }
        return Iterator(*this , root , "level_order");
    }

    OrgChart::Node &OrgChart::get_root()
    {
        if(this->root==nullptr)
        {
            throw("the root doesn't exist");
        }
        return *root;
    }

    int OrgChart::get_num_of_employees()const
    {
        return num_of_employees;
    }

    map<int , vector<OrgChart::Node *>> OrgChart::get_map_order()
    {
        return map_order;
    }


    ostream &operator << ( ostream &os, const OrgChart &orgC)
    {
        if(orgC.num_of_employees==0)
        {
            return os;
        }
        string organization="";

         for(auto const  &level : orgC.map_order)
        {
            for(OrgChart::Node *temp_e : level.second)
            {
                organization+=temp_e->emp_name;
                organization+= " , ";
            }
        }
        return os << organization;
    }      
        
         
}   
