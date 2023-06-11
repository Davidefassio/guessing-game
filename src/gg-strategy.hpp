#pragma once

#include "Utils.hpp"

class Results
{
public:
    Results(std::uint64_t s, std::uint64_t p) : s(s), p(p) {}

    friend bool operator==(const Results& lhs, const Results& rhs)
    {
        return lhs.s == rhs.s && lhs.p == rhs.p;
    }

public:
    std::uint64_t s;
    std::uint64_t p;
};

inline bool verify_legality(const Mat64i& perms, std::vector<std::uint8_t>& occ, std::uint64_t word, std::uint64_t prev, Results pres)
{
    // Set occ all to zeros
    std::memset(occ.data(), 0, occ.size() * sizeof(std::uint8_t));

    Results res{ 0, 0 };

    for (std::uint64_t i = 0; i < perms.cols(); ++i)
        ++occ[perms.get(prev, i)];

    for (std::uint64_t i = 0; i < perms.cols(); ++i)
    {
        if (perms.get(word, i) == perms.get(prev, i))
            ++res.p;
        else if (occ[perms.get(word, i)])
            ++res.s;
    }

    return res == pres;
}

inline Results get_results(const Mat64i& perms, std::uint64_t n, std::uint64_t word, std::uint64_t corr)
{
    std::vector<std::uint64_t> occ(n, 0);
    Results res{ 0, 0 };

    for (std::uint64_t i = 0; i < perms.cols(); ++i)
        ++occ[perms.get(corr, i)];

    for (std::uint64_t i = 0; i < perms.cols(); ++i)
    {
        if (perms.get(word, i) == perms.get(corr, i))
            ++res.p;
        else if (occ[perms.get(word, i)])
            ++res.s;
    }

    return res;
}
