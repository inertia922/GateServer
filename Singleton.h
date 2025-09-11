#ifndef SINGLETON_DETAIL_H
#define SINGLETON_DETAIL_H

#include <memory>
#include <iostream>

template<typename T>
class SingleTon {
public:
    // ��ȡ����ʵ�����̰߳�ȫ��C++11��֤�ֲ���̬������ʼ���̰߳�ȫ��
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> instance = std::shared_ptr<T>(new T());
        return instance;
    }

    // ��ӡʵ����ַ����֤Ψһ��
    void PrintAddress() const {
        std::cout << "ʵ����ַ: " << GetInstance().get() << std::endl;
    }

protected:
    // ���캯����Ϊ protected����ֹ�ⲿֱ�ӹ���
    SingleTon() = default;
    ~SingleTon() = default;

    // ���ÿ����͸�ֵ��ȷ��Ψһ��
    SingleTon(const SingleTon&) = delete;
    SingleTon& operator=(const SingleTon&) = delete;
};

#endif // SINGLETON_DETAIL_H