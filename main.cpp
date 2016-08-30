#include <QCoreApplication>
#include <iostream>
#include <regex>
#include <functional>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	std::string str;
	std::cin >> str;
	std::regex reg("[+]{0,1}[1-9][0-9]{0,17}");
	long double counter(0);
	
	if( std::regex_match(str.begin(), str.end(), reg) )
	{
		str.erase( std::remove_if(str.begin(), str.end(), [&](const char &c){ return ( (c == '+') || (c == '\n') ); }), str.end()  );
		long double inputValue = std::stold( str );
		
		
		std::function<long long( long long, int & )> recursiveCheck =
		        [&]( long long previousValue, int &number )->long long
		{
			++number;
			long long nextValue = previousValue + number;
			
			if( nextValue >= inputValue )
				return nextValue;
			else
				return recursiveCheck( nextValue, number );
		};
		
		
		long long previousValue(0);
		
		forever
		{
			++counter;
			long double nextValue = previousValue + counter;
			
			previousValue = nextValue;
			
			if( nextValue >= inputValue )
				break;
		}
		
//		long long calculatedValue = recursiveCheck( 0, counter );
//		if( calculatedValue != inputValue )
		if( previousValue != inputValue )
			counter = 0;
	}
	
	std::cout << counter << std::endl;
	
	return a.exec();
}
