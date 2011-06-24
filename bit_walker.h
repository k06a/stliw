#include <iterator>

/// --------------------------------------------------------------------

template<typename Category,
         typename IterType,
         typename T = int>
class bit_walk_iterator
    : public std::iterator<Category,T>
{
public:
    IterType it;
    T nextBit;

public:
    bit_walk_iterator()
        : it(), nextBit(T())
    {
    }

    bit_walk_iterator(IterType & it)
        : it(it), nextBit(T())
    {
    }

    // Base methods

    bit_walk_iterator & operator ++ ()
    {
        nextBit++;
        if (nextBit == CHAR_BIT*sizeof(value_type))
        {
            ++it;
            nextBit = 0;
        }
        return *this;
    }

    bit_walk_iterator operator ++ (int) 
    {
        bit_walk_iterator tmp(*this);
        operator++();
        return tmp;
    }

    // Input category methods

    bool operator == (const bit_walk_iterator & rhs) const
    {
        return (it == rhs.it) && (nextBit == rhs.nextBit);
    }

    bool operator != (const bit_walk_iterator & rhs) const
    {
        return !(*this == rhs);
    }

    const T operator * () const
    {
        int byteNumber = nextBit / 8;
        int bitNumber  = nextBit % 8;
        char & ch = byteNumber[(char*)&(*it)];
        if ((*it) & (1 << bitNumber))
            return 1;
        return 0;
    }

    // Output category methods

    bit_walk_iterator & operator * ()
    {
        return *this;
    }

    template<typename TParam>
    bit_walk_iterator & operator = (TParam x)
    {
        int byteNumber = nextBit / 8;
        int bitNumber  = nextBit % 8;
        char & ch = byteNumber[(char*)&(*it)];
        ch &= (-1)^(1 << bitNumber);
        ch |= ((x?1:0) << bitNumber)
        return *this;
    }

    // Bidirectional category methods

    bit_walk_iterator & operator -- ()
    {
        nextBit--;
        if (nextBit == -1)
        {
            --it;
            nextBit = CHAR_BIT*sizeof(value_type)-1;
        }
        return *this;
    }

    bit_walk_iterator operator -- (int) 
    {
        bit_walk_iterator tmp(*this);
        operator--();
        return tmp;
    }

    // Random access category methods

private:
    bit_walk_iterator & move()
    {
        int bitsInObject = CHAR_BIT*sizeof(value_type);

        if (nextBit < 0)
        {
            it -= ((-nextBit) / bitsInObject)
                  + ((-nextBit) % bitsInObject > 0);
            nextBits = bitsInObject - ((-nextBit) % bitsInObject);
        } else
        if (nextBit > bitsInObject)
        {
            it += nextBit / bitsInObject;
            nextBit %= bitsInObject;
        }
        
        return *this;
    }

public:
    bit_walk_iterator & operator += (int n)
    {
        nextBit += n;
        return move();
    }

    bit_walk_iterator & operator -= (int n)
    {
        nextBit -= n;
        return move();
    }

    bool operator < (const bit_walk_iterator & der) const
    {
        return (it < der.it);
    }

    bool operator > (const bit_walk_iterator & der) const
    {
        return (it > der.it);
    }

    bool operator <= (const bit_walk_iterator & der) const
    {
        return (it <= der.it);
    }

    bool operator >= (const bit_walk_iterator & der) const
    {
        return (it >= der.it);
    }

    bit_walk_iterator operator [] (int n) const
    {
        bit_walk_iterator tmp(*this);
        return tmp += n;
    }
};

template<typename Category, typename IterType, typename T>
bit_walk_iterator<Category,IterType,T> operator + (
    const bit_walk_iterator<Category,IterType,T> & der, int n)
{
    bit_walk_iterator<Category,IterType,T> tmp(der);
    return tmp += n;
}

template<typename Category, typename IterType, typename T>
bit_walk_iterator<Category,IterType,T> operator + (
    int n, const bit_walk_iterator<Category,IterType,T> & der)
{
    bit_walk_iterator<Category,IterType,T> tmp(der);
    return tmp += n;
}

template<typename Category, typename IterType, typename T>
bit_walk_iterator<Category,IterType,T> operator - (
    const bit_walk_iterator<Category,IterType,T> & der, int n)
{
    bit_walk_iterator<Category,IterType,T> tmp(der);
    return tmp -= n;
}

template<typename Category, typename IterType, typename T>
ptrdiff_t operator - (
    const bit_walk_iterator<Category,IterType,T> & a,
    const bit_walk_iterator<Category,IterType,T> & b)
{
    return (a.it - b.it) + (a.nextBit - b.nextBit);
}

/// --------------------------------------------------------------------

template<typename T, typename IterType>
bit_walk_iterator<typename std::iterator_traits<IterType>::iterator_category,IterType,T>
bit_walker(IterType it)
{
    return it;
}

template<typename IterType>
bit_walk_iterator<typename std::iterator_traits<IterType>::iterator_category,IterType,int>
bit_walker(IterType it)
{
    return it;
}
