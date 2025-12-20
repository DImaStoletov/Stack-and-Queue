#include "Stack.h"
#include "Queue.h"
#include <gtest/gtest.h>
#include <sstream>
#include <algorithm>

TEST(StackTest, Stack_Iterator)
{
    Stack<int> s;
    s.Push(10);
    s.Push(20);
    s.Push(30);

    Stack<int>::const_iterator cit = s.cbegin(), ocit;
    EXPECT_EQ(*cit, 30);
    ocit = ++cit;
    EXPECT_EQ(*cit, 20);
    EXPECT_EQ(*ocit, 20);
    ocit = cit++;
    EXPECT_EQ(*cit, 10);
    EXPECT_EQ(*ocit, 20);
    ++cit;
    EXPECT_EQ(cit, s.cend());

    const Stack<int>& r = s;
    cit = r.begin();
    EXPECT_EQ(*cit, 30);
    ++cit;
    EXPECT_EQ(*cit, 20);
    cit++;
    EXPECT_EQ(*cit, 10);
    ++cit;
    EXPECT_EQ(cit, r.end());

    Stack<int>::iterator it = s.begin(), oit;
    EXPECT_EQ(*it, 30);
    oit = ++it;
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*oit, 20);
    oit = it++;
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*oit, 20);
    *oit = 5;
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*oit, 5);
    ++it;
    EXPECT_EQ(it, s.end());

    std::stringstream sout;
    sout << s;
    EXPECT_EQ(sout.str(), "30 5 10");
}

TEST(StackTest, Stack_For)
{
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    const Stack<int>& r = s;
    int expected1[] = {3, 2, 1};
    int idx = 0;
    for (auto& v : r) EXPECT_EQ(v, expected1[idx++]);

    int expected2[] = {6, 4, 2};
    idx = 0;
    for (auto& v : s) v *= 2;

    idx = 0;
    for (const auto& v : s) EXPECT_EQ(v, expected2[idx++]);

    int expected3[] = {7, 5, 3};

    for (Stack<int>::iterator it = s.begin(); it != s.end(); ++it) {
        *it += 1;
    }
    idx = 0;
    for (Stack<int>::const_iterator it = s.begin(); it != s.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (Stack<int>::const_iterator it = r.begin(); it != r.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (Stack<int>::const_iterator it = s.cbegin(); it != s.cend(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
}

TEST(StackTest, Stack_PushPopCopy)
{
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    s.Pop();
    s.Push(10);
    s.Push(20);

    Stack<int> copy_s(s);

    int expected_orig[] = {20, 10, 2, 1};
    int idx = 0;
    for (auto v : copy_s) EXPECT_EQ(v, expected_orig[idx++]);

    copy_s.Pop();
    copy_s.Pop();
    copy_s.Push(99);
    copy_s.Push(98);
    copy_s.Push(97);

    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy[] = {97, 98, 99, 2, 1};
    idx = 0;
    for (auto v : copy_s) EXPECT_EQ(v, expected_copy[idx++]);

    Stack<int> moved_s(std::move(copy_s));

    int expected_moved[] = {97, 98, 99, 2, 1};
    idx = 0;
    for (auto v : moved_s) EXPECT_EQ(v, expected_moved[idx++]);

    EXPECT_TRUE(copy_s.IsEmpty());

    Stack<int> s2;
    s2 = s;
    idx = 0;
    for (auto v : s2) EXPECT_EQ(v, expected_orig[idx++]);

    s2.Pop();
    s2.Push(42);
    s2.Push(99);

    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy_asgn[] = {99, 42, 10, 2, 1};
    idx = 0;
    for (auto v : s2) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    Stack<int> s3;
    s3 = std::move(s2);
    idx = 0;
    for (auto v : s3) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    EXPECT_TRUE(s2.IsEmpty());

    s3.Pop();
    s3.Push(77);
    int expected_final[] = {77, 42, 10, 2, 1};
    idx = 0;
    for (auto v : s3) EXPECT_EQ(v, expected_final[idx++]);
}

TEST(StackTest, Stack_IO)
{
    Stack<int> s;
    s.Push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> s;

    EXPECT_EQ(s.Size(), 6);

    int expected[] = {5, 4, 3, 2, 1, 0};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << s;

    std::string expected_str = "5 4 3 2 1 0";
    EXPECT_EQ(sout.str(), expected_str);

    for (auto& v : s) v += 10;

    std::stringstream sout2;
    sout2 << s;
    std::string expected_str2 = "15 14 13 12 11 10";
    EXPECT_EQ(sout2.str(), expected_str2);
}

TEST(StackTest, Stack_Algs)
{
    Stack<int> s;

    for (int i = 1; i <= 5; ++i) s.Push(i);

    auto it = std::find_if(s.begin(), s.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(*it, 4);
    *it = 3;

    const Stack<int>& r = s;
    auto cit = std::find_if(r.begin(), r.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(*cit, 2);

    it = std::find_if(s.begin(), s.end(), [](int v){ return v == 0; });
    EXPECT_EQ(it, s.end());

    auto count_even = std::count_if(s.begin(), s.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(count_even, 1);

    std::replace_if(s.begin(), s.end(), [](int v){ return v % 2 != 0; }, 99);
    int expected_replace[] = {99, 99, 99, 2, 99};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_replace[idx++]);

    std::for_each(s.begin(), s.end(), [](int& v){ v += 1; });
    int expected_for_each[] = {100, 100, 100, 3, 100};
    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_for_each[idx++]);
}

TEST(QueueTest, Queue_Iterator)
{
    Queue<int> q;
    q.Push(10);
    q.Push(20);
    q.Push(30);

    Queue<int>::const_iterator cit = q.cbegin(), ocit;
    EXPECT_EQ(*cit, 10);
    ocit = ++cit;
    EXPECT_EQ(*cit, 20);
    EXPECT_EQ(*ocit, 20);
    ocit = cit++;
    EXPECT_EQ(*cit, 30);
    EXPECT_EQ(*ocit, 20);
    ++cit;
    EXPECT_EQ(cit, q.cend());

    const Queue<int>& r = q;
    cit = r.begin();
    EXPECT_EQ(*cit, 10);
    ++cit;
    EXPECT_EQ(*cit, 20);
    cit++;
    EXPECT_EQ(*cit, 30);
    ++cit;
    EXPECT_EQ(cit, r.end());

    Queue<int>::iterator it = q.begin(), oit;
    EXPECT_EQ(*it, 10);
    oit = ++it;
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*oit, 20);
    oit = it++;
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*oit, 20);
    *oit = 5;
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*oit, 5);
    ++it;
    EXPECT_EQ(it, q.end());

    std::stringstream sout;
    sout << q;
    EXPECT_EQ(sout.str(), "10 5 30");
}

TEST(QueueTest, Queue_For)
{
    Queue<int> q;
    q.Push(1);
    q.Push(2);
    q.Push(3);

    const Queue<int>& r = q;
    int expected1[] = {1, 2, 3};
    int idx = 0;
    for (auto& v : r) EXPECT_EQ(v, expected1[idx++]);

    int expected2[] = {2, 4, 6};
    idx = 0;
    for (auto& v : q) v *= 2;

    idx = 0;
    for (const auto& v : q) EXPECT_EQ(v, expected2[idx++]);

    int expected3[] = {3, 5, 7};

    for (Queue<int>::iterator it = q.begin(); it != q.end(); ++it) {
        *it += 1;
    }
    idx = 0;
    for (Queue<int>::const_iterator it = q.begin(); it != q.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (Queue<int>::const_iterator it = r.begin(); it != r.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (Queue<int>::const_iterator it = q.cbegin(); it != q.cend(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
}

TEST(QueueTest, Queue_PushPopCopy)
{
    Queue<int> q;
    q.Push(1);
    q.Push(2);
    q.Push(3);

    q.Pop();
    q.Push(10);
    q.Push(20);

    Queue<int> copy_q(q);

    int expected_orig[] = {2, 3, 10, 20};
    int idx = 0;
    for (auto v : copy_q) EXPECT_EQ(v, expected_orig[idx++]);

    copy_q.Pop();
    copy_q.Pop();
    copy_q.Push(99);
    copy_q.Push(98);
    copy_q.Push(97);

    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy[] = {10, 20, 99, 98, 97};
    idx = 0;
    for (auto v : copy_q) EXPECT_EQ(v, expected_copy[idx++]);

    Queue<int> moved_q(std::move(copy_q));

    int expected_moved[] = {10, 20, 99, 98, 97};
    idx = 0;
    for (auto v : moved_q) EXPECT_EQ(v, expected_moved[idx++]);

    EXPECT_TRUE(copy_q.IsEmpty());

    Queue<int> q2;
    q2 = q;
    idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected_orig[idx++]);

    q2.Pop();
    q2.Push(42);
    q2.Push(99);

    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy_asgn[] = {3, 10, 20, 42, 99};
    idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    Queue<int> q3;
    q3 = std::move(q2);
    idx = 0;
    for (auto v : q3) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    EXPECT_TRUE(q2.IsEmpty());

    q3.Pop();
    q3.Push(77);
    int expected_final[] = {10, 20, 42, 99, 77};
    idx = 0;
    for (auto v : q3) EXPECT_EQ(v, expected_final[idx++]);
}

TEST(QueueTest, Queue_IO)
{
    Queue<int> q;
    q.Push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> q;

    EXPECT_EQ(q.Size(), 6);

    int expected[] = {0, 1, 2, 3, 4, 5};
    int idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << q;

    std::string expected_str = "0 1 2 3 4 5";
    EXPECT_EQ(sout.str(), expected_str);

    for (auto& v : q) v += 10;

    std::stringstream sout2;
    sout2 << q;
    std::string expected_str2 = "10 11 12 13 14 15";
    EXPECT_EQ(sout2.str(), expected_str2);
}

TEST(QueueTest, Queue_Algs)
{
    Queue<int> q;

    for (int i = 1; i <= 5; ++i) q.Push(i);

    auto it = std::find_if(q.begin(), q.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(*it, 2);
    *it = 3;

    const Queue<int>& r = q;
    auto cit = std::find_if(r.begin(), r.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(*cit, 4);

    it = std::find_if(q.begin(), q.end(), [](int v){ return v == 0; });
    EXPECT_EQ(it, q.end());

    auto count_even = std::count_if(q.begin(), q.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(count_even, 1);

    std::replace_if(q.begin(), q.end(), [](int v){ return v % 2 != 0; }, 99);
    int expected_replace[] = {99, 99, 99, 4, 99};
    int idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_replace[idx++]);

    std::for_each(q.begin(), q.end(), [](int& v){ v += 1; });
    int expected_for_each[] = {100, 100, 100, 5, 100};
    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_for_each[idx++]);
}

TEST(ContainerTest, BaseContainer)
{
    Stack<int> s;
    Queue<int> q;

    s.Push(1);
    s.Push(2);
    s.Push(3);
    q.Push(10);
    q.Push(20);
    q.Push(30);

    fwd_container<int>& bs = s;
    fwd_container<int>& bq = q;
    const fwd_container<int>& cs = s;

    s.Clear();
    bs = q;

    int expected_s_after[] = {30, 20, 10};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_s_after[idx++]);

    q.Clear();
    bq = s;

    int expected_q_after[] = {30, 20, 10};
    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_q_after[idx++]);

    idx = 0;
    for (auto& it : bs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (const auto& it : bs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (const auto& it : cs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);

    idx = 0;
    for (const auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
