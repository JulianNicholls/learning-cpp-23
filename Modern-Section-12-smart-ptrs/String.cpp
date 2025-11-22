#include <iostream>

#include "String.h"

String::String(const String &arg)
{
	// Make a shallow copy of the argument
	size_ = arg.size_;
	data_ = arg.data_;
	counter_ = arg.counter_;

	// Any other code needed to configure the new object
	++*counter_; // "this" has been bound - increment the counter
	cout << "Copy constructor: data = " << static_cast<void *>(data_) << ", counter = " << counter_ << ", count = " << *counter_ << endl;
}

String &String::operator=(const String &other)
{
	cout << "Assigned-to object: data = " << (void *)data_ << ", counter = " << counter_ << ", count = " << *counter_ << endl;

	String temp(other);

	swap(*this, temp);

	return *this;
}

// Move constructor
String::String(String &&arg) noexcept
{
	cout << "Move constructor called" << endl;
	data_ = arg.data_;
	size_ = arg.size_;
	counter_ = arg.counter_; // Shallow copy of counter pointer

	// Prevent double deletion
	arg.data_ = nullptr;
	arg.counter_ = nullptr;
}

String &String::operator=(String &&arg) noexcept
{
	cout << "Move assignment operator called" << endl;
	String temp(std::move(arg)); // Call move constructor
	swap(*this, temp);					 // Exchange our data with temp's data

	return *this;
}

void String::print() const
{
	cout << "size = " << size_;
	cout << ", data address " << static_cast<void *>(data_);
	cout << ", counter " << static_cast<void *>(counter_);
	if (counter_)
		cout << ", count = " << *counter_;
	cout << endl;
}
