#include <iomanip>
#include <iostream>
#include <ctime>

/**
 * @brief
 * @tparam Timer Any class that exposes the timeToProcess(int n) method
 * @param timer an instance of this class that shall have its timeToProcess method timed
 * @param n an upper bound for timing considerations
 * @return the time to process said function
 */
template <typename T>
double FindTime(T timer, int n)
{
    return timer.timeToProcess(n);
}

class TimedProcessor
{
public:
    double timeToProcess(int n)
    {
        clock_t start = clock();
        DoSomething(n);
        clock_t finish = clock();
        return static_cast<double>(finish - start) / CLOCKS_PER_SEC;
    }
protected:
    virtual void DoSomething(int n) = 0;
};

/**
 * @brief A concrete implementation of the TimedProcessor wherein DoSomething is defined
 *        by the code presented in Programming Problem 1A of Chapter 10 of our textbook
 *        by Carrano & Henry.
 */
class ProgrammingProblem1A : public TimedProcessor
{
protected:
    void DoSomething(int n) override
    {
        int sum{ 0 };
        for (int i{ 1 }; i < n; ++i)
        {
            for (int j{ 1 }; j < 10000; ++j)
            {
                sum += j;
            }
        }
    }
};

/**
 * @brief A concrete implementation of the TimedProcessor wherein DoSomething is defined
 *        by the code presented in Programming Problem 1B of Chapter 10 of our textbook
 *        by Carrano & Henry.
 */
class ProgrammingProblem1B : public TimedProcessor
{
protected:
    void DoSomething(int n) override
    {
        int i, j, sum = 0;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                sum = sum + j;
    }
};

/**
 * @brief A concrete implementation of the TimedProcessor wherein DoSomething is defined
 *        by the code presented in Programming Problem 2B of Chapter 10 of our textbook
 *        by Carrano & Henry.
 */
class Timer
{
public:
    /**
     * @brief Provide ability for Timer objects to "act" like one-arg functions.
     * @param n an upper bound on things to do while function is timed
     * @return the time, in seconds, it takes to do something (defined by subclasses).
     */
    double operator()(int n) const
    {
        clock_t start = clock();
        DoSomething(n);
        clock_t finish = clock();
        return static_cast<double>(finish - start) / CLOCKS_PER_SEC;
    }
protected:
    virtual void DoSomething(int n) const = 0;
};
class AKindOfTimer : public Timer
{
protected:
    void DoSomething(int n) const override
    {
        int sum{ 0 };
        for (int i{ 1 }; i < n; ++i)
        {
            for (int j{ 1 }; j < 10000; ++j)
            {
                sum += j;
            }
        }
    }
};
class BKindOfTimer : public Timer
{
protected:
    void DoSomething(int n) const override
    {
        int i, j, sum = 0;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                sum = sum + j;
    }
};

/**
 * @brief Template function used to find the time to process some action of a given function object.
 * @tparam Processor Any kind of function object that takes a single int argument
 * @param time_to_process a function object that takes a single int argument
 * @param n an upper bound for the function object to do its thing
 * @return the time (in seconds) it took the function object to do its thing
 */
template <typename Processor>
double FindTimeToProcess(Processor time_to_process, int n)
{
    return time_to_process(n);
}

int main()
{
    int n = 0;

    ProgrammingProblem1A pp1a{};
    double time1A = 0, time1B = 0, time2B = 0;
    for (n = 1; time1A <= time1B; n++)
    {
        time1A = FindTime(pp1a, n);
        time1B = FindTime(ProgrammingProblem1B{}, n);
        if (time1A > time1B)
            break;
    }
    std::cout << "Using Timed processor\n";
    std::cout << "Loop 1B is faster than Loop 1A at n= " << n << std::endl;
    std::cout << "Time consumed by loop 1B is    (n = " << n << "):  " << time2B << std::endl;
    std::cout << "Time consumed by loop 1A is    (n = " << n << "): " << time1A << std::endl;


    //using method 2 of implementation//
    time1A = 0; time1B = 0;
    AKindOfTimer timerA{};
    BKindOfTimer timerB{};
    for (n = 0; time1A <= time1B; n++)
    {

        time1A = timerA(n);
        time1B = timerB(n);
        if (time1A > time1B)
            break;
    }

    std::cout << "\n\nUsing Timer\n";
    std::cout << "Loop 1B is faster than Loop 1A at n= " << n << std::endl;
    std::cout << "Time consumed by loop 1B is    (n = " << n << "):  " << time2B << std::endl;
    std::cout << "Time consumed by loop 1A is    (n = " << n << "): " << time1A << std::endl;
    system("pause");
    return 0;
}
