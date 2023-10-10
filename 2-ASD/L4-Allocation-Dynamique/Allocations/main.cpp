//FORBIDDEN cout
//FORBIDDEN cerr
//FORBIDDEN printf
//FORBIDDEN puts
//FORBIDDEN putchar
//FORBIDDEN putc
#include "util.h"
#include "c.h"

int cnt = 0; // utilisez cette variable globale

void f0() noexcept {
    enter("f0");
    static C c2 = C(++cnt);
    C elem = ++cnt;
    leave("f0");
}

C *f1() {
    enter("f1");
    C *p;
    p = new C(++cnt);
    leave("f1");
    return p;
}

C *f2() {
    enter("f2");
    C *p;

    p = new C[2] {++cnt, ++cnt};

    leave("f2");
    return p;
}

void f3(C *p) noexcept {
    enter("f3");
    new(p) C(++cnt);
    leave("f3");
}

void f4(C *p, size_t n) noexcept {
    enter("f4");
    for(size_t i = 0; i < n; ++i) {
        new(&p[i]) C(++cnt);
    }
    leave("f4");
}

int main() {
    enter("main");
    C begin = C(++cnt);
    f0();
    f0();
    auto p1 = f1();
    auto p2 = f2();
    C* p3 = static_cast<C *>(::operator new(sizeof(C)));
    f3(p3);
    delete[] p2;
    delete p1;

    C* p4 = static_cast<C *>(::operator new[](sizeof(C) * 3));
    f4(p4, 2);
    delete p3;
    f4(&p4[2], 1);
    for (size_t i = 0; i < 3; ++i) {
        p4[i].~C();
    }
    ::operator delete(p4);
    leave("main");
}
