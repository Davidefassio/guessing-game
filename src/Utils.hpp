#pragma once

#include "Mat.hpp"
#include "combinatorics.hpp"

#include <cstdint>
#include <vector>
#include <numeric>

namespace Utils 
{
	inline std::uint64_t factorial(std::uint64_t n)
	{
		std::uint64_t res = 1;
		for (std::uint64_t i = 2; i <= n; ++i)
			res *= i;
		return res;
	}

	inline std::uint64_t disposition(std::uint64_t n, std::uint64_t l)
	{
		std::uint64_t stop = n - l;
		if (stop == 0)
			stop = 1;

		std::uint64_t res = 1;
		for (std::uint64_t i = n; i > stop; --i)
			res *= i;
		return res;
	}

	inline Mat64i create_disposition(std::uint64_t n, std::uint64_t l)
	{
		Mat64i res(disposition(n, l), l);
		std::uint64_t r = 0, c = 0;

		std::vector<std::uint64_t> vec(n);
		std::iota(vec.begin(), vec.end(), 0);

		for_each_permutation(vec.begin(), vec.begin() + l, vec.end(),
			[&](auto first, auto last)
			{
				c = 0;
				for (; first != last; ++first)
					res.set(r, c++, *first);
				++r;
				return false;
			});

		return res;
	}
}