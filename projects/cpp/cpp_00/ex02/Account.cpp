#include "Account.hpp"
#include <iostream>
#include <ctime>

Account::Account( int initial_deposit ) : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
	Account::_nbAccounts++;
	Account::_totalAmount += _amount;
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "created" << std::endl;
}
Account::~Account( void )
{
	Account::_nbAccounts--; //Зачем?
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "closed" << std::endl;
}
Account::Account( void ) : _accountIndex(_nbAccounts) , _amount(0), _nbDeposits(0), _nbWithdrawals(0)
{
	Account::_nbAccounts++;
}

int	Account::getNbAccounts( void )
{
	return Account::_nbAccounts;
}

int	Account::getTotalAmount( void )
{
	return Account::_totalAmount;
}
int	Account::getNbDeposits( void )
{
	return Account::_totalNbDeposits;
}
int	Account::getNbWithdrawals( void )
{
	return Account::_totalNbWithdrawals;
}
void	Account::displayAccountsInfos( void )
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts() << ";";
	std::cout << "total:" << Account::getTotalAmount() << ";";
	std::cout << "deposits:" << Account::getNbDeposits() << ";";
	std::cout << "withdrawals:" << Account::getNbWithdrawals() << std::endl;

}

void	Account::_displayTimestamp( void )
{
	std::time_t date;
	struct tm *date_time;

	std::time(&date);
	date_time = std::localtime(&date);
	std::cout	<< "[" << date_time->tm_year + 1900;
	if (date_time->tm_mon < 10)
		std::cout << "0";
	std::cout << (date_time->tm_mon + 1);
	if (date_time->tm_mday < 10)
		std::cout << "0";
	std::cout << (date_time->tm_mday) << "_";
	if (date_time->tm_hour < 10)
		std::cout << "0";
	std::cout << (date_time->tm_hour);
	if (date_time->tm_min < 10)
		std::cout << "0";
	std::cout << (date_time->tm_min);
	if (date_time->tm_sec < 10)
		std::cout << "0";
	std::cout << (date_time->tm_sec) << "] ";
}

void	Account::makeDeposit( int deposit )
{
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	std::cout << "deposit:" << deposit << ";";
	if (deposit > 0)
	{
		_amount += deposit;
		_nbDeposits += 1;
		Account::_totalNbDeposits += 1;
		Account::_totalAmount += deposit;
	}
	std::cout << "amount:" << _amount << ";";
	std::cout << "nb_deposits:" << _nbDeposits << std::endl;
}
bool	Account::makeWithdrawal( int withdrawal )
{
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	
	if (withdrawal < _amount)
	{
		std::cout << "withdrawal:" << withdrawal << ";";
		if (withdrawal > 0)
		{
			_amount -= withdrawal;
			_nbWithdrawals += 1;
			Account::_totalNbWithdrawals += 1;
			Account::_totalAmount -= withdrawal;
		}
		std::cout << "amount:" << _amount << ";";
		std::cout << "nb_withdrawals:" << _nbWithdrawals << std::endl;
	}
	else 
	{
		std::cout << "withdrawal:refused" << std::endl;
		return false;
	}
	return true;
}

int		Account::checkAmount( void ) const
{
	return _amount;
}

void	Account::displayStatus( void ) const
{
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "deposits:" << _nbDeposits << ";";
	std::cout << "withdrawals:" << _nbWithdrawals << std::endl;

}

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;