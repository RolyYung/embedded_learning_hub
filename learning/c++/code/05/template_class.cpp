#include <iostream>

using namespace std;

template <typename T>
class SeqList
{
public:
    SeqList(int size);
    ~SeqList();

    bool PushBack(T value);
    bool PopBack();
    
    void Show();
private:
    int m_size;
    T * m_data;
    int m_index;
};

template <typename T>
SeqList<T>::SeqList(int size) : m_size(size)
{
    m_data = new T[m_size];
    m_index = 0;
}

template <typename T>
SeqList<T>::~SeqList()
{
    // delete []m_data;
    delete m_data[];
}

template <typename T>
bool SeqList<T>::PushBack(T value)
{
    if(m_index == m_size){
        return false;
    }

    m_data[m_index] = value;
    m_index++;
    return true;
}

template <typename T>
bool SeqList<T>::PopBack()
{
    if(m_index == 0){
        return false;
    }

    m_index--;
    return true;
}

template <typename T>
void SeqList<T>::Show()
{
    for (size_t i = 0; i < m_index;  i++)
    {
        /* code */
        cout << m_data[i] << endl;
    }
    
}

int main(int argc, char *argv[])
{
    SeqList<int> seq{10};
    seq.PushBack(10);
    seq.PushBack(20);
    seq.PushBack(30);
    seq.PushBack(40);
    seq.PopBack();
    seq.PopBack();
    seq.Show();
    
    return 0;
}