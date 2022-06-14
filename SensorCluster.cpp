/*******************************************************************************/
//// Project 2: Using NIC addresses to Cluster Nodes of a Sensor Network //
/// CPSC 535 -section 1 //
/// Prof: Doina Bein //
/// Group: netclust//
/// Group members //
//  NIDHI SHAH :  nidhishah989@csu.fullerton.edu
//  MERIN JOSEPH: merin.joseph@csu.fullerton.edu
//  APEKSHA SHAH: apeksha@csu.fullerton.edu
////////////////////////////////////////////
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"
#include <queue>
#include<utility>
using namespace std;

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

//////////////////////////////////////////////////////////////////////////////////////
/* function to convert a character into its digit; 'A' converts into 10; 'B' into 11, etc.
*/
unsigned int hexa_to_number(char ch) {
    unsigned int temp = 0;
    // TODO: implement this function
    switch(ch)
    {
      case 'A':     //for 'A' character from NIC
        temp= 10;
        break;
      case 'B':    //for 'B' character from NIC
        temp= 11;
        break;
      case 'C':   //for 'C' character from NIC
        temp= 12;
        break;
      case 'D':   //for 'D' character from NIC
        temp= 13;
        break;
      case 'E':   //for 'E' character from NIC
        temp= 14;  
        break;
      case 'F':   //for 'F' character from NIC
        temp= 15;
        break;
      default:
        cout << "Invalid character" << endl;
        throw std::length_error("Invalid character");
    }
    return temp;
}
    
////////////////////////////////////////////////////////////////////////////
// function to return the hash value based on the first digit
unsigned int hashfct1(string nic) {
  ////// first digit means- index 0
  int hashval1;
  if (isdigit(nic[0]))       //if is digit from 0-9 , gives the hashvalue according to it as number %10 = same number
  {
      hashval1 = ((nic[0]-'0')%10);  //converitng the character number to integer number
  }
  else if(isalpha(nic[0]))     //if the nic character is from A-F , call the hexa_to_number function to get hash value
  {         
     hashval1 = hexa_to_number(nic[0]); 
  }
  return hashval1;
}

/////////////////////////////////////////////////////////////////////////////////////
// function to return the hash value based on the second digit
unsigned int hashfct2(string nic) {
  ////// first digit means- index 1
  int hashval2;
  if (isdigit(nic[1]))
  {
     hashval2= ((nic[1]-'0')%10);
  }
  else if(isalpha(nic[1]))
  {
     hashval2= hexa_to_number(nic[1]);
  }
  return hashval2;
}

///////////////////////////////////////////////////////////////////
// function to return the hash value based on the third digit
unsigned int hashfct3(string nic) {
	////// first digit means- index 2
  int hashval3;
  if (isdigit(nic[2]))
  {
     hashval3= ((nic[2]-'0')%10);
  }
  else if(isalpha(nic[2]))
  {
     hashval3= hexa_to_number(nic[2]);
  }
  return hashval3;
}

/////////////////////////////////////////////////////////////////////
// function to return the hash value based on the fourth digit
unsigned int hashfct4(string nic) {
	 ////// first digit means- index 3
  int hashval4;
  if (isdigit(nic[3]))
  {
     hashval4= ((nic[3]-'0')%10);
  }
  else if(isalpha(nic[3])){
     hashval4= hexa_to_number(nic[3]);
  } 
  return hashval4;
}

//////////////////////////////////////////////////////////////////////
// function to return the hash value based on the fifth digit
unsigned int hashfct5(string nic) {
	 ////// first digit means- index 4
  int hashval5;
  if (isdigit(nic[4]))
  {
      hashval5= ((nic[4]-'0')%10);
  }
  else if(isalpha(nic[4]))
  {
      hashval5= hexa_to_number(nic[4]);
  }
  return hashval5;
}

////////////////////////////////////////////////////////////////
// function to return the hash value based on the fourth digit
unsigned int hashfct6(string nic) {
	 ////// first digit means- index 5
  int hashval6;
  if (isdigit(nic[5]))
  {
     hashval6= ((nic[5]-'0')%10);
  }
  else if(isalpha(nic[5]))
  {
     hashval6= hexa_to_number(nic[5]); 
  }
  return hashval6;
}

///////////////////////////////////////////////////////////////
// Constructor for struct Item
Item::Item(string itemName, string nic):itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    string nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

/////////////////////////////////////////////////////////////////////////////////////////
// function that adds the specified NIC to the sensor network (i.e., to all hash tables)
void SensorNIC::addItem(string itemName, string nic) {
  // create a new Item based on given itemname(sensor name) and nic number
  Item newItem(itemName,nic);
  // now add the sensor item in 6 hashtables with its NIC number,
  // The hashvalue will be find through custom hashfunctions depend on hashtable.
  hT1[nic]=newItem; //Insert sensor to hashtable 1
  hT2[nic]=newItem; //Insert sensor to hashtable 2
  hT3[nic]=newItem; //Insert sensor to hashtable 3
  hT4[nic]=newItem; //Insert sensor to hashtable 4
  hT5[nic]=newItem; //Insert sensor to hashtable 5
  hT6[nic]=newItem; //Insert sensor to hashtable 6
}

////////////////////////////////////////////////////////////////////
// function that removes the sensor specified by the nic value from the network
// if sensor is found, then it is removed and the function returns true
// else returns false
bool SensorNIC::removeItem(string nic) {
   //store the true and false result
   bool bool1;
   if (hT1.find(nic) == hT1.end()) //if the nic not found.. means it is not in any hashtables.. return false
    { 
        bool1 = false; 
    }
  else  //the nic found in the first hashtable, so, it is avaiable in all hashtables, remove it from everyone and return true
  {
      hT1.erase(nic); //remove sensor from hashtable 1
      hT2.erase(nic);  //remove sensor from hashtable 2
      hT3.erase(nic);  //remove sensor from hashtable 3
      hT4.erase(nic);  //remove sensor from hashtable 4
      hT5.erase(nic);  //remove sensor from hashtable 5
      hT6.erase(nic);  //remove sensor from hashtable 6
      bool1 = true;
  }
    return bool1;
}

//////////////////////////////////////////////////////////////////////////
// function that decides the best hash function, i.e. the ones among
// fct1-fct6 that creates the most balanced sensor network for the current
// set of NIC addresses, i.e. data member allItems

// Hints:
// Calculate the balance of each hashtable, one by one.
unsigned int SensorNIC::bestHashing() {
 
  //the variables stores the min and max load value of cluster 
  unsigned int min,max;
  ////////////////////////// for hashtable 1 ////////////////////
  //store the first cluster load value as min and max
  min = max = hT1.bucket_size(0);
  // run the loop for all clusters except cluster o, and find min and max load value for hashtable 1 clusters
  for (unsigned i=1; i<16; ++i)
   {
      if(hT1.bucket_size(i)<min) // if the bucket size is less than, min load until now, than it becomes new min load value
      {
         min=hT1.bucket_size(i); //change the min laod value
      }
      if(hT1.bucket_size(i)>max) // if the bucket size is greater than, max load until now, than it becomes new max load value
      {
          max=hT1.bucket_size(i); //change the max laod value
      }
  }
  // balance of hashtable 1 calculation
  int loadbalance1 =max-min;
  ///////////////////////////////////////////////////////////////////
  
  ////////////////////////// for hashtable 2 ////////////////////
  //store the first cluster load value as min and max
  min = max = hT2.bucket_size(0);
  // run the loop for all clusters except cluster o, and find min and max load value for hashtable 2 clusters
  for (unsigned i=1; i<16; ++i)
  {
    if(hT2.bucket_size(i)<min) // if the bucket size is less than, min load until now, than it becomes new min load value
    {
        min=hT2.bucket_size(i); //change the min laod value
    }
    if(hT2.bucket_size(i)>max) // if the bucket size is greater than, max load until now, than it becomes new max load value
    {
        max=hT2.bucket_size(i); //change the max laod value
    }
  }
  
  // balance of hashtable 2 calculation
  int loadbalance2 =max-min;
  ///////////////////////////////////////////////////////////////////
  
  ////////////////////////// for hashtable 3 ////////////////////
  //store the first cluster load value as min and max
  min = max = hT3.bucket_size(0);
   // run the loop for all clusters except cluster o, and find min and max load value for hashtable 3 clusters
  for (unsigned i=1; i<16; ++i) {
  
    if(hT3.bucket_size(i)<min) // if the bucket size is less than, min load until now, than it becomes new min load valu
    {
        min=hT3.bucket_size(i); //change the min laod value
    }
    if(hT3.bucket_size(i)>max) // if the bucket size is greater than, max load until now, than it becomes new max load value
    { 
        max=hT3.bucket_size(i); //change the max laod value
    }
  }
  // balance of hashtable 3 calculation
  int loadbalance3 =max-min;
  ///////////////////////////////////////////////////////////////////
  
  ////////////////////////// for hashtable 4 ////////////////////
  //store the first cluster load value as min and max
  min = max = hT4.bucket_size(0);
  // run the loop for all clusters except cluster o, and find min and max load value for hashtable 4 clusters
  for (unsigned i=1; i<16; ++i) {
  
    if(hT4.bucket_size(i)<min) // if the bucket size is less than, min load until now, than it becomes new min load va
    {
        min=hT4.bucket_size(i); //change the min laod value
    }
    if(hT4.bucket_size(i)>max) // if the bucket size is greater than, max load until now, than it becomes new max load value
    {
        max=hT4.bucket_size(i); //change the max laod value
    }
  }
  // balance of hashtable 4 calculation
  int loadbalance4 =max-min;
  ///////////////////////////////////////////////////////////////////
  
  ////////////////////////// for hashtable 5 ////////////////////
  //store the first cluster load value as min and max
  min = max = hT5.bucket_size(0);
  // run the loop for all clusters except cluster o, and find min and max load value for hashtable 5 clusters
  for (unsigned i=1; i<16; ++i) {
  
    if(hT5.bucket_size(i)<min) // if the bucket size is less than, min load until now, than it becomes new min load va
    {
       min=hT5.bucket_size(i); //change the min laod value
    }
    if(hT5.bucket_size(i)>max) // if the bucket size is greater than, max load until now, than it becomes new max load value
    {
        max=hT5.bucket_size(i); //change the max laod value
    }
  }
  // balance of hashtable 5 calculation
  int loadbalance5 =max-min;
  ///////////////////////////////////////////////////////////////////
  
  ////////////////////////// for hashtable 6 ////////////////////
  //store the first cluster load value as min and max
  min = max = hT6.bucket_size(0);
  // run the loop for all clusters except cluster o, and find min and max load value for hashtable 6 clusters
  for (unsigned i=1; i<16; ++i) {
  
    if(hT6.bucket_size(i)<min) // if the bucket size is less than, min load until now, than it becomes new min load v
    {
        min=hT6.bucket_size(i); //change the min laod value
    }
    if(hT6.bucket_size(i)>max) // if the bucket size is greater than, max load until now, than it becomes new max load val
    {
        max=hT6.bucket_size(i); //change the max laod value
    }
  }
   // balance of hashtable 6 calculation
  int loadbalance6 =max-min;
   ///////////////////////////////////////////////////////////////////////
    
  // We calculate the load factor for each table and then store the load factor value in a min-heap priority queue. once all values 
  //are stored in min-heap for all 6 hash tables, then choose the min value.

  //insert all load balance value with hashtable number, and it will sort the queue with lower loadbalance to higher load balance
  typedef pair<int, int> load;
  priority_queue <load, vector<load>, greater<load>> bestloadqueue;
    bestloadqueue.push(make_pair(loadbalance1,1));
    bestloadqueue.push(make_pair(loadbalance2,2));
    bestloadqueue.push(make_pair(loadbalance3,3));
    bestloadqueue.push(make_pair(loadbalance4,4));
    bestloadqueue.push(make_pair(loadbalance5,5));
    bestloadqueue.push(make_pair(loadbalance6,6));

  // Then, calculate the lowest balance - wihch is top in queue
  pair<int, int> top = bestloadqueue.top();
  // return the hashtable number as result - which has best load balance
  return top.second;
}
///////////////////////////////////////////////////////////////

/////////////////////////////////////////////////
// ALREADY COMPLETED
size_t SensorNIC::size() {
  if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) )
  	  throw std::length_error("Hash table sizes are not the same");
    
	return hT1.size();
}
