#include<thread>
#include<mutex>
#include<list>
template<typename T>
class TaskQueue{
private:
    std::list<T> ls;
    std::mutex mx;
    std::condition_variable cv;
public:
    void push(const T& val){
        std::unique_lock<std::mutex> ul(mx);
        ls.push_back(val);
        cv.notify_one();
    }
    T remove(){
        std::unique_lock<std::mutex> ul(mx);
        while(ls.size() == 0){
            cv.wait(ul);
        }
        T val = ls.front();
        ls.pop_front();
        return val;
    }
    size_t size(){
        std::unique_lock<std::mutex> ul(mx);
        return ls.size();
    }
public:
    TaskQueue() = default;
    virtual ~TaskQueue() = default;
    TaskQueue(const TaskQueue&) = delete;
    TaskQueue& operator = (const TaskQueue&) = delete;
};