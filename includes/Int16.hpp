class Int16 : IOperand
{

private:
	int				_value;
	int				_precision;
	std::string 	_type;

public:
	Int16();
	Int16(Int16 & const);
	Int16& operator=(Int16 const &);
	~Int16();
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