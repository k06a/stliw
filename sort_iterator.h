//
// sort_iterator.h
// Copyright (c) 2011, Bukov Anton (k06aaa@gmail.com)
// This source is released under the LGPL license.
//

#include <iterator>

namespace stliw
{
    template<typename Category,
             typename IterType,
             typename T>
    class sort_iterator
        : public std::iterator<Category,T>
    {
    public:
        IterType current;
        IterType end;

    public:
        sort_iterator()
            : current(IterType())
            , end(IterType())
        {
        }

        sort_iterator(IterType & current, IterType & end)
            : current(current)
            , end(end)
        {
            makeSortStep();
        }

        void makeSortStep()
        {
            IterType minValueIter = current;
            for(IterType iter = current; iter != end; ++iter)
                if (*iter < *minValueIter)
                    minValueIter = iter;
            std::iter_swap(minValueIter, current);
        }

        // Base methods

        sort_iterator & operator ++ ()
        {
            ++current;
            makeSortStep();
            return *this;
        }

        sort_iterator operator ++ (int) 
        {
            sort_iterator tmp(*this);
            operator++();
            return tmp;
        }

        // Input category methods

        bool operator == (const sort_iterator & rhs) const
        {
            return (current == rhs.current);
        }

        bool operator == (const IterType & rhs) const
        {
            return (current == rhs);
        }

        bool operator != (const sort_iterator & rhs) const
        {
            return !(*this == rhs);
        }

        bool operator != (const IterType & rhs) const
        {
            return !(*this == rhs);
        }

        value_type & operator * ()
        {
            return *current;
        }

        // Bidirectional category methods

        sort_iterator & operator -- ()
        {
            --current;
            return *this;
        }

        sort_iterator operator -- (int) 
        {
            sort_iterator tmp(*this);
            operator--();
            return tmp;
        }

        // Random access category methods

        sort_iterator & operator += (int n)
        {
            for (int i = 0; i < n; i++)
                ++current;
            return *this;
        }

        sort_iterator & operator -= (int n)
        {
            current -= n;
            return *this;
        }

        bool operator < (const sort_iterator & der) const
        {
            return (current < der.current);
        }

        bool operator > (const sort_iterator & der) const
        {
            return (current > der.current);
        }

        bool operator <= (const sort_iterator & der) const
        {
            return (current <= der.current);
        }

        bool operator >= (const sort_iterator & der) const
        {
            return (current >= der.current);
        }

        sort_iterator operator [] (int n) const
        {
            sort_iterator tmp(*this);
            return tmp += n;
        }
    };

    template<typename Category, typename IterType, typename T>
    sort_iterator<Category,IterType,T> operator + (
        const sort_iterator<Category,IterType,T> & der, int n)
    {
        sort_iterator<Category,IterType,T> tmp(der);
        return tmp += n;
    }

    template<typename Category, typename IterType, typename T>
    sort_iterator<Category,IterType,T> operator + (
        int n, const sort_iterator<Category,IterType,T> & der)
    {
        sort_iterator<Category,IterType,T> tmp(der);
        return tmp += n;
    }

    template<typename Category, typename IterType, typename T>
    sort_iterator<Category,IterType,T> operator - (
        const sort_iterator<Category,IterType,T> & der, int n)
    {
        sort_iterator<Category,IterType,T> tmp(der);
        return tmp -= n;
    }

    template<typename Category, typename IterType, typename T>
    ptrdiff_t operator - (
        const sort_iterator<Category,IterType,T> & a,
        const sort_iterator<Category,IterType,T> & b)
    {
        return (a.current - b.current);
    }

    template<typename Category, typename IterType, typename T>
    ptrdiff_t operator - (
        const sort_iterator<Category,IterType,T> & a,
        const IterType & b)
    {
        return (a.current - b);
    }

    /// --------------------------------------------------------------------

    template<typename IterType>
    sort_iterator<typename std::iterator_traits<IterType>::iterator_category,
                  IterType,
                  typename std::iterator_traits<IterType>::value_type>
    sorter(IterType current, IterType end)
    {
        return sort_iterator<typename std::iterator_traits<IterType>::iterator_category,
                             IterType,
                             typename std::iterator_traits<IterType>::value_type>(current,end);
    }
}
// namespace stliw