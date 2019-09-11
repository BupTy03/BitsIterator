#pragma once
#ifndef OSTREAM_BITS_ITERATOR
#define OSTREAM_BITS_ITERATOR

#include <ostream>
#include <cassert>

class OstreamBitsIterator;
void flush(OstreamBitsIterator& it);

class OstreamBitsIterator
{
	class reference;
	friend reference;
public:
	static constexpr int BITS_IN_BYTE = 8;

	explicit OstreamBitsIterator(std::ostream& os) : stream_{ &os } { }

	OstreamBitsIterator& operator++()
	{
		++currBitIndex_;
		if (currBitIndex_ >= 8) {
			if (stream_ == nullptr) {
				return *this;
			}

			stream_->write(reinterpret_cast<char*>(&currByte_), 1);
			if (!(*stream_)) {
				stream_ = nullptr;
				return *this;
			}

			currByte_ = 0;
			currBitIndex_ = 0;
		}
		return *this;
	}
	OstreamBitsIterator operator++(int) { auto retval = *this; ++(*this); return retval; }

	bool operator==(OstreamBitsIterator other) const
	{
		if (stream_ == nullptr || other.stream_ == nullptr) {
			return stream_ == other.stream_;
		}

		return stream_->tellp() == other.stream_->tellp() && currBitIndex_ == other.currBitIndex_;
	}
	bool operator!=(OstreamBitsIterator other) const { return !(*this == other); }

	reference operator*() { return reference(this); }

	void flush() 
	{
		if (stream_ != nullptr && (*stream_) && currBitIndex_ > 0) {
			stream_->write(reinterpret_cast<char*>(&currByte_), 1);
		}
	}

private:
	class reference {
		friend OstreamBitsIterator;
	public:
		reference& operator=(bool value) 
		{ 
			context_->currByte_ |= (value << (BITS_IN_BYTE - context_->currBitIndex_ - 1));
			return *this;
		}

	private:
		explicit reference(OstreamBitsIterator* context) : context_{ context } { assert(context_ != nullptr); }
		OstreamBitsIterator* context_ = nullptr;
	};

private:
	std::ostream* stream_ = nullptr;
	std::uint8_t currByte_ = 0;
	std::uint8_t currBitIndex_ = 0;
};

void flush(OstreamBitsIterator& it) { it.flush(); }


#endif // !OSTREAM_BITS_ITERATOR