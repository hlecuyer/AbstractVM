
class Int8 : IOperand
{

private:
	char			_value;
	int				_precision;
	std::string 	_type;

public:
	Int8();
	Int8(Int8 & const);
	Int8& operator=(Int8 const &);
	~Int8();
	int getPrecision( void ) const;
	eOperandType getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;
	std::string const & toString( void ) const;
	~IOperand( void ) {}
	
};
