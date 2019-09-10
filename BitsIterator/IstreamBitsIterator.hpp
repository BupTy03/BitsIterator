#pragma once
#ifndef ISTREAM_BITS_ITERATOR
#define ISTREAM_BITS_ITERATOR

#include <iostream>
#include <cassert>

class IstreamBitsIterator
{
public:
	static constexpr int BITS_IN_BYTE = 8;

	explicit IstreamBitsIterator() {}
	explicit IstreamBitsIterator(std::istream& is) : stream_{ &is }
	{
		if (*stream_) {
			stream_->read(reinterpret_cast<char*>(&currByte_), 1);
		}
		else {
			stream_ = nullptr;
		}
	}

	IstreamBitsIterator& operator++()
	{
		++currBitIndex_;
		if (currBitIndex_ >= 8) {
			currByte_ = 0;
			currBitIndex_ = 0;

			assert(stream_ != nullptr);
			stream_->read(reinterpret_cast<char*>(&currByte_), 1);
			if (is_last_byte()) {
				stream_ = nullptr;
				return *this;
			}
		}
		return *this;
	}
	IstreamBitsIterator operator++(int) { auto retval = *this; ++(*this); return retval; }

	bool operator==(IstreamBitsIterator other) const
	{
		if (stream_ == nullptr || other.stream_ == nullptr) {
			return stream_ == other.stream_;
		}

		return stream_->tellg() == other.stream_->tellg() && currBitIndex_ == other.currBitIndex_;
	}

	bool operator!=(IstreamBitsIterator other) const { return !(*this == other); }

	bool operator*() const { return currByte_ & (1 << (BITS_IN_BYTE - currBitIndex_ - 1)); }

	bool is_last_byte() const { return stream_ == nullptr || !(*stream_); }

private:
	std::istream* stream_ = nullptr;
	std::uint8_t currByte_ = 0;
	std::uint8_t currBitIndex_ = 0;
};


#endif // !ISTREAM_BITS_ITERATOR
