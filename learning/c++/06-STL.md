专门讲一下标准库的一些知识补充.

# struct
***
struct 和 class 几乎完全一样, 只是默认的访问域不一样.
一个默认是public 一个默认是private
原因分析: c++为了兼容C语言, 同时扩展了struct的用法,让struct有了class的用途(构造 析构 成员 初始化列表等等)


# `weak_ptr`
***
`weak_ptr` 和 `shared_ptr`几乎是绑定的, 是为了解决`shared_ptr`可能导致的内存泄漏而已而出来的一种智能指针函数

相关函数:
`weak_ptr<P> p(new P{1}`
`weak_ptr<P> p = make_shared<P>(P{1})`
`weak_ptr<P> p = shared_ptr<P>(new P{1})`