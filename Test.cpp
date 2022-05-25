#define CHECK DOCTEST_CHECK
#include "doctest.h"
#include "OrgChart.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;
using namespace ariel;



TEST_CASE("checking the size of the organization")
{

    OrgChart organization;
    CHECK_EQ(organization.get_num_of_employees(),0);
    organization.add_root("CEO");
    organization.add_sub("CEO", "CTO");         // Now the CTO is subordinate to the CEO
    organization.add_sub("CEO", "CFO");         // Now the CFO is subordinate to the CEO
    organization.add_sub("CEO", "COO");         // Now the COO is subordinate to the CEO
    organization.add_sub("CTO", "VP_SW"); // Now the VP Software is subordinate to the CTO
    organization.add_sub("COO", "VP_BI");
    
    CHECK_EQ(organization.get_num_of_employees(),6);
    CHECK_EQ(organization.get_map_order()[1].size(),3);
    CHECK_EQ(organization.get_map_order()[2].size(),2);
    CHECK_EQ(organization.get_map_order()[0].size(),1);




    OrgChart organization1;
    organization1.add_root("HEAD");
    organization1.add_sub("HEAD", "right_hand");
    organization1.add_sub("HEAD", "left_hand");
    organization1.add_sub("right_hand", "right_emp_1");    
    organization1.add_sub("left_hand", "left_emp_1");
    organization1.add_sub("right_hand", "right_emp_2");     
    organization1.add_sub("left_hand", "left_emp_2");
    CHECK_EQ(organization1.get_num_of_employees(),7);

    organization1.add_root("NEW_BOSS");
    CHECK_EQ(organization1.get_num_of_employees(),7);
    organization1.add_sub("left_hand", "left_emp_3") ;
    organization1.add_sub("left_hand", "left_emp_4") ;
    CHECK_EQ(organization1.get_num_of_employees(),9);



    
}

TEST_CASE("checking adding new employees"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("1"));
    CHECK_NOTHROW(organization.add_sub("1", "2"));
    CHECK_NOTHROW(organization.add_sub("1", "3"));
    CHECK_NOTHROW(organization.add_sub("2", "4"));
    CHECK_NOTHROW(organization.add_sub("2", "5"));
    CHECK_NOTHROW(organization.add_sub("3", "6"));
    CHECK_NOTHROW(organization.add_sub("3", "7"));
    CHECK_NOTHROW(organization.add_root("BOSS"));
    CHECK_NOTHROW(organization.add_sub("4", "8"));
    CHECK_NOTHROW(organization.add_sub("4", "9"));
    CHECK_NOTHROW(organization.add_sub("5", "10"));
    CHECK_NOTHROW(organization.get_root());
    CHECK_EQ(organization.get_num_of_employees(),10);
    CHECK_EQ(organization.get_map_order()[1].size(),2);
    CHECK_EQ(organization.get_map_order()[2].size(),4);
    CHECK_EQ(organization.get_map_order()[0].size(),1);




    OrgChart organization1;
    CHECK_THROWS(organization1.add_sub("right_hand", "right_emp_1"));
    CHECK_THROWS(organization1.add_sub("left_hand", "left_emp_1") ) ;   
    CHECK_THROWS(organization1.get_root());  
    CHECK_NOTHROW(organization1.add_root("Boss"));
    CHECK_EQ(organization1.get_num_of_employees(),1);
    CHECK_NOTHROW(organization1.add_sub("BOSS", "right_hand"));
    CHECK_EQ(organization1.get_num_of_employees(),2);
    CHECK_NOTHROW(organization1.add_sub("BOSS", "left_hand"));
    CHECK_NOTHROW(organization1.add_sub("left_hand", "left_emp_1") );
    CHECK_EQ(organization1.get_num_of_employees(),5);

  




   


    
}