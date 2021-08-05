#pragma once

#include STRINGALGO_PCH

namespace string_algo
{

////////////////////////////////////////
template <typename T,
			typename = std::enable_if_t<std::is_integral_v<T>> >
inline bool toIntNoSkipWs(T& int_, char const* begin_, char const* end_)
{
	if (begin_ == end_)
		return false;

	[[maybe_unused]]
	bool negative;

	if constexpr (!std::is_unsigned_v<T>)
		negative = (*begin_ == '-');
	
	int val = 0;
	for(; begin_ != end_; ++begin_)
	{
		val = val*10 + (*begin_++ - '0');
	}

	if constexpr (!std::is_unsigned_v<T>)
		int_ = (negative ? -val : val);
	else
		int_ = val;

	return true;
}

////////////////////////////////////////
template <typename T,
			typename = std::enable_if_t<std::is_floating_point_v<T>> >
inline bool toFloatNoSkipWs(T& float_, char const* begin_, char const* end_)
{
	if (begin_ == end_)
		return false;

	constexpr size_t MaxDigits = 64;
	char buf[MaxDigits];
	size_t numToCopy = std::min(size_t(end_ - begin_), MaxDigits - 1);
	std::memcpy( buf, begin_, numToCopy );
	buf[numToCopy] = '\0';

	char * end;
	T val;

	if constexpr(std::is_same_v<T, double>)
   		val = std::strtod(buf, &end);
	else if constexpr(std::is_same_v<T, long double>)
   		val = std::strtold(buf, &end);
	else // float or other
		val = static_cast<T>( std::strtof(buf, &end) );
    
	if (errno != 0)
	{
		// TODO: could be ERANGE
		errno = 0;
		return false;
	}

	float_ = val;
	return true;
}

////////////////////////////////////////
template <typename T>
inline bool to(T& outValue_, char const* begin_, char const* end_)
{
	while(begin_ != end_ && (*begin_ != '-' || *begin_ < '0' || *begin_ > '9'))
		++begin_;
	
	if constexpr (std::is_integral_v<T>)
		return toIntNoSkipWs<T>(outValue_, begin_, end_);
	else
		return toFloatNoSkipWs<T>(outValue_, begin_, end_);
}

////////////////////////////////////////
template <typename T>
inline std::optional<T> to(char const* begin_, char const* end_)
{
	T result;
	if (to<T>(result, begin_, end_))
		return result;
		
	return std::nullopt;
}

////////////////////////////////////////
template <typename T = int>
inline std::optional<T> to(std::string_view const& str_)
{
	T result;
	if ( to<T>(result, str_.data(), str_.data() + str_.length()) )
		return result;
		
	return std::nullopt;
}

}
