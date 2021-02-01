#include "catch2/catch.hpp"

#include "libcxx/include/type_traits"

// template basic:

template<class T> inline void swap(T& a, T& b)
{
    T c = a;
    a = b;
    b = c;
}

template<class T>
class Vector
{
    T* v = nullptr;
    int sz = 0;
    int pos = 0;

    void large_sz() {
		int new_sz = sz;
		if (new_sz == 0)  new_sz = 1;
		else new_sz = sz * 2;
        T* t = new T[new_sz];
        memcpy(t, v, sizeof(T*) * sz);
        delete[] v;
        v = t;
        sz = new_sz;
    }

public:
    Vector() {}
    explicit Vector(int sz) : sz(sz) { v = new T[sz]; }
    virtual ~Vector() { delete[] v; }

    T& elem(int i) { return v[i]; }
	T& operator[](int i) { return v[i]; }

    void push_back(T& x) {
        if (pos >= sz) large_sz();
        v[pos] = x; pos++;
    }

    int size() { return sz; }
    int len() { return pos; }

    void swap(Vector& o) { swap(v, o.v); swap(sz, o.sz); swap(pos, o.pos); }
};

template<class T> void swap(Vector<T>& a, Vector<T>& b)
{
    a.swap(b);
}

// 完全专门化
template<> class Vector<void*>
{
    // 重新定义自己的成员变量
    void** p = nullptr;
    int sz = 0;
    int pos = 0;

	void large_sz() {
        int new_sz = sz;
        if (new_sz == 0)  new_sz = 1;
        else new_sz = sz * 2;
        void** t = new void*[new_sz];
		memcpy(t, p, sizeof(void*) * sz);
		delete[] p;
        p = t;
        sz = new_sz;
	}

public:
    Vector() {}
    Vector(int sz) : sz(sz) { p = new void*[sz]; }
    virtual ~Vector() { delete[] p; }

    void*& elem(int i) { return p[i]; }
    void*& operator[] (int i) { return p[i]; }

	void push_back(void*& x) {
		if (pos >= sz) large_sz();
		p[pos] = x; pos++;
	}

	int size() { return sz; }
	int len() { return pos; }

	void swap(Vector& o) {
        ::swap(p, o.p); ::swap(sz, o.sz); ::swap(pos, o.pos);
	}
};

// 部分专门化
// 从非模板类派生模板类
template<class T> class Vector<T*> : private Vector<void*>
{
public:
    typedef Vector<void*> Base;

    Vector() : Base() {}
    explicit Vector(int i) : Base(i) { }
    virtual ~Vector() {}

    T*& elem(int i) { return reinterpret_cast<T*&>(Base::elem(i)); }
    T*& operator[] (int i) { return reinterpret_cast<T*&>(Base::operator[](i)); }

    void push_back(T*& x) {
        Base::push_back(reinterpret_cast<void*&>(x));
    }

    int size() { return Base::size(); }
    int len() { return Base::len(); }

    void swap(Vector& o) { Base::swap(o); }
};

template<class T> bool less(T a, T b) { return a < b; }

// less<const char*> 可以不用写，在函数参数中自动推导
// less<> 这个尖括号也不需要，前面template<>已经有了
// less<const char*> --> less<> --> less
template<> bool less(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}

// 把容器的基本运算符定义在一个单独的模板类中
// 方法 1 T-C分开
template <class C> class Basic_ops {
public:
    bool operator==(const C& c) const {
        if (derived().size() != c.size()) return false;
        for (int i = 0; i < derived().size(); ++i) {
            if (derived()[i] != c[i]) return false;
        }
        return true;
    }

    bool operator!= (const C& c) const {
        return !operator==(c);
    }

    const C& derived() const { return static_cast<const C&>(*this); }
};

template<class T> class Math_container : public Basic_ops<Math_container<T>> {
    T* v;
    size_t sz;

public:
    size_t size() const {
        return sz;
    }
    T& operator[] (size_t i) {
        return v[i];
    }
    const T& operator[] (size_t i) const {
        return v[i];
    }
};

// 这些要添加前置声明
template<class T, class C> class Mcontainer;
template<class T, class C>
bool operator==(const Mcontainer<T, C>& a, const Mcontainer<T, C>& b);
template<class T, class C>
bool operator!=(const Mcontainer<T, C>& a, const Mcontainer<T, C>& b);

// 方法2 T-C合并一个类
template<class T, class C> class Mcontainer {
    C elements;

public:
	size_t size() const {
		return elements.size();
	}

    T& operator[] (size_t i) { return elements[i]; }

    // 模板中的friend function
    friend bool operator==<>(const Mcontainer&, const Mcontainer&);
    friend bool operator!=<>(const Mcontainer&, const Mcontainer&);
};

template<class T, class C>
bool operator==(const Mcontainer<T, C>& a, const Mcontainer<T, C>& b)
{
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[b]) return false;
    }
    return true;
}

template<class T, class C>
bool operator!=(const Mcontainer<T, C>& a, const Mcontainer<T, C>& b)
{
    return !operator==(a, b);
}

template<typename T> class My_array {
    T* v;
    size_t sz;

public:

    size_t size() { return sz; }
    T& operator[] (size_t i) { return v[i]; }
};

// double 相等的问题
typedef Mcontainer<double, My_array<double>> MAC;

// helper class:

TEST_CASE("conditional", "[type_traits]") {
	using namespace omega;

    typedef conditional<(sizeof(int32_t) > sizeof(int64_t)), int32_t, int64_t>::type Type1;
    typedef conditional<false, int32_t, int64_t>::type Type2;
    typedef conditional<true, int32_t, int64_t>::type Type3;
    typedef conditional_t<false, int32_t, int64_t> Type4;

	REQUIRE(sizeof(Type1) == sizeof(int64_t));
	REQUIRE(sizeof(Type2) == sizeof(int64_t));
	REQUIRE(sizeof(Type3) == sizeof(int32_t));
    REQUIRE(sizeof(Type4) == sizeof(int64_t));

    Vector<int*> vip;
    int* ip = new int(123);
    vip.push_back(ip);
    int len = vip.len();
    int size = vip.size();
    REQUIRE(*vip[0] == 123);
}

struct T0 {
	enum { int_t, float_t } type;

    // template = int 等价于 template N = int，只是起一个类型推导匹配作用，并不需要实际类型
    // 我们需要的是前面的 Integer
	template <typename Integer,
		      typename = omega::enable_if_t<omega::is_integral<Integer>::value>
	>
		T0(Integer) : type(int_t) {}

	//template <typename Floating,
	//	      typename = std::enable_if_t<std::is_floating_point<Floating>::value>
	//>
	//	T(Floating) : type(float_t) {} // error C2535: 'T::T(Integer)': member function already defined or declared
};

struct T1 {
    enum { int_t, float_t } type;

    template <typename Integer,
              typename omega::enable_if_t <omega::is_integral<Integer>::value, bool> = true
    >
        T1(Integer) : type(int_t) {}

	template <typename Floating,
		typename omega::enable_if_t <omega::is_floating_point<Floating>::value, bool> = true
	>
		T1(Floating) : type(float_t) {}
};

TEST_CASE("enable_if", "[type_traits]") {
    using namespace omega;

    T0 t(1);
    T1 t1(1);
    T1 t1f(1.f);
}

TEST_CASE("integral_constant", "[type_traits]") {
    using namespace omega;

    integral_constant<bool, true> true_t;

    REQUIRE(true_t.value == true);
    REQUIRE(true_t.operator bool() == true);
    REQUIRE(static_cast<bool>(true_t) == true);
}

// helper traits
TEST_CASE("is_const", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_const<const int>::value == true);
    REQUIRE(is_const<int>::value == false);
}

TEST_CASE("is_volatile", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_volatile<volatile int>::value == true);
    REQUIRE(is_volatile<int>::value == false);
}

TEST_CASE("remove_const", "[type_traits]") {
    using namespace omega;

    REQUIRE(std::is_same<remove_const<const int>::type, int>::value == true);
}

TEST_CASE("remove_volatile", "[type_traits]") {
    using namespace omega;

    REQUIRE(std::is_same<remove_volatile<volatile int>::type, int>::value == true);
}

TEST_CASE("remove_cv", "[type_traits]") {
    using namespace omega;

    REQUIRE(std::is_same<remove_cv<volatile const int>::type, int>::value == true);
}

// -- type
TEST_CASE("is_void", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_void<void>::value == true);
    REQUIRE(is_void<const void>::value == true);
    REQUIRE(is_void<volatile const void>::value == true);

    REQUIRE(is_void<int>::value == false);
}

TEST_CASE("__is_nullptr_t", "[type_traits]") {
    using namespace omega;

    REQUIRE(__is_nullptr_t<std::nullptr_t>::value == true);
    //REQUIRE(__is_nullptr_t<NULL>::value == true);
    //REQUIRE(__is_nullptr_t<nullptr>::value == true);

    REQUIRE(__is_nullptr_t<int>::value == false);
}

TEST_CASE("is_integral", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_integral<bool>::value == true);
    REQUIRE(is_integral<char>::value == true);
    REQUIRE(is_integral<signed char>::value == true);
    REQUIRE(is_integral<unsigned char>::value == true);
    REQUIRE(is_integral<wchar_t>::value == true);

    REQUIRE(is_integral<char16_t>::value == true);
    REQUIRE(is_integral<char32_t>::value == true);

    REQUIRE(is_integral<short>::value == true);
    REQUIRE(is_integral<unsigned short>::value == true);
    REQUIRE(is_integral<int>::value == true);
    REQUIRE(is_integral<unsigned int>::value == true);
    REQUIRE(is_integral<long>::value == true);
    REQUIRE(is_integral<unsigned long>::value == true);
    REQUIRE(is_integral<long long>::value == true);
    REQUIRE(is_integral<unsigned long long>::value == true);

    struct S {};
    REQUIRE(is_integral<S>::value == false);
    REQUIRE(is_integral<std::string>::value == false);
    REQUIRE(is_integral<float>::value == false);
    REQUIRE(is_integral<double>::value == false);
    REQUIRE(is_integral<long double>::value == false);
}

TEST_CASE("is_floating_point", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_floating_point<float>::value == true);
    REQUIRE(is_floating_point<double>::value == true);
    REQUIRE(is_floating_point<long double>::value == true);
    REQUIRE(is_floating_point<int>::value == false);
}

TEST_CASE("is_array", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_array<float[]>::value == true);
    REQUIRE(is_array<float[1]>::value == true);
    //int x;
    //REQUIRE(is_array<float[x]>::value == true);
    REQUIRE(is_array<int>::value == false);
}

TEST_CASE("is_pointer", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_pointer<float[]>::value == false);
    REQUIRE(is_pointer<float[1]>::value == false);
    //float f[] = {0, 1, 2};
    //REQUIRE(is_pointer<decltype(f)>::value == true);
    REQUIRE(is_pointer<float*>::value == true);
    REQUIRE(is_pointer<int>::value == false);
}

TEST_CASE("is_lvalue_reference", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_lvalue_reference<float[]>::value == false);
    REQUIRE(is_lvalue_reference<int&>::value == true);
}

TEST_CASE("is_rvalue_reference", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_rvalue_reference<float[]>::value == false);
    REQUIRE(is_rvalue_reference<int&&>::value == true);
}

TEST_CASE("is_reference", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_reference<float[]>::value == false);
    REQUIRE(is_reference<int&>::value == true);
    REQUIRE(is_reference<int&&>::value == true);
}

TEST_CASE("is_union", "[type_traits]") {
    using namespace omega;

    //REQUIRE(is_union<float[]>::value == false);
    //REQUIRE(is_union<int&>::value == true);
    REQUIRE(is_union<int&&>::value == false);
    union U {};
    REQUIRE(is_union<U>::value == true);
    //REQUIRE(__is_union<U> == true);
}

TEST_CASE("is_class", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_class<float[]>::value == false);
    REQUIRE(is_class<int&>::value == false);
    REQUIRE(is_class<int&&>::value == false);

    class A {};
    REQUIRE(is_class<A>::value == true);
    struct S {};
    REQUIRE(is_class<S>::value == true);
    union U {};
    REQUIRE(is_class<U>::value == false);
}

// Primary classification traits:
TEST_CASE("is_enum", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_enum<float[]>::value == false);
    REQUIRE(is_enum<int&>::value == false);
    REQUIRE(is_enum<int&&>::value == false);

    class A {};
    REQUIRE(is_enum<A>::value == false);
    struct S {};
    REQUIRE(is_enum<S>::value == false);
    union U {};
    REQUIRE(is_enum<U>::value == false);

    enum E {};
    REQUIRE(is_enum<E>::value == true);
    enum class EC {};
    REQUIRE(is_enum<EC>::value == true);
}


// Secondary classification traits:


// Const-volatile properties and transformations:


// Reference transformations:


// Pointer transformations:


// Integral properties:


// Array properties and transformations:


// Member introspection:


// Relationships between types:


// Alignment properties and transformations:
