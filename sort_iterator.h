//
// sort_iterator.h
// Copyright (c) 2011, Bukov Anton (k06aaa@gmail.com)
// This source is released under the LGPL license.
//

#include <iterator>

namespace stliw
{
    enum SortOrder
    {
        Ascending,
        Descending
    };

    template<typename Category,
             typename IterType,
             typename T,
             SortOrder SORT = Ascending>
    class sort_iterator
        : public std::iterator<Category,T>
    {
    public:
        IterType begin;
        IterType end;
        IterType prevIter;
        int index;

    public:
        sort_iterator()
            : begin(IterType())
            , end(IterType())
            , prevIter(IterType())
            , index(0)
        {
        }

        sort_iterator(const IterType & begin,
                      const IterType & end)
            : begin(begin)
            , end(end)
            , prevIter(IterType())
            , index(0)
        {
            if (begin == end)
            {
                prevIter = end;
                return;
            }
            
            if (SORT == Ascending)
                makeSortStepForward();
            else
                makeSortStepBackward();
        }

    private:
        void makeSortStepForward()
        {
            if (index == end - begin)
            {
                prevIter = end;
                return;
            }

            if (index == 0)
            {
                prevIter = begin;
                for(IterType it = begin; it != end; ++it)
                    if (*it < *prevIter)
                        prevIter = it;
                index++;
                return;
            }

            IterType minValueIter = begin;
            for(IterType it = begin; it != end; ++it)
            {
                if (*prevIter < *it)
                {
                    if (*it < *minValueIter)
                        minValueIter = it; 
                }
                else
                if (*prevIter == *it)
                {
                    if (prevIter < it)
                    {
                        minValueIter = it;
                        break;
                    }
                }
            }
            prevIter = minValueIter;
            index++;
        }

        void makeSortStepBackward()
        {
            if (index == end - begin)
            {
                prevIter = end;
                return;
            }

            if (index == 0)
            {
                prevIter = begin;
                for(IterType it = begin; it != end; ++it)
                    if (*prevIter < *it)
                        prevIter = it;
                index--;
                return;
            }

            IterType maxValueIter = begin;
            for(IterType it = begin; it != end; ++it)
            {
                if (*it < *prevIter)
                {
                    if (*maxValueIter == *prevIter)
                        maxValueIter = it;
                    else
                    if (*maxValueIter < *it)
                        maxValueIter = it; 
                }
                else
                if (*prevIter == *it)
                {
                    if (it < prevIter)
                    {
                        maxValueIter = it;
                        break;
                    }
                }
            }
            prevIter = maxValueIter;
            index--;
        }

        // Base methods

    public:
        sort_iterator & operator ++ ()
        {
            if (SORT == Ascending)
                makeSortStepForward();
            else
                makeSortStepBackward();
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
            return (prevIter == rhs.prevIter);
        }

        bool operator == (const IterType & rhs) const
        {
            return (begin + index == rhs);
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
            return *prevIter;
        }

        // Bidirectional category methods

        sort_iterator & operator -- ()
        {
            if (SORT == Ascending)
                makeSortStepBackward();
            else
                makeSortStepForward();
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
                ++begin;
            return *this;
        }

        sort_iterator & operator -= (int n)
        {
            begin -= n;
            return *this;
        }

        bool operator < (const sort_iterator & der) const
        {
            return (begin < der.begin);
        }

        bool operator > (const sort_iterator & der) const
        {
            return (begin > der.begin);
        }

        bool operator <= (const sort_iterator & der) const
        {
            return (begin <= der.begin);
        }

        bool operator >= (const sort_iterator & der) const
        {
            return (begin >= der.begin);
        }

        sort_iterator operator [] (int n) const
        {
            sort_iterator tmp(*this);
            return tmp += n;
        }
    };

    template<typename Category, typename IterType, typename T, SortOrder SORT>
    sort_iterator<Category,IterType,T,SORT> operator + (
        const sort_iterator<Category,IterType,T,SORT> & der, int n)
    {
        sort_iterator<Category,IterType,T,SORT> tmp(der);
        return tmp += n;
    }

    template<typename Category, typename IterType, typename T, SortOrder SORT>
    sort_iterator<Category,IterType,T,SORT> operator + (
        int n, const sort_iterator<Category,IterType,T,SORT> & der)
    {
        sort_iterator<Category,IterType,T,SORT> tmp(der);
        return tmp += n;
    }

    template<typename Category, typename IterType, typename T, SortOrder SORT>
    sort_iterator<Category,IterType,T,SORT> operator - (
        const sort_iterator<Category,IterType,T,SORT> & der, int n)
    {
        sort_iterator<Category,IterType,T,SORT> tmp(der);
        return tmp -= n;
    }

    template<typename Category, typename IterType, typename T, SortOrder SORT>
    ptrdiff_t operator - (
        const sort_iterator<Category,IterType,T,SORT> & a,
        const sort_iterator<Category,IterType,T,SORT> & b)
    {
        return (a.begin - b.begin);
    }

    template<typename Category, typename IterType, typename T, SortOrder SORT>
    ptrdiff_t operator - (
        const sort_iterator<Category,IterType,T,SORT> & a,
        const IterType & b)
    {
        return (a.begin - b);
    }

    /// --------------------------------------------------------------------

    template<SortOrder SORT, typename IterType>
    sort_iterator<typename std::iterator_traits<IterType>::iterator_category,
                  IterType,
                  typename std::iterator_traits<IterType>::value_type,
                  SORT>
    sorter(IterType begin, IterType end = IterType())
    {
        if (end == IterType())
            end = begin;
        return sort_iterator<typename std::iterator_traits<IterType>::iterator_category,
                             IterType,
                             typename std::iterator_traits<IterType>::value_type,
                             SORT>(begin,end);
    }

    template<typename IterType>
    sort_iterator<typename std::iterator_traits<IterType>::iterator_category,
                  IterType,
                  typename std::iterator_traits<IterType>::value_type,
                  Ascending>
    sorter(IterType begin, IterType end = IterType())
    {
        if (end == IterType())
            end = begin;
        return sort_iterator<typename std::iterator_traits<IterType>::iterator_category,
                             IterType,
                             typename std::iterator_traits<IterType>::value_type,
                             Ascending>(begin,end);
    }
}
// namespace stliw