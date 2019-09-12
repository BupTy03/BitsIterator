#pragma once
#ifndef OSTREAM_BITS_ITERATOR
#define OSTREAM_BITS_ITERATOR

#include <ostream>
#include <cassert>

class OstreamBitsIterator;
static void flush(OstreamBitsIterator& it);
static std::uint8_t current_bit(const OstreamBitsIterator& it);

namespace OstreamBitsIteratorImpl {
	class reference_type {
		friend OstreamBitsIterator;
	public:
		reference_type& operator=(bool value);

	private:
		explicit reference_type(OstreamBitsIterator* context) : context_{ context } { assert(context_ != nullptr); }
		OstreamBitsIterator* context_ = nullptr;
	};
}

class OstreamBitsIterator : public std::iterator<std::output_iterator_tag, bool, std::ptrdiff_t, bool*, OstreamBitsIteratorImpl::reference_type>
{
	friend OstreamBitsIteratorImpl::reference_type;
public:
	static constexpr int BITS_IN_BYTE = 8;

	explicit OstreamBitsIterator(std::ostream& os) : stream_{ &os } { }

	void flush()
	{
		if (stream_ != nullptr && (*stream_) && currBitIndex_ > 0) {
			stream_->write(reinterpret_cast<char*>(&currByte_), 1);
		}
	}
	std::uint8_t currentBit() const { return currBitIndex_; }

	OstreamBitsIterator& operator++()
	{
		++currBitIndex_;
		if (currBitIndex_ >= BITS_IN_BYTE) {
			if (stream_ == nullptr) {
				return *this;
			}

			stream_->write(reinterpret_cast<char*>(&currByte_), 1);
			currByte_ = 0;
			currBitIndex_ = 0;
			if (!(*stream_)) {
				stream_ = nullptr;
				return *this;
			}
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

private:
	std::ostream* stream_ = nullptr;
	std::uint8_t currByte_ = 0;
	std::uint8_t currBitIndex_ = 0;
};

void flush(OstreamBitsIterator& it) { it.flush(); }
std::uint8_t current_bit(const OstreamBitsIterator& it) { return it.currentBit(); }

namespace OstreamBitsIteratorImpl {
	reference_type& reference_type::operator=(bool value)
	{
		context_->currByte_ |= (value << (OstreamBitsIterator::BITS_IN_BYTE - context_->currBitIndex_ - 1));
		return *this;
	}
}

#if 0

#include <ostream>
#include <cassert>

class OstreamBitsIterator;
void flush(OstreamBitsIterator& it);
std::uint8_t current_bit(const OstreamBitsIterator& it);

namespace OstreamBitsIteratorImpl {
	class reference_type {
		friend OstreamBitsIterator;
	public:
		reference_type& operator=(bool value);

	private:
		explicit reference_type(OstreamBitsIterator* context) : context_{ context } { assert(context_ != nullptr); }
		OstreamBitsIterator* context_ = nullptr;
	};
}

class OstreamBitsIterator : public std::iterator<std::output_iterator_tag, bool, std::ptrdiff_t, bool*, OstreamBitsIteratorImpl::reference_type>
{
	friend OstreamBitsIteratorImpl::reference_type;
public:
	static constexpr int BITS_IN_BYTE = 8;

	explicit OstreamBitsIterator(std::ostream& os) : stream_{ &os } { }

	void flush()
	{
		if (stream_ != nullptr && (*stream_) && currBitIndex_ > 0) {
			stream_->write(reinterpret_cast<char*>(&currByte_), 1);
		}
	}
	std::uint8_t currentBit() const { return currBitIndex_; }

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

private:
	std::ostream* stream_ = nullptr;
	std::uint8_t currByte_ = 0;
	std::uint8_t currBitIndex_ = 0;
};

void flush(OstreamBitsIterator& it) { it.flush(); }
std::uint8_t current_bit(const OstreamBitsIterator& it) { return it.currentBit(); }

namespace OstreamBitsIteratorImpl {
	reference_type& reference_type::operator=(bool value)
	{
		context_->currByte_ |= (value << (OstreamBitsIterator::BITS_IN_BYTE - context_->currBitIndex_ - 1));
		return *this;
	}
}

#endif


#endif // !OSTREAM_BITS_ITERATOR