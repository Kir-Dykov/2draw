//returns number that is on margin of double precision to number d
//that is, d+=epsilon(d) changes actual value of d, but d+=0.5*epsilon(d) already doesn't
//if number is too close to zero, (such that it's precision limit 
//cannot be expessed using doubles), functions returns the smalest positive double
double epsilon(const double& d) {
	//the whole function is pure IEEE 754 magic
	//to understand this, read about IEEE 754 double-precision standart

	const unsigned long long int exp_shift     = 0x0340000000000000; //(52Ui64 << 52)
	const unsigned long long int mask_signed   = 0xFFF0000000000000; // 12 1's and 52 0's
	const unsigned long long int mask_unsigned = 0x7FF0000000000000; // one 0, 11 1's, 52 0's
	const unsigned long long int minimal       = 0x0010000000000000; // minimal strictly positive double

	unsigned long long int magic = *((unsigned long long int*)&d); // convert double to raw ones and zeros

	if ((magic & mask_unsigned) <= exp_shift) // exponent is too small, so substraction of exp_shift is i
		return *((double*)&minimal);

	magic = (magic & mask_signed) - exp_shift; // diskard mantissa, lower exponent by 52
	return *((double*)&magic);
}