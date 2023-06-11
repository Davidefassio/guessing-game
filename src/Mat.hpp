#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>

template <class T>
class Mat_
{
public:
	// Default constructor
	Mat_() = delete;

	// Base constructor
	Mat_(std::uint64_t row, std::uint64_t col) : row(row), col(col), data(new T[row * col])
	{
	}

	// Copy constructor
	Mat_(const Mat_& other) : row(other.row), col(other.col), data(new T[row * col])
	{
		std::memcpy(data, other.data, row * col * sizeof(T));
	}

	// Move constructor
	Mat_(Mat_&& other) noexcept : row(other.row), col(other.col), data(std::exchange(other.data, nullptr))
	{
	}
	
	// Destructor
	~Mat_()
	{
		delete[] data;
	}

	// Swap specialization
	friend void swap(Mat_& first, Mat_& second) noexcept
	{
		using std::swap;

		swap(first.row, second.row);
		swap(first.col, second.col);
		swap(first.data, second.data);
	}

	// Copy assignment
	Mat_& operator=(Mat_ other)
	{
		swap(*this, other);
		return *this;
	}

	// Move assignment
	Mat_& operator=(Mat_&& other) noexcept
	{
		swap(*this, other);
		return *this;
	}

	// Getter
	T get(std::uint64_t r, std::uint64_t c) const
	{
		return data[r * col + c];
	}

	std::uint64_t rows() const
	{
		return row;
	}

	std::uint64_t cols() const
	{
		return col;
	}

	// Setter
	void set(std::uint64_t r, std::uint64_t c, T value)
	{
		data[r * col + c] = value;
	}

	// Get pointer to underlying data
	T* getPtr(std::uint64_t r = 0, std::uint64_t c = 0)
	{
		return &(data[r * col + c]);
	}

	// Get pointer to underlying data (const version)
	const T* getPtr(std::uint64_t r = 0, std::uint64_t c = 0) const
	{
		return &(data[r * col + c]);
	}

	// Convert to string
	std::string toString() const
	{
		std::stringstream ss{};

		for (std::uint64_t r = 0; r < row; ++r)
		{
			for (std::uint64_t c = 0; c < col; ++c)
				ss << data[r * col + c] << " ";
			ss << "\n";
		}
		return ss.str();
	}

	// Print debug information
	void debug() const
	{
		std::cout << "Rows: " << row << "\n";
		std::cout << "Cols: " << col << "\n";
		std::cout << "Data: "<< "\n";
		for (std::uint64_t r = 0; r < row; ++r)
		{
			for (std::uint64_t c = 0; c < col; ++c)
				std::cout << data[r * col + c] << " ";
			std::cout << "\n";
		}
	}

public:
	// Create a new matrix with all bits set to zero
	static Mat_ zeros(std::uint64_t row, std::uint64_t col)
	{
		Mat_<T> res{ row, col };
		std::memset(res.getPtr(), 0, row * col * sizeof(T));
		return res;
	}

private:
	std::uint64_t row;
	std::uint64_t col;
	T* data;
};

// Typedef
typedef Mat_<int> Mat;

typedef Mat_<std::uint8_t> Mat8i;
typedef Mat_<std::uint16_t> Mat16i;
typedef Mat_<std::uint32_t> Mat32i;
typedef Mat_<std::uint64_t> Mat64i;

typedef Mat_<float> Mat32f;
typedef Mat_<double> Mat64f;