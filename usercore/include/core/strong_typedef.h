#ifndef STRONG_TYPEDEF_H
#define STRONG_TYPEDEF_H

// http://www.ilikebigbits.com/blog/2014/5/6/type-safe-identifiers-in-c
template<class Tag, class impl, impl default_value>
class StrongTypedef
{
public:
    static StrongTypedef invalid() { return StrongTypedef(); }

    // Defaults to ID::invalid()
    StrongTypedef() : m_val(default_value) { }

    // Explicit constructor:
    explicit StrongTypedef(impl val) : m_val(val) { }

    // Explicit conversion to get back the impl:
    explicit operator impl() const { return m_val; }

    friend bool operator==(StrongTypedef a, StrongTypedef b) { return a.m_val == b.m_val; }
    friend bool operator!=(StrongTypedef a, StrongTypedef b) { return a.m_val != b.m_val; }
    friend bool operator<(StrongTypedef a, StrongTypedef b) { return a.m_val < b.m_val; }

private:
    impl m_val;
};

#endif // STRONG_TYPEDEF_H
