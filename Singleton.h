#ifndef SINGLETON_DETAIL_H
#define SINGLETON_DETAIL_H

#include <memory>
#include <iostream>

template<typename T>
class SingleTon {
public:
    // 获取单例实例（线程安全，C++11保证局部静态变量初始化线程安全）
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> instance = std::shared_ptr<T>(new T());
        return instance;
    }

    // 打印实例地址，验证唯一性
    void PrintAddress() const {
        std::cout << "实例地址: " << GetInstance().get() << std::endl;
    }

protected:
    // 构造函数设为 protected，防止外部直接构造
    SingleTon() = default;
    ~SingleTon() = default;

    // 禁用拷贝和赋值，确保唯一性
    SingleTon(const SingleTon&) = delete;
    SingleTon& operator=(const SingleTon&) = delete;
};

#endif // SINGLETON_DETAIL_H