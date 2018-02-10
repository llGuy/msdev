#pragma once
//non-significant function used in some of the derived classes of RSValue
inline unsigned int Power(int num,int exp) {
	if(exp == 0) return 1;
	if(exp == 1) return num;
	if(exp > 1) {
		//creates int result
		unsigned int result = 1;
		for(int j = 0; j < exp; j++) {
			//result is multiplied by the original number input
			result = result * num;
		}
		return result;
	}
	else return 1;
}

inline unsigned int FindNumDigits(unsigned int input) {
	unsigned int count = 0;
	while(input != 0) {
		input /= 10;
		count++;
	}
	return count;
}

inline std::string ConvertIntToString(unsigned int num) {
	std::string result;
	unsigned int NumOfDigits = FindNumDigits(num);
	char *arrayOfChar = new char[NumOfDigits];
	for(unsigned int digit = 0; digit < NumOfDigits; digit++) {
		arrayOfChar[digit] = (char)num % 10 + 48;
		num /= 10;
	}
	for(unsigned int digit = NumOfDigits; digit > 0; digit--) {
		result += arrayOfChar[digit - 1];
	}
	return result;
}
inline unsigned int CalculateStrTOInt(std::string inputValue) {
	unsigned int _lengthOfNum = inputValue.length();
	unsigned int _result = 0;
	for(unsigned int _digitOfNum = 0; _digitOfNum < _lengthOfNum; _digitOfNum++)
		_result += (int)(inputValue[_digitOfNum] - 48) * Power(10,_lengthOfNum - _digitOfNum - 1);
	return _result;
}