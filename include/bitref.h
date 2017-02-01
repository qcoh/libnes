#pragma once

template <typename T, typename S, int I>
class BitRef {
public:
	BitRef(T& t) : m_ref{t} {}
	~BitRef() = default;

	BitRef(const BitRef&) = delete;
	BitRef& operator=(const BitRef&) = delete;
	BitRef(BitRef&&) = delete;
	BitRef& operator=(BitRef&&) = delete;

	operator bool() const { return ((m_ref >> I) & 1) != 0; }
	BitRef& operator=(const bool& rhs) {
		m_ref = static_cast<S>((m_ref & (~(1 << I))) | (rhs << I));
		return *this;
	}

private:
	T& m_ref;
};
