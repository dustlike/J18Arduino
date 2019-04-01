#pragma once



#include <stddef.h>
#include <stdint.h>


template<size_t BUFFER_SIZE_POWER>
class VariableRingBuffer
{
	static constexpr size_t SERIAL_BUFFER_SIZE = 1 << BUFFER_SIZE_POWER;
	
public:
	uint8_t _aucBuffer[SERIAL_BUFFER_SIZE] ;
	volatile size_t _iHead ;
	volatile size_t _iTail ;
	
	VariableRingBuffer() { clear(); }
	void store_char(uint8_t);
	void clear();
	int read_char();
	int available();
	int availableForStore();
	int peek();
	bool isFull();
	
private:
	size_t nextIndex(size_t index)
	{
		return (index + 1) & (SERIAL_BUFFER_SIZE - 1);
	}
};


template<size_t X>
void VariableRingBuffer<X>::store_char(uint8_t c)
{
	size_t i = nextIndex(_iHead);
	
	if ( i != _iTail )
	{
		_aucBuffer[_iHead] = c;
		_iHead = i;
	}
}


template<size_t X>
void VariableRingBuffer<X>::clear()
{
	_iHead = _iTail = 0;
}


template<size_t X>
int VariableRingBuffer<X>::read_char()
{
	if(_iTail == _iHead) return -1;
	
	uint8_t value = _aucBuffer[_iTail];
	_iTail = nextIndex(_iTail);
	
	return value;
}


template<size_t X>
int VariableRingBuffer<X>::available()
{
	return (SERIAL_BUFFER_SIZE + _iHead - _iTail) & (SERIAL_BUFFER_SIZE - 1);
}


template<size_t X>
int VariableRingBuffer<X>::availableForStore()
{
	return (SERIAL_BUFFER_SIZE - 1 - _iHead + _iTail) & (SERIAL_BUFFER_SIZE - 1);
}


template<size_t X>
int VariableRingBuffer<X>::peek()
{
	return (_iTail == _iHead)? -1 : _aucBuffer[_iTail];
}


template<size_t X>
bool VariableRingBuffer<X>::isFull()
{
	return nextIndex(_iHead) == _iTail;
}


//////////////////////////////////////////////////////////////////////////


//64byte version of variable ring buffer.
class RingBuffer : public VariableRingBuffer<6>
{
	//empty body. All methods inherit from VariableRingBuffer
};
