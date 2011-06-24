#include <iterator>

/// --------------------------------------------------------------------
/// Mixins of different iterator types:
///   bit_walk_iterator_base
///   bit_walk_iterator_input
///   bit_walk_iterator_output
///   bit_walk_iterator_forward
///   bit_walk_iterator_bidirectional
///   bit_walk_iterator_random_access
/// Help:
///   http://www.cplusplus.com/reference/std/iterator/
/// --------------------------------------------------------------------

template<typename IterType,
         typename Derived>
class bit_walk_iterator_base
{
public:
    IterType it;
    int nextBit;

public:
    bit_walk_iterator_base()
        : it(), nextBit(0)
    {
    }

    bit_walk_iterator_base(IterType & it)
        : it(it), nextBit(0)
    {
    }

    Derived & operator ++ ()
    {
        nextBit++;
        if (nextBit == CHAR_BIT*sizeof(typename IterType::value_type))
        {
            ++it;
            nextBit = 0;
        }
        return static_cast<Derived&>(*this);
    }

    Derived operator ++ (int) 
    {
        Derived tmp(*(Derived*)this);
        operator++();
        return tmp;
    }
};

template<typename Derived>
class bit_walk_iterator_input
{
public:
    bool operator == (const Derived & rhs) const
    {
        Derived * base = (Derived*)this;
        return (base->it == rhs.it) && (base->nextBit == rhs.nextBit);
    }

    bool operator != (const Derived & rhs) const
    {
        return !(*this == rhs);
    }

    const int & operator * () const
    {
        int byteNumber = nextBit / 8;
        int bitNumber  = nextBit % 8;
        char & ch = byteNumber[(char*)&(*it)];
        int bit = (*it) & (1 << bitNumber);
        return bit ? 1 : 0;
    }
};

template<typename Derived>
class bit_walk_iterator_output
{
public:
    Derived & operator * ()
    {
        return *this;
    }

    Derived & operator = (int x)
    {
        Derived * base = (Derived*)this;
        int byteNumber = base->nextBit / 8;
        int bitNumber  = base->nextBit % 8;
        char & ch = byteNumber[(char*)&(*base->it)];
        ch &= (-1)^(1 << bitNumber);
        ch |= ((x?1:0) << bitNumber)
        return *this;
    }
};

template<typename Derived>
class bit_walk_iterator_bidirectional
{
public:
    Derived & operator -- ()
    {
        nextBit--;
        if (nextBit == -1)
        {
            --it;
            nextBit = CHAR_BIT*sizeof(typename IterType::value_type)-1;
        }
        return static_cast<Derived&>(*this);
    }

    Derived operator -- (int) 
    {
        Derived tmp(*(Derived*)this);
        operator--();
        return tmp;
    }
};

template<typename Derived>
class bit_walk_iterator_random_access
{
    Derived & move()
    {
        int bitsInObject = CHAR_BIT*sizeof(typename IterType::value_type);

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
        
        return static_cast<Derived&>(*this);
    }

public:
    Derived & operator += (int n)
    {
        nextBit += n;
        return move();
    }

    Derived & operator -= (int n)
    {
        nextBit -= n;
        return move();
    }

    bool operator < (const bit_walk_iterator_random_access<Derived> & der) const
    {
        Derived * d1 = (Derived*)&a;
        Derived * d2 = (Derived*)&b;
        eturn (d1->it < d2->it);
    }

    bool operator > (const bit_walk_iterator_random_access<Derived> & der) const
    {
        Derived * d1 = (Derived*)&a;
        Derived * d2 = (Derived*)&b;
        eturn (d1->it > d2->it);
    }

    bool operator <= (const bit_walk_iterator_random_access<Derived> & der) const
    {
        Derived * d1 = (Derived*)&a;
        Derived * d2 = (Derived*)&b;
        eturn (d1->it <= d2->it);
    }

    bool operator >= (const bit_walk_iterator_random_access<Derived> & der) const
    {
        Derived * d1 = (Derived*)&a;
        Derived * d2 = (Derived*)&b;
        eturn (d1->it >= d2->it);
    }

    Derived operator [] (int n)
    {
        Derived d(*(Derived*)this);
        return d += n;
    }
};

template<typename Derived>
Derived operator + (const bit_walk_iterator_random_access<Derived> & der, int n)
{
    bit_walk_iterator_random_access<Derived> tmp(der);
    tmp += n;
    return tmp;
}

template<typename Derived>
Derived operator + (int n, const bit_walk_iterator_random_access<Derived> & der)
{
    bit_walk_iterator_random_access<Derived> tmp(der);
    tmp += n;
    return tmp;
}

template<typename Derived>
Derived operator - (const bit_walk_iterator_random_access<Derived> & der, int n)
{
    bit_walk_iterator_random_access<Derived> tmp(der);
    tmp -= n;
    return tmp;
}

template<typename Derived>
Derived operator - (const bit_walk_iterator_random_access<Derived> & a,
                    const bit_walk_iterator_random_access<Derived> & b)
{
    Derived * d1 = (Derived*)&a;
    Derived * d2 = (Derived*)&b;
    return (d1->it - d2->it);
}

/// --------------------------------------------------------------------
/// Different template specializaions:
///   bit_walk_iterator<std::input_iterator_tag>
///   bit_walk_iterator<std::output_iterator_tag>
///   bit_walk_iterator<std::forward_iterator_tag>
///   bit_walk_iterator<std::bidirectional_iterator_tag>
///   bit_walk_iterator<std::random_access_iterator_tag>
/// Help:
///   http://www.cplusplus.com/reference/std/iterator/
/// --------------------------------------------------------------------

template<typename Category, typename IterType>
class bit_walk_iterator
{
};

template<typename IterType>
class bit_walk_iterator<std::input_iterator_tag, IterType>
    : public std::iterator<std::input_iterator_tag, int>
    , public bit_walk_iterator_base<IterType,
                                    bit_walk_iterator<std::input_iterator_tag,
                                                      IterType> >
    , public bit_walk_iterator_input<bit_walk_iterator<std::input_iterator_tag,
                                                       IterType> >
{
public:
    bit_walk_iterator(IterType & it)
        : bit_walk_iterator_base(it)
    {
    }
};

template<typename IterType>
class bit_walk_iterator<std::output_iterator_tag, IterType>
    : public std::iterator<std::output_iterator_tag, int>
    , public bit_walk_iterator_base<IterType,
                                    bit_walk_iterator<std::output_iterator_tag,
                                                      IterType> >
    , public bit_walk_iterator_output<bit_walk_iterator<std::output_iterator_tag,
                                                        IterType> >
{
public:
    bit_walk_iterator(IterType & it)
        : bit_walk_iterator_base(it)
    {
    }
};

template<typename IterType>
class bit_walk_iterator<std::forward_iterator_tag, IterType>
    : public std::iterator<std::forward_iterator_tag, int>
    , public bit_walk_iterator_base<IterType,
                                    bit_walk_iterator<std::forward_iterator_tag,
                                                      IterType> >
    , public bit_walk_iterator_input<bit_walk_iterator<std::forward_iterator_tag,
                                                       IterType> >
    , public bit_walk_iterator_output<bit_walk_iterator<std::forward_iterator_tag,
                                                        IterType> >
{
public:
    bit_walk_iterator()
    {
    }

    bit_walk_iterator(IterType & it)
        : bit_walk_iterator_base(it)
    {
    }
};

template<typename IterType>
class bit_walk_iterator<std::bidirectional_iterator_tag, IterType>
    : public std::iterator<std::bidirectional_iterator_tag, int>
    , public bit_walk_iterator_base<IterType,
                                    bit_walk_iterator<std::bidirectional_iterator_tag,
                                                      IterType> >
    , public bit_walk_iterator_input<bit_walk_iterator<std::bidirectional_iterator_tag,
                                                       IterType> >
    , public bit_walk_iterator_output<bit_walk_iterator<std::bidirectional_iterator_tag,
                                                        IterType> >
    , public bit_walk_iterator_bidirectional<bit_walk_iterator<std::bidirectional_iterator_tag,
                                                               IterType> >
{
public:
    bit_walk_iterator()
    {
    }

    bit_walk_iterator(IterType & it)
        : bit_walk_iterator_base(it)
    {
    }
};

template<typename IterType>
class bit_walk_iterator<std::random_access_iterator_tag, IterType>
    : public std::iterator<std::random_access_iterator_tag, int>
    , public bit_walk_iterator_base<IterType,
                                    bit_walk_iterator<std::random_access_iterator_tag,
                                                      IterType> >
    , public bit_walk_iterator_input<bit_walk_iterator<std::bidirectional_iterator_tag,
                                                       IterType> >
    , public bit_walk_iterator_output<bit_walk_iterator<std::bidirectional_iterator_tag,
                                                        IterType> >
    , public bit_walk_iterator_bidirectional<bit_walk_iterator<std::bidirectional_iterator_tag,
                                                               IterType> >
    , public bit_walk_iterator_random_access<bit_walk_iterator<std::random_access_iterator_tag,
                                                               IterType> >
{
public:
    bit_walk_iterator()
    {
    }

    bit_walk_iterator(IterType & it)
        : bit_walk_iterator_base(it)
    {
    }
};


template<typename IterType>
bit_walk_iterator<typename IterType::iterator_category,IterType>
bit_walker(IterType & it)
{
    return it;
}