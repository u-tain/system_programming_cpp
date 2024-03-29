#ifndef LINALG_LINALG_HH
#define LINALG_LINALG_HH

#include <ostream>
#include <vector>

class Expression {};

template <class T>
class Vector;

template <class E>
Vector<typename E::value_type> evaluate(const E& expr) {
    using value_type = typename E::value_type;
    const auto n = expr.size();
    Vector<value_type> result(n);
    for (int i = 0; i < n; ++i) {
        result(i) = expr.evaluate(i);
    }
    return result;
}


template <class T>
class Vector : public Expression {

public:
    using value_type = T;

private:
    std::vector<T> _data;

public:

    Vector(std::initializer_list<T> rhs) : _data(rhs) {}
    explicit Vector(int n) : _data(n) {}
    template <class E>
    Vector(const E& expr,
        typename std::enable_if<std::is_base_of<Expression, E>::value, E>::type* dummy = nullptr) :
        Vector(::evaluate(expr)) {}

    Vector() = default;
    ~Vector() = default;
    Vector(Vector&& rhs) = default;
    Vector(const Vector& rhs) = default;
    Vector& operator=(Vector&& rhs) = default;
    Vector& operator=(const Vector& rhs) = default;

    bool operator!=(const Vector& rhs) const {
        const auto n = size();
        if (n != rhs.size())
            return true;
        for (int i = 0; i < n; ++i) {
            if (this->_data[i] != rhs._data[i])
                return true;
        }
        return false;
    }
    bool operator==(const Vector& rhs) const { return !(*this != rhs); }

    T& operator()(int i) { return this->_data[i]; }
    const T& operator()(int i) const { return this->_data[i]; }
    T evaluate(int i) { return this->_data[i]; }
    T evaluate(int i) const { return this->_data[i]; }
    int size() const { return this->_data.size(); }
    void display(std::ostream& out) const {
        out << "Vector(";
        const auto n = size();
        if (n != 0) { out << this->_data.front(); }
        for (int i = 1; i < n; ++i) { out << ',' << this->_data[i]; }
        out << ')';
    }

};
// реализация бинарного +
template <class E>
typename std::enable_if<std::is_base_of<Expression, E>::value, std::ostream&>::type
operator<<(std::ostream& out, const E& expr) {
    expr.display(out); return out;
}

template <class E1, class E2>
class Plus : public Expression {

public:
    using value_type =
        typename std::common_type<typename E1::value_type, typename E2::value_type>::type;

private:
    const E1& _a;
    const E2& _b;

public:
    explicit Plus(const E1& a, const E2& b) : _a(a), _b(b) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) + this->_b.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) + this->_b.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Plus(" << this->_a << ", " << this->_b << ')';
    }

};

template <class E1, class E2>
typename std::enable_if<std::is_base_of<Expression, E1>::value&&
    std::is_base_of<Expression, E2>::value, Plus<E1, E2>>::type
    operator+(const E1& a, const E2& b) {
    return Plus<E1, E2>(a, b);
}

/// реализация унарного -
template <class E>
class M : public Expression {
public:
    using value_type =
        typename std::common_type<typename E::value_type>::type;
private:
    const E& _a;
public:
    explicit M(const E& a) : _a(a) {}
    value_type evaluate(int i) {
        if (this->_a.evaluate(i) == 0)
            return this->_a.evaluate(i);
        else
            return -this->_a.evaluate(i);
    }
    value_type evaluate(int i) const {
        if (this->_a.evaluate(i) == 0)
            return this->_a.evaluate(i);
        else
            return -this->_a.evaluate(i);
    }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "M(" << this->_a << ')';
    }
};
template <class E>
typename std::enable_if<std::is_base_of<Expression, E>::value, M<E>>::type
operator-(const E& a) {
    return M<E>(a);
}
/// реализация унарного +
template <class E>
class P : public Expression {
public:
    using value_type =
        typename std::common_type<typename E::value_type>::type;
private:
    const E& _a;
public:
    explicit P(const E& a) : _a(a) {}
    value_type evaluate(int i) { return  this->_a.evaluate(i); }
    value_type evaluate(int i) const { return  this->_a.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "P(" << this->_a << ')';
    }
};
template <class E>
typename std::enable_if<std::is_base_of<Expression, E>::value, P<E>>::type
operator+(const E& a) {
    return P<E>(a);
}
/// реализация бинарного -
template <class E1, class E2>
class Minus : public Expression {

public:
    using value_type =
        typename std::common_type<typename E1::value_type, typename E2::value_type>::type;

private:
    const E1& _a;
    const E2& _b;

public:
    explicit Minus(const E1& a, const E2& b) : _a(a), _b(b) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) - this->_b.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) - this->_b.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Minus(" << this->_a << ", " << this->_b << ')';
    }

};

template <class E1, class E2>
typename std::enable_if<std::is_base_of<Expression, E1>::value&&
    std::is_base_of<Expression, E2>::value, Minus<E1, E2>>::type
    operator-(const E1& a, const E2& b) {
    return Minus<E1, E2>(a, b);
}
/// реализация бинарного оператора *
template <class E1, class E2>
class Proizv : public Expression {

public:
    using value_type =
        typename std::common_type<typename E1::value_type, typename E2::value_type>::type;

private:
    const E1& _a;
    const E2& _b;

public:
    explicit Proizv(const E1& a, const E2& b) : _a(a), _b(b) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) * this->_b.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) * this->_b.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Proizv(" << this->_a << ", " << this->_b << ')';
    }

};

template <class E1, class E2>
typename std::enable_if<std::is_base_of<Expression, E1>::value&&
    std::is_base_of<Expression, E2>::value, Proizv<E1, E2>>::type
    operator*(const E1& a, const E2& b) {
    return Proizv<E1, E2>(a, b);
}
/// реализация бинарного оператора /
template <class E1, class E2>
class Del : public Expression {

public:
    using value_type =
        typename std::common_type<typename E1::value_type, typename E2::value_type>::type;

private:
    const E1& _a;
    const E2& _b;

public:
    explicit Del(const E1& a, const E2& b) : _a(a), _b(b) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) / this->_b.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) / this->_b.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Del(" << this->_a << ", " << this->_b << ')';
    }

};

template <class E1, class E2>
typename std::enable_if<std::is_base_of<Expression, E1>::value&&
    std::is_base_of<Expression, E2>::value, Del<E1, E2>>::type
    operator/(const E1& a, const E2& b) {
    return Del<E1, E2>(a, b);
}
/// реализация операратора <
template <class E1, class E2>
class Sravn : public Expression {

public:
    using value_type = int;

private:
    const E1& _a;
    const E2& _b;

public:
    explicit Sravn(const E1& a, const E2& b) : _a(a), _b(b) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) < this->_b.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) < this->_b.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Sravn(" << this->_a << ", " << this->_b << ')';
    }

};

template <class E1, class E2>
typename std::enable_if<std::is_base_of<Expression, E1>::value&&
    std::is_base_of<Expression, E2>::value, Sravn<E1, E2>>::type
    operator<(const E1& a, const E2& b) {
    return Sravn<E1, E2>(a, b);
}
/// реализация операратора all
template <class E>
class All : public Expression {

public:
    using value_type = bool;

private:
    const E& _a;

public:
    explicit All(const E& a) : _a(a) {}
    value_type evaluate(int i) { return this->_a.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "All(" << this->_a << ')';
    }

};

template <class E>
typename std::enable_if<std::is_base_of<Expression, E>::value, bool>::type
all(const E& a) {
    bool result = true;
    for (int i = 0; i < a.size(); i++) {
        result &= a.evaluate(i);
    }
    return result;
};


/// реализация ?:
template <class E1, class E2, class E3>
class Where : public Expression {

public:
    using value_type =
        typename std::common_type<typename E1::value_type, typename E2::value_type, typename E3::value_type> ::type;


private:
    const E1& _a;
    const E2& _b;
    const E3& _c;

public:
    explicit Where(const E1& a, const E2& b, const E3& c) : _a(a), _b(b), _c(c) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) ? this->_b.evaluate(i) : this->_c.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) ? this->_b.evaluate(i) : this->_c.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Where(" << this->_a << ", " << this->_b << ')';
    }

};

template <class E1, class E2, class E3>
typename std::enable_if<std::is_base_of<Expression, E1>::value&&
    std::is_base_of<Expression, E2>::value&& std::is_base_of<Expression, E3>::value, Where<E1, E2, E3>>::type
    where(const E1& a, const E2& b, const E3& c) {
    return Where<E1, E2, E3>(a, b, c);
}
#endif // vim:filetype=cpp
