// File:        a5gradingdriver.cpp
// Author:      Geoffrey Tien
// Date:        April 11, 2016
// Description: Grading driver for CMPT 225 assignment 5

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "slinkedlist.hpp"
#include "hashtable.hpp"

using namespace std;

// maximum score declarations
const static double lltest1max = 3;
const static double lltest2max = 2;
const static double lltest3max = 2;
const static double lltest4max = 4;
const static double lltest5max = 2;
const static double httest1max = 2;
const static double httest2max = 5;
const static double httest3max = 4;
const static double httest4max = 2;

// forward function declarations
double LLTest1();
double LLTest2();
double LLTest3();
double LLTest4();
double LLTest5();
double HTTest1();
double HTTest2();
double HTTest3();
double HTTest4();

// program entry point
int main()
{
    double lltest1score = 0;
    double lltest2score = 0;
    double lltest3score = 0;
    double lltest4score = 0;
    double lltest5score = 0;
    double httest1score = 0;
    double httest2score = 0;
    double httest3score = 0;
    double httest4score = 0;
    
    cout << "Running linked list test 1: IsEmpty, InsertFront, Size, Contains... ";
    lltest1score = LLTest1();
    cout << " done.\n" << endl;
    
    cout << "Running linked list test 2: InsertBack, Size, Contains... ";
    lltest2score = LLTest2();
    cout << " done.\n" << endl;
    
    cout << "Running linked list test 3: Retrieve, Dump... ";
    lltest3score = LLTest3();
    cout << " done.\n" << endl;
    
    cout << "Running linked list test 4: Remove, RemoveAll... ";
    lltest4score = LLTest4();
    cout << " done.\n" << endl;
    
    cout << "Running linked list test 5: copy constructor, operator=... ";
    lltest5score = LLTest5();
    cout << " done.\n" << endl;
    
    cout << "Running hash table test 1: default constructor, Size, MaxSize, Insert (no expansion), ListAt... ";
    httest1score = HTTest1();
    cout << " done.\n" << endl;
    
    cout << "Running hash table test 2: parameterized constructor, Insert (with expansion), MaxSize, ListAt... ";
    httest2score = HTTest2();
    cout << " done.\n" << endl;
    
    cout << "Running hash table test 3: Remove, Search, Retrieve... ";
    httest3score = HTTest3();
    cout << " done.\n" << endl;
    
    cout << "Running hash table test 4: copy constructor, operator=... ";
    httest4score = HTTest4();
    cout << " done.\n" << endl;
    
    // compute total and maximum scores
    double testscoresum = lltest1score + lltest2score + lltest3score + lltest4score +
    lltest5score +
    httest1score + httest2score + httest3score + httest4score;
    
    double testmax = lltest1max + lltest2max + lltest3max + lltest4max +
    lltest5max +
    httest1max + httest2max + httest3max + httest4max;
    
    // format a string for summary output
    cout << "Test summary\n------------------------------------------------------------" << endl;
    string summary;
    ostringstream oss;
    oss << "LLTest1: " << lltest1score << "/" << lltest1max << "\tLLTest2: " << lltest2score << "/" << lltest2max
    << "\tLLTest3: " << lltest3score << "/" << lltest3max << endl
    << "LLTest4: " << lltest4score << "/" << lltest4max << "\tLLTest5: " << lltest5score << "/" << lltest5max << endl << endl
    << "HTTest1: " << httest1score << "/" << httest1max << "\tHTTest2: " << httest2score << "/" << httest2max
    << "\tHTTest3: " << httest3score << "/" << httest3max << endl
    << "HTTest4: " << httest4score << "/" << httest4max << endl
    << "------------------------------------------------------------" << endl
    << "Total: " << testscoresum << "/" << testmax << endl;
    cout << oss.str() << endl;
    
    system("pause");
    return 0;
}

// IsEmpty, InsertFront, Size, Contains
double LLTest1()
{
    double score = 0;
    
    // test empty and size 0
    SLinkedList<int> lla;
    if (lla.IsEmpty() && lla.Size() == 0)
        score += 0.5;
    
    // search empty list for an item
    if (!lla.Contains(17))
        score += 0.5;
    
    // add the first item
    lla.InsertFront(5);
    if ((!lla.IsEmpty()) && lla.Size() == 1 && lla.Contains(5))
        score += 1;
    
    // add another two items
    lla.InsertFront(7);
    lla.InsertFront(9);
    if ((!lla.IsEmpty()) && lla.Size() == 3 && lla.Contains(5) && lla.Contains(7) && lla.Contains(9))
        score += 0.5;
    
    // search for non-existent item
    if (!lla.Contains(17))
        score += 0.5;
    
    return score;
}

// InsertBack, Size, Contains
double LLTest2()
{
    double score = 0;
    
    SLinkedList<int> lla;
    if (lla.IsEmpty() && lla.Size() == 0)
    {
        lla.InsertBack(5);
        if ((!lla.IsEmpty()) && lla.Size() == 1 && lla.Contains(5))
            score += 1;
    }
    
    SLinkedList<int> llb;
    llb.InsertBack(7);
    llb.InsertFront(5); // together with InsertFront
    llb.InsertBack(9);
    if ((!llb.IsEmpty()) && llb.Size() == 3 && llb.Contains(5) && llb.Contains(7) && llb.Contains(9))
        score += 0.5;
    
    // search for non-existent item
    if (!lla.Contains(17))
        score += 0.5;
    
    return score;
}

// Retrieve, Dump
double LLTest3()
{
    double score = 0;
    
    SLinkedList<double> lla;
    
    lla.InsertBack(5);
    lla.InsertBack(7);
    lla.InsertBack(9);
    
    double* dptra;
    dptra = lla.Retrieve(17);
    if (dptra == NULL)
        score += 0.5;
    
    double* dptrb;
    dptrb = lla.Retrieve(7);
    if (*dptrb == 7)
    {
        score += 0.5;
        *dptrb = 6;
        if (lla.Size() == 3 && lla.Contains(5) && lla.Contains(6) && lla.Contains(9) && !lla.Contains(7))
            score += 0.5;
    }
    
    vector<double> vd = lla.Dump();
    if (vd.size() == 3 && vd.at(0) == 5 && vd.at(1) == 6 && vd.at(2) == 9)
        score += 0.5;
    
    return score;
}

// Remove, RemoveAll
double LLTest4()
{
    double score = 0;
    
    SLinkedList<int> lla;
    
    // Remove from empty list
    if (!lla.Remove(3))
        score += 0.5;
    
    lla.InsertBack(5);
    lla.InsertBack(6);
    lla.InsertBack(7);
    lla.InsertBack(8);
    
    if (!lla.Remove(17) && lla.Size() == 4)
        score += 0.5;
    
    if (lla.Size() == 4)
    {
        if (lla.Remove(5) && lla.Size() == 3 && !lla.Contains(5))
            score += 0.5;
    }
    
    SLinkedList<int> llb;
    llb.InsertBack(5);
    llb.InsertBack(6);
    llb.InsertBack(7);
    llb.InsertBack(8);
    if (llb.Size() == 4)
    {
        if (llb.Remove(8) && llb.Size() == 3 && !llb.Contains(8))
            score += 0.5;
    }
    
    SLinkedList<int> llc;
    llc.InsertBack(5);
    llc.InsertBack(6);
    llc.InsertBack(7);
    llc.InsertBack(8);
    if (llc.Size() == 4)
    {
        if (llc.Remove(6) && llc.Size() == 3 && !llc.Contains(6))
            score += 0.5;
    }
    
    SLinkedList<int> lld;
    lld.InsertBack(3);
    lld.InsertBack(4);
    if (lld.Size() == 2)
    {
        if (lld.Remove(4) && lld.Remove(3) && lld.IsEmpty())
            score += 0.5;
    }
    
    SLinkedList<int> lle;
    lle.InsertBack(5);
    lle.InsertBack(6);
    lle.InsertBack(7);
    lle.InsertBack(8);
    if (lle.Size() == 4)
    {
        lle.RemoveAll();
        if (lle.IsEmpty())
            score += 1;
    }
    
    return score;
}

// copy constructor, operator=
double LLTest5()
{
    double score = 0;
    
    SLinkedList<int> lla;
    lla.InsertBack(4);
    lla.InsertBack(5);
    lla.InsertBack(6);
    lla.InsertBack(7);
    
    SLinkedList<int> llb(lla);
    lla.InsertBack(8);
    llb.Remove(4);
    if (lla.Size() == 5 && lla.Contains(4) && lla.Contains(8))
        score += 0.5;
    if (llb.Size() == 3 && !llb.Contains(4) && !llb.Contains(8))
        score += 0.5;
    
    SLinkedList<int> llc;
    llc.InsertBack(9);
    llc.InsertBack(10);
    llc.InsertBack(11);
    llc.InsertBack(12);
    
    llb = llc;
    llc.InsertBack(13);
    llb.Remove(9);
    if (llc.Size() == 5 && llc.Contains(9) && llc.Contains(13))
        score += 0.5;
    if (llb.Size() == 3 && !llb.Contains(9) && !llb.Contains(13))
        score += 0.5;
    
    return score;
}

// default constructor, Size, MaxSize, Insert (no expansion), ListAt
double HTTest1()
{
    double score = 0;
    
    HashTable ht1;
    if (ht1.Size() == 0 && ht1.MaxSize() == 101)
    {
        bool listsempty = true;
        for (int i = 0; i < ht1.MaxSize(); i++)
        {
            listsempty = listsempty && ht1.ListAt(i)->IsEmpty();
        }
        if (listsempty)
            score += 0.5;
    }
    
    // Insert 4 items: 3 unique, into 2 different indices
    bool insertresult = true;
    insertresult = insertresult && ht1.Insert(UserAccount("bob", REGULAR_)); // hash index: 5
    insertresult = insertresult && ht1.Insert(UserAccount("max", REGULAR_)); // hash index: 36
    insertresult = insertresult && ht1.Insert(UserAccount("cj", REGULAR_));  // hash index: 5
    insertresult = insertresult && !ht1.Insert(UserAccount("bob", ADMIN_));  // hash index: 5, duplicate username
    if (insertresult && ht1.Size() == 3)
        score += 0.5;
    if (ht1.ListAt(5)->Size() == 2 && ht1.ListAt(36)->Size() == 1 && ht1.ListAt(48)->Size() == 0)
        score += 1;
    
    return score;
}

// parameterized constructor, Insert (with expansion), MaxSize, ListAt
double HTTest2()
{
    double score = 0;
    
    HashTable ht1(2); // maxsize: 5
    if (ht1.Size() == 0 && ht1.MaxSize() == 5)
    {
        bool listsempty = true;
        for (int i = 0; i < ht1.MaxSize(); i++)
        {
            listsempty = listsempty && ht1.ListAt(i)->IsEmpty();
        }
        if (listsempty)
            score += 0.5;
    }
    
    // Insert 4 unique items, into same index 0
    bool insertresult = true;
    insertresult = insertresult && ht1.Insert(UserAccount("hd", REGULAR_)); // 7 after resize
    insertresult = insertresult && ht1.Insert(UserAccount("md", REGULAR_)); // 2 after resize
    insertresult = insertresult && ht1.Insert(UserAccount("tj", REGULAR_)); // 1 after resize
    insertresult = insertresult && ht1.Insert(UserAccount("kc", REGULAR_)); // 3 after resize
    if (insertresult && ht1.Size() == 4)
        score += 0.5;
    if (ht1.LoadFactor() == 0.8)
        score += 0.5;
    if (ht1.ListAt(0)->Size() == 4 && ht1.ListAt(1)->Size() == 0 && ht1.ListAt(2)->Size() == 0 && ht1.ListAt(3)->Size() == 0 && ht1.ListAt(4)->Size() == 0)
        score += 1;
    
    // expand the array
    insertresult = insertresult && ht1.Insert(UserAccount("ju", REGULAR_)); // 0 after resize
    if (insertresult && ht1.Size() == 5 && ht1.MaxSize() == 11)
        score += 0.5;
    if (ht1.LoadFactor() == (double) 5 / (double) 11)
        score += 0.5;
    if (ht1.ListAt(0)->Size() == 1 && ht1.ListAt(1)->Size() == 1 && ht1.ListAt(2)->Size() == 1 && ht1.ListAt(3)->Size() == 1 && ht1.ListAt(4)->Size() == 0 && ht1.ListAt(7)->Size() == 1)
        score += 1.5;
    
    return score;
}

// Remove, Search, Retrieve
double HTTest3()
{
    double score = 0;
    
    HashTable ht1;
    
    // empty table
    if (!ht1.Search(UserAccount("bob", REGULAR_)))
        score += 0.5;
    if (!ht1.Remove(UserAccount("bob", ADMIN_)))
        score += 0.5;
    
    bool insertresult = true;
    insertresult = insertresult && ht1.Insert(UserAccount("bob", REGULAR_)); // hash index: 5
    insertresult = insertresult && ht1.Insert(UserAccount("max", REGULAR_)); // hash index: 36
    insertresult = insertresult && ht1.Insert(UserAccount("cj", REGULAR_));  // hash index: 5
    if (insertresult)
    {
        if (!ht1.Search(UserAccount("fo", REGULAR_))) // hash index: 5, non-existent
            score += 0.5;
        if (ht1.Search(UserAccount("bob", ADMIN_))) // match on username
            score += 0.5;
        
        UserAccount* uap = ht1.Retrieve(UserAccount("fo", ADMIN_));
        if (uap == NULL)
            score += 0.5;
        uap = ht1.Retrieve(UserAccount("bob", ADMIN_));
        if (uap != NULL)
            uap->SetPassword("password", "mynewpassword");
        UserAccount* uap2 = ht1.Retrieve(UserAccount("bob", REGULAR_));
        if (uap2 != NULL && uap2->GetPassword() == "mynewpassword")
            score += 0.5;
        
        if (!ht1.Remove(UserAccount("fo", REGULAR_)))
            score += 0.5;
        if (ht1.Remove(UserAccount("bob", ADMIN_)) && ht1.Size() == 2)
            score += 0.5;
    }
    
    return score;
}

// copy constructor, operator=
double HTTest4()
{
    double score = 0;
    
    HashTable ht1(5);
    // 3 items into index 0
    ht1.Insert(UserAccount("cc", REGULAR_));
    ht1.Insert(UserAccount("dd", REGULAR_));
    ht1.Insert(UserAccount("ee", REGULAR_));
    if (ht1.Size() == 3 && ht1.ListAt(0)->Size() == 3)
    {
        HashTable ht2(ht1);
        if (ht2.Size() == 3 && ht2.ListAt(0)->Size() == 3)
        {
            score += 0.5;
            ht1.Insert(UserAccount("ff", REGULAR_));
            ht2.Remove(UserAccount("cc", REGULAR_));
            if (ht1.Size() == 4 && ht2.Size() == 2 && ht1.Search(UserAccount("cc", REGULAR_)) && 
                !ht2.Search(UserAccount("cc", REGULAR_)) && !ht2.Search(UserAccount("ff", REGULAR_)))
                score += 0.5;
        }
    }
    
    
    HashTable ht3;
    ht3.Insert(UserAccount("aaa", ADMIN_));
    ht3.Insert(UserAccount("bbb", REGULAR_));
    if (ht3.Size() == 2)
    {
        ht3 = ht1;
        if (ht3.Size() == 4 && ht3.ListAt(0)->Size() == 4)
        {
            score += 0.5;
            ht1.Remove(UserAccount("cc", REGULAR_));
            ht1.Remove(UserAccount("ff", REGULAR_));
            if (ht3.Size() == 4 && ht3.ListAt(0)->Size() == 4 &&
                ht3.Search(UserAccount("cc", REGULAR_)) && ht3.Search(UserAccount("ff", REGULAR_)))
                score += 0.5;
        }
    }
    
    return score;
}