/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Mark Page
**    Michael J. Fromberger
*/

// This class is based on the original MPI library (not NSS, because of license restrictions) with some modifications.
// Some ideas and algorithms are from NSS (Netscape Security Suite). Where they have been used, the function contains a reference note
//
// Note, since September 2011, I believe the MPI homepage is now: http://spinning-yarns.org/michael/mpi/
// The license is as follows
// This software was written by Michael J. Fromberger,
//   http://www.dartmouth.edu/~sting/
//
// See the MPI home page at
//   http://www.dartmouth.edu/~sting/mpi/
//
// This software is in the public domain.  It is entirely free, and you
// may use it and/or redistribute it for whatever purpose you choose;
// however, as free software, it is provided without warranty of any
// kind, not even the implied warranty of merchantability or fitness for
// a particular purpose.

/// \addtogroup clanCore_Math clanCore Math
/// \{

#pragma once

#include "API/Core/System/cl_platform.h"

typedef cl_ubyte32		cl_bigint_digit;
typedef cl_ubyte64		cl_bigint_word;		// Must be twice the size of cl_bigint_digit
typedef unsigned int	cl_bigint_size;

/// \brief Big Integer class
///
/// ** Designed to clear internal memory after use **
///
/// \xmlonly !group=Core/Math! !header=core.h! \endxmlonly
class CL_BigInt
{
/// \name Construction
/// \{
public:
	/// \brief Constructs a big integer (initialised to zero)
	CL_BigInt();

	/// \brief Constructs a big integer (initialised to zero)
	CL_BigInt(unsigned int precision_digits);

	/// \brief Copy constructor
	CL_BigInt(const CL_BigInt &other);

	/// \brief Destructor
	~CL_BigInt();

	CL_BigInt &operator=(const CL_BigInt& other);

/// \}
/// \name Attributes
/// \{

public:

/// \}
/// \name Operations
/// \{

public:
	void read_unsigned_octets( const unsigned char *input_str, unsigned int input_length);

	void zero();

	bool make_prime(cl_bigint_size num_bits);

	// Compare a <=> 0.  Returns <0 if a<0, 0 if a=0, >0 if a>0.
	int cmp_z() const;

	void set_bit(cl_bigint_size bit_number, cl_bigint_size value);

	int significant_bits() const;

	void sieve(const cl_bigint_digit *primes, cl_bigint_size num_primes, std::vector<unsigned char> &sieve);

	// Compute c = a (mod d).  Result will always be 0 <= c < d
	cl_bigint_digit mod_d(cl_bigint_digit d) const;

	// Compute the quotient q = a / d and remainder r = a mod d, for a single digit d.  Respects the sign of its divisor (single digits are unsigned anyway).
	void div_d(cl_bigint_digit d, CL_BigInt *q, cl_bigint_digit *r) const;

	void copy(CL_BigInt *to) const;

	// Compute the sum out_b = this + d, for a single digit d.  Respects the sign of its primary addend (single digits are unsigned anyway).
	void add_d(cl_bigint_digit d, CL_BigInt &out_b) const;

	// Using w as a witness, try pseudo-primality testing based on Fermat's little theorem. 
	// If a is prime, and (w, a) = 1, then w^a == w (mod a).
	// So, we compute z = w^a (mod a) and compare z to w; if they are
	// equal, the test passes and we return true.  Otherwise, we return false.
	bool fermat(cl_bigint_digit w) const;


	// Performs nt iteration of the Miller-Rabin probabilistic primality
	// test on a.  Returns true if the tests pass, false if one fails.
	// If false is returned, the number is definitely composite.  If true
	bool pprime(int nt) const;

	void set(cl_bigint_digit d);

	// Compute c = (a ** b) mod m.  Uses a standard square-and-multiply
	// method with modular reductions at each step. (This is basically the
	// same code as expt(), except for the addition of the reductions)
	//
	// The modular reductions are done using Barrett's algorithm (see reduce() for details)
	void exptmod(const CL_BigInt *b, const CL_BigInt *m, CL_BigInt *c) const;

	// Compute c = a (mod m).  Result will always be 0 <= c < m.
	void mod(const CL_BigInt *m, CL_BigInt *c) const;

	// Compute q = a / b and r = a mod b.  Input parameters may be re-used
	// as output parameters.  If q or r is NULL, that portion of the
	// computation will be discarded (although it will still be computed)
	void div(const CL_BigInt *b, CL_BigInt *q, CL_BigInt *r) const;

	// Compute c = a + b.  All parameters may be identical.
	void add(const CL_BigInt *b, CL_BigInt *c) const;

	void sub(const CL_BigInt *b, CL_BigInt *c) const;

	int cmp(const CL_BigInt *b) const;

	// Compare a <=> d.  Returns <0 if a<d, 0 if a=d, >0 if a>d
	int cmp_d(cl_bigint_digit d) const;

	// Compute the difference b = a - d, for a single digit d.  Respects the sign of its subtrahend (single digits are unsigned anyway).
	void sub_d(cl_bigint_digit d, CL_BigInt *b) const;

	// Compute b = -a.  'a' and 'b' may be identical.
	void neg(CL_BigInt *b) const;

	cl_bigint_size trailing_zeros() const;

	void div_2d(cl_bigint_digit d, CL_BigInt *q, CL_BigInt *r) const;

	void sqrmod(const CL_BigInt *m, CL_BigInt *c) const;
	void sqr(CL_BigInt *b) const;

	// Assigns a random value to a.  This value is generated using the
	// standard C library's rand() function, so it should not be used for
	// cryptographic purposes, but it should be fine for primality testing,
	// since all we really care about there is reasonable statistical
	// properties.
	// As many digits as a currently has are filled with random digits.  */
	void random();

	// Exchange mp1 and mp2 without allocating any intermediate memory
	// (well, unless you count the stack space needed for this call and the
	// locals it creates...).  This cannot fail.
	void exch(CL_BigInt *mp2);

	// Compute c = a * b.  All parameters may be identical.
	void mul(const CL_BigInt *b, CL_BigInt *c) const;

	// Compute c = a^-1 (mod m), if there is an inverse for a (mod m).
	// This is equivalent to the question of whether (a, m) = 1.  If not,
	// false is returned, and there is no inverse.
	bool invmod(const CL_BigInt *m, CL_BigInt *c) const;

	// Compute g = (a, b) and values x and y satisfying Bezout's identity
	// (that is, ax + by = g).  This uses the extended binary GCD algorithm
	// based on the Stein algorithm used for mp_gcd()
	void xgcd(const CL_BigInt *b, CL_BigInt *g, CL_BigInt *x, CL_BigInt *y) const;

	//  Compute b = |a|.  'a' and 'b' may be identical.
	void abs(CL_BigInt *b) const;

	int iseven() const;

	//  Returns a true (non-zero) value if a is odd, false (zero) otherwise.
	int isodd() const;

	// Compute c = a / 2, disregarding the remainder.
	void div_2(CL_BigInt *c) const;

	void to_unsigned_octets( unsigned char *output_str, unsigned int output_length) const;

	int unsigned_octet_size() const;
/// \}
/// \name Implementation
/// \{
private:

	static const int default_allocated_precision = 64;
	static const int num_bits_in_digit = (8*sizeof(cl_bigint_digit));
	static const int num_bits_in_word = (8*sizeof(cl_bigint_word));
	static const cl_bigint_word digit_radix = 1ULL << (8*sizeof(cl_bigint_digit));
	static const cl_bigint_digit digit_half_radix = 1U << (8*sizeof(cl_bigint_digit) - 1);
	static const cl_bigint_word word_maximim_value = ~0;

	inline cl_bigint_digit internal_carryout(cl_bigint_word w) const
	{
		return w >> num_bits_in_digit;
	}

	inline cl_bigint_digit internal_accum(cl_bigint_word w) const
	{
		return (cl_bigint_digit) w;
	}

	void internal_init_size(cl_bigint_size prec);
	void internal_free();
	void internal_lshd(cl_bigint_size p);
	void internal_pad(cl_bigint_size min);
	void internal_grow(cl_bigint_size min);
	void internal_clamp();
	int internal_ispow2d(cl_bigint_digit d) const;
	void internal_div_2d(cl_bigint_digit d);
	void internal_rshd(cl_bigint_size p);
	int  internal_ispow2() const;
	void internal_mod_2d(cl_bigint_digit d);
	void internal_mul_2d(cl_bigint_digit d);

	// Exchange the data for a and b; (b, a) = (a, b)
	void internal_exch(CL_BigInt *b);

	// Compare |a| <=> d, return 0 if equal, <0 if a<d, >0 if a>d
	int internal_cmp_d(cl_bigint_digit d) const;

	void internal_div_d(cl_bigint_digit d, cl_bigint_digit *r);

	void internal_add_d(cl_bigint_digit d);
	void internal_sub_d(cl_bigint_digit d);
	cl_bigint_digit internal_norm(CL_BigInt *b);
	void internal_sub(const CL_BigInt *b);

	int internal_cmp(const CL_BigInt *b) const;
	void internal_div(CL_BigInt *b);
	void internal_mul_d(cl_bigint_digit d);
	void internal_add(const CL_BigInt *b);
	void internal_mul(const CL_BigInt *b);
	void internal_div_2();
	void internal_mul_2();

	void internal_reduce(const CL_BigInt *m, CL_BigInt *mu);
	void internal_sqr();

	void build_primes();

	bool digits_negative;	// True if the value is negative
	cl_bigint_size digits_alloc;		// How many digits allocated
	cl_bigint_size digits_used;		// How many digits used
	cl_bigint_digit *digits;	// The digits themselves

	static const int prime_tab_size = 6542;
	static cl_bigint_digit prime_tab[prime_tab_size];
	static bool prime_tab_built;

/// \}

};


/// \}

