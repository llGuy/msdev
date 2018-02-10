#pragma once
#include "Misc.h"

#define	XOR(a,b) a ^ b
#define AND(a,b) a & b
#define OR(a,b) a | b
#define LSHFT(a,b) a << b
#define RSHFT(a,b) a >> b

class Encryption {
public:
	explicit Encryption(void) = default;
	~Encryption(void) {};

	virtual std::string& Encrypt(void) = 0;
};

class XOR_Encryption : public Encryption {
private:
	std::string _key = "";
	std::string _rsString = "";		//text or variable to encrypt
	std::string _valueOfRSV = "";
	std::string _destination = "";
	std::string _encryptedString = "";
	/*void ExtractRSString(const std::string &text) {
		size_t _index = 12;
		while(text[_index] != ',') {
			_rsString += text[_index];
			_index++;
		}
	}*/
	void GetValueOfInput(const std::string &input) {
		auto _getValueOfConst = [&](void)->void {
			size_t _index = 1;
			while(input[_index] != '\"') {
				_valueOfRSV += input[_index];
				_index++;
			}
		};
		auto _getValueOfVar = [&](void)->void {
			_valueOfRSV = VList::listStr.FindNodeStr(input,
				VList::listStr._head)->_value;
		}; 
		if(input[0] == '\"') _getValueOfConst();
		else _getValueOfVar();
	}
	void GetEncryptedString(void) {
		_encryptedString = _valueOfRSV;
		for(size_t _indexRSV = 0,_indexKey = 0; _indexRSV < _valueOfRSV.length();
			_indexRSV++, _indexKey = (_indexKey == _key.length()) ? 0 : _indexKey + 1) {
			//checks if indexKey is = to the length of the key
			//if so, it will set it so 0, otherwise, increment it
			_encryptedString[_indexRSV] = XOR((size_t)_encryptedString[_indexRSV],_key[_indexKey]);
		}
	}
	std::string& GetDestination(void) {
		Variable<std::string>* _varDestination =VList::listStr.FindNodeStr(_destination,
			VList::listStr._head);
		std::string& _destString = _varDestination->_value;
		_varDestination->_isEncrypted = true;
		return _destString;
	}
	/*void GetKey(const std::string &input) {
		size_t _index = _rsString.length() + 2;
		while(input[_index] != ')') {
			_key += input[_index];
			_index++;
		}
	}*/
public:
	explicit XOR_Encryption(void) = default;
	explicit XOR_Encryption(const std::string &textToEnc,const std::string &key,const std::string &destination)
		: _key(key),_rsString(textToEnc),_destination(destination) {};
	~XOR_Encryption(void) {};

	std::string& Encrypt(void) override { GetDestination() = _encryptedString; }
};

class LSB_Encryption : public Encryption {
public:
	explicit LSB_Encryption(void) = default;
	explicit LSB_Encryption(std::string &temp) {};		//constructor takes arguments
};