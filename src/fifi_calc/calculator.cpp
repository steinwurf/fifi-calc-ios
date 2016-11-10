// Copyright (c) 2016 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#include "calculator.hpp"

#include <map>
#include <string>
#include <memory>

#include <fifi/optimal_prime.hpp>
#include <fifi/simple_online.hpp>

namespace fifi_calc
{
class calculator::impl
{
private:

	struct stack_interface
	{
		virtual uint32_t add(uint32_t a, uint32_t b) const = 0;
		virtual uint32_t subtract(uint32_t a, uint32_t b) const = 0;
		virtual uint32_t divide(uint32_t a, uint32_t b) const = 0;
		virtual uint32_t multiply(uint32_t a, uint32_t b) const = 0;
		virtual uint32_t invert(uint32_t a) const = 0;
		virtual uint32_t max_value() const = 0;

		virtual ~stack_interface()
		{}
	};

    template<class Field>
	class stack : public stack_interface
	{
	public:
		uint32_t add(uint32_t a, uint32_t b) const
		{
			return m_field.add(a, b);
		}

		uint32_t subtract(uint32_t a, uint32_t b) const
		{
			return m_field.subtract(a, b);
		}
		
		uint32_t divide(uint32_t a, uint32_t b) const
		{
			return m_field.divide(a, b);
		}
		
		uint32_t multiply(uint32_t a, uint32_t b) const
		{
			return m_field.multiply(a, b);
		}
		
		uint32_t invert(uint32_t a) const
		{
			return m_field.invert(a);
		}

		uint32_t max_value() const
		{
			return Field::field_type::max_value;
		}

		Field m_field;
	};

public:

    impl()
    	: m_field("binary2")
    {
    	stacks["binary2"] = std::make_shared<stack<fifi::simple_online<fifi::binary>>>();
        stacks["binary4"] = std::make_shared<stack<fifi::simple_online<fifi::binary4>>>();
        stacks["binary8"] = std::make_shared<stack<fifi::simple_online<fifi::binary8>>>();
        stacks["binary16"] = std::make_shared<stack<fifi::simple_online<fifi::binary16>>>();
        stacks["prime2325"] = std::make_shared<stack<fifi::optimal_prime<fifi::prime2325>>>();
    }

    uint32_t add(uint32_t a, uint32_t b) const
    {
        return stacks.at(m_field)->add(a, b);
    }

	uint32_t subtract(uint32_t a, uint32_t b) const
	{
        return stacks.at(m_field)->subtract(a, b);
	}
	
	uint32_t divide(uint32_t a, uint32_t b) const
	{
        return stacks.at(m_field)->divide(a, b);
	}
	
	uint32_t multiply(uint32_t a, uint32_t b) const
	{
        return stacks.at(m_field)->multiply(a, b);
	}
	
	uint32_t invert(uint32_t a) const
	{
        return stacks.at(m_field)->invert(a);
	}
	
	uint32_t max_value() const
	{
        return stacks.at(m_field)->max_value();
	}

	std::string field() const
	{
		return m_field;
	}

	void set_field(const std::string& field)
	{
		m_field = field;
	}

	std::string m_field;
    std::map<std::string, std::shared_ptr<stack_interface>> stacks;
};


calculator::calculator() :
    m_impl(new impl())
{ }

// The destructor must be defined in the cpp file, since the default
// destructor would be inlined in the header and the impl class would
// be incomplete.
calculator::~calculator()
{ }

uint32_t calculator::add(uint32_t a, uint32_t b) const
{
    return m_impl->add(a, b);
}

uint32_t calculator::subtract(uint32_t a, uint32_t b) const
{
	return m_impl->subtract(a, b);
}

uint32_t calculator::multiply(uint32_t a, uint32_t b) const
{
	return m_impl->multiply(a, b);
}

uint32_t calculator::divide(uint32_t a, uint32_t b) const
{
	return m_impl->divide(a, b);
}

uint32_t calculator::invert(uint32_t a) const
{
	return m_impl->invert(a);
}

uint32_t calculator::max_value() const
{
	return m_impl->max_value();
}

std::string calculator::field() const
{
	return m_impl->field();
}

void calculator::set_field(const std::string& field)
{
	return m_impl->set_field(field);
}
}
