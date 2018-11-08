#include <iostream>
#include <memory>
#include "SmartPtr.h"

using namespace std;

SmartPtr::SmartPtr( )
{
    m_ptr = new DataType;
    m_refcount = new size_t (1);
    cout << "SmartPtr Dflt-ctor allocation, RefCount =" << *m_refcount << endl;
}

SmartPtr::SmartPtr( DataType * data )
{
    m_ptr = new DataType;
    m_ptr = data;
    m_refcount = new size_t;
    if(m_ptr)
    {
        *m_refcount = 1;
    }
    else
    {
        *m_refcount = 0;
        cout << "NULL pointer was passed, no data was allocated..." << endl;
    }

    cout << "SmartPtr Prmtrz-ctor from data pointer, RefCount =" << *m_refcount;
    cout << endl;
}


SmartPtr::SmartPtr( const SmartPtr& other ) //access to preallocated other.m_ptr && other.m_refcount
{
    if(other.m_ptr)
    {
        m_ptr = other.m_ptr;
        m_refcount = other.m_refcount;
        ++(*m_refcount);
    }
    else //other.m_ptr == NULL
    {
        cout << "Object with NULL pointer data was passed, refcount not incremented..." << endl;
        m_refcount = new size_t (0);
    }
    cout << "SmartPtr Copy-ctor, RefCount =" << *m_refcount << endl; //(c)
}


SmartPtr::~SmartPtr( )
{
    if(*m_refcount > 0)
        --(*m_refcount);

    else
    {
        cout << "SmartPtr D-tor, RefCount =" << *m_refcount << endl; //(d)
        delete m_refcount; //(c)
        delete m_ptr; //(c)
    }
}

SmartPtr& SmartPtr::operator=( const SmartPtr& rhs )
{
    if(this == &rhs)
        return *this;

    //if (this != &rhs)
    //{
    if(*m_refcount > 0)
        --(*m_refcount);
    else if(*m_refcount == 0)
    {
        cout << "SmartPtr Assignment Operator - Pre-releasing Memory , RefCount:";
        cout << *m_refcount << endl;
        delete m_refcount;
        delete m_ptr;
    }

    //return &SmartPtr (rhs);
    //SmartPtr * test_ptr = SmartPtr(rhs);
    //return test_ptr;
    //need to change this function to call the copy constructor
    if(!rhs.m_ptr)
    {
        cout << "Object with NULL pointer data was passed, refcount not incremented..." << endl;
        //m_ptr = NULL;
        m_refcount = new size_t (0);
    }
    else
    {
        cout << "Edit me 2" << endl;
        //m_ptr = NULL;
        m_ptr = rhs.m_ptr;
        m_refcount = rhs.m_refcount;
        ++(*m_refcount);
    }
    cout << "SmartPtr Assignment, RefCount=" << *m_refcount << endl;
    //}
    return *this;
}

//Overloaded dereference operator

DataType& SmartPtr::operator*( )
{
    return *m_ptr;
}

//overladed indirect member access operator
DataType* SmartPtr::operator->( )
{
    return m_ptr;
}
