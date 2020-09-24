#include <bits/stdc++.h>

int shortestSubarray(std::vector<int> &A, int K)
{
    if (A.size() == 1 && A[0] != K)
    {
        return -1;
    }
    int sum = 0;
    std::vector<std::pair<int, int *>> store;
    int *max_val = nullptr;
    std::vector<int>::iterator it = A.begin(), end = A.end();
    int two_sum = 0;
    while (it != end)
    {
        if (*it >= K)
        {
            return 1;
        }
        else
        {
            if (max_val == nullptr || *it > *max_val)
            {
                max_val = &*it;
            }
            if (it != end-1 && *it + *(it + 1) > two_sum)
            {
                two_sum = *it + *(it + 1);
            }
            std::pair<int, int *> n_pair(*it, &*it);
            store.insert(std::upper_bound(store.begin(), store.end(), n_pair,
                                          [](std::pair<int, int *> a, std::pair<int, int *> b) {
                                              return a.first > b.first;
                                          }),
                         n_pair);
        }
        it++;
    }
    if (two_sum > K)
        return 2;
    if(A.size() < 2)
        return -1;
    std::size_t arr_sz = 3;
    int max_sum = 0;
    if(max_val != &A[0] && max_val != &A.back()){
        max_sum = (*max_val + *(max_val + 1) + *(max_val - 1) > *max_val) ? *max_val + *(max_val + 1) + *(max_val - 1) : *max_val;
    }else if (max_val != &A[0]+1){
         max_sum = (*max_val + *(max_val - 1) + *(max_val - 2) > *max_val) ? *max_val + *(max_val - 1) + *(max_val -2) : *max_val;
    }else if(max_val != &A[A.size()-1]){
         max_sum = (*max_val + *(max_val + 2) + *(max_val + 1) > *max_val) ? *max_val + *(max_val + 2) + *(max_val + 1) : *max_val;
    }else{
        max_sum = *max_val;
    }
    int current_arr_sz = 0;
    for (; arr_sz <= A.size(); arr_sz++)
    {
        for (int i = 0; i <= store.size(); i++)
        {
            int *left = store[i].second;
            int *right = store[i].second;
            sum = store[i].first;
            current_arr_sz = 0;
            while (current_arr_sz != arr_sz)
            {
                if (left != &A[0])
                {
                    sum += *left;
                    left -= 1;
                    current_arr_sz++;
                }
                if (right != &A[A.size() - 1])
                {
                    sum += *right;
                    right += 1;
                    current_arr_sz++;
                }
                if (sum < K)
                {
                    if (left == &A[0] && right == &A[A.size() - 1])
                    {
                        return -1;
                    }
                    if (sum > max_sum)
                    {
                        max_val = store[i].second;
                        max_sum = sum;
                    }
                }
                else
                {
                    return arr_sz;
                }
            }
            delete left;
            delete right;
        }
    }
    std::cout << "here\n";
    return -1;
}

int main()
{
    std::vector<int> t = {-500, -100, 600, 1};
    std::vector<int> t2 = {1, 2};
    std::vector<int> t3 = {1, 2, 60, 100, 20, 50, 4, -2, 3, -500, -1, 1, 1, 1, -3, 4};
    int res = shortestSubarray(t, 1);
    std::cout << "Result: " << res << '\n';
    res = shortestSubarray(t2, 4);
    std::cout << "Result2: " << res << '\n';
    res = shortestSubarray(t3, 4);
    std::cout << "Result3: " << res << '\n';
    res = shortestSubarray(t3, 500);
    std::cout << "Result4: " << res << '\n';
    res = shortestSubarray(t3, 101);
    std::cout << "Result5: " << res << '\n';
    res = shortestSubarray(t3, 999);
    std::cout << "Result6: " << res << '\n';
    res = shortestSubarray(t3, 90);
    std::cout << "Result7: " << res << '\n';
    std::vector<int> t4 = {2, -1, 2};
    std::cout << shortestSubarray(t4, 3) << std::endl;
    return 0;
}
