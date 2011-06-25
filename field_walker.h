//
// field_walker.h
// Copyright (c) 2011, Bukov Anton (k06aaa@gmail.com)
// This source is released under the LGPL license.
//

#include <iterator>

namespace stliw
{
    #define fieldof(Object,field) (&(((Object*)NULL)->field))

    template<typename Category,
             typename IterType,
             typename FieldType>
    class field_walk_iterator
        : public std::iterator<Category,FieldType>
    {
    public:
        IterType it;
        FieldType * field;

    public:
        field_walk_iterator(FieldType * field)
            : it(IterType()), field(field)
        {
        }

        field_walk_iterator(IterType & it, FieldType * field)
            : it(it), field(field)
        {
        }

        // Base methods

        field_walk_iterator & operator ++ ()
        {
            ++it;
            return *this;
        }

        field_walk_iterator operator ++ (int) 
        {
            field_walk_iterator tmp(*this);
            operator++();
            return tmp;
        }

        // Input category methods

        bool operator == (const field_walk_iterator & rhs) const
        {
            return (it == rhs.it);
        }

        bool operator != (const field_walk_iterator & rhs) const
        {
            return !(*this == rhs);
        }

        FieldType operator * () const
        {
            return *(FieldType&*)((long)field) + ((long)&*it)
        }

        FieldType & operator * ()
        {
            long a = (long)&(*it);
            long b = (long)field;
            return *(FieldType*)(a + b);
        }

        // Bidirectional category methods

        field_walk_iterator & operator -- ()
        {
            --it;
            return *this;
        }

        field_walk_iterator operator -- (int) 
        {
            field_walk_iterator tmp(*this);
            operator--();
            return tmp;
        }

        // Random access category methods

        field_walk_iterator & operator += (int n)
        {
            it += n;
            return *this;
        }

        field_walk_iterator & operator -= (int n)
        {
            it -= n;
            return *this;
        }

        bool operator < (const field_walk_iterator & der) const
        {
            return (it < der.it);
        }

        bool operator > (const field_walk_iterator & der) const
        {
            return (it > der.it);
        }

        bool operator <= (const field_walk_iterator & der) const
        {
            return (it <= der.it);
        }

        bool operator >= (const field_walk_iterator & der) const
        {
            return (it >= der.it);
        }

        field_walk_iterator operator [] (int n) const
        {
            field_walk_iterator tmp(*this);
            return tmp += n;
        }
    };

    template<typename Category, typename IterType, typename T>
    field_walk_iterator<Category,IterType,T> operator + (
        const field_walk_iterator<Category,IterType,T> & der, int n)
    {
        field_walk_iterator<Category,IterType,T> tmp(der);
        return tmp += n;
    }

    template<typename Category, typename IterType, typename T>
    field_walk_iterator<Category,IterType,T> operator + (
        int n, const field_walk_iterator<Category,IterType,T> & der)
    {
        field_walk_iterator<Category,IterType,T> tmp(der);
        return tmp += n;
    }

    template<typename Category, typename IterType, typename T>
    field_walk_iterator<Category,IterType,T> operator - (
        const field_walk_iterator<Category,IterType,T> & der, int n)
    {
        field_walk_iterator<Category,IterType,T> tmp(der);
        return tmp -= n;
    }

    template<typename Category, typename IterType, typename T>
    ptrdiff_t operator - (
        const field_walk_iterator<Category,IterType,T> & a,
        const field_walk_iterator<Category,IterType,T> & b)
    {
        return (a.it - b.it);
    }

    template<typename Category, typename IterType, typename T>
    ptrdiff_t operator - (
        const field_walk_iterator<Category,IterType,T> & a,
        const IterType & b)
    {
        return (a.it - b);
    }

    /// --------------------------------------------------------------------

    template<typename IterType, typename T>
    field_walk_iterator<typename std::iterator_traits<IterType>::iterator_category,IterType,T>
    field_walker(IterType it, T * field)
    {
        return field_walk_iterator<typename std::iterator_traits<IterType>::iterator_category,IterType,T>(it,field);
    }
}
// namespace stliw