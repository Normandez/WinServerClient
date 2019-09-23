// main.cpp

#include <QApplication>

#include <exception>
#include <fstream>

#include "QClient.h"

int main( int argc, char* argv[] )
{
	int ret = 0;
	std::ofstream exception_strm( "exception.log", std::ios_base::out | std::ios_base::trunc );		// Info about handled exceptions
	if( !exception_strm.is_open() )
	{
		printf("exception log file not opened");
	}

	try
	{
		QApplication app( argc, argv );

		QClient client(&app);
		client.show();

		ret = app.exec();
	}
	catch( const std::bad_alloc& bad_alloc_ex )
	{
		exception_strm << "MAIN: bad_alloc exception handled: " << bad_alloc_ex.what() << std::endl;
		exception_strm.close();

		return 1;
	}
	catch( const std::bad_exception& bad_exception_ex )
	{
		exception_strm << "MAIN: bad_exception exception handled: " << bad_exception_ex.what() << std::endl;
		exception_strm.close();

		return 2;
	}
	catch( const std::logic_error& logic_error_ex )
	{
		exception_strm << "MAIN: logic_error exception handled: " << logic_error_ex.what() << std::endl;
		exception_strm.close();

		return 3;
	}
	catch( const std::runtime_error& runtime_error_ex )
	{
		exception_strm << "MAIN: runtime_error exception handled: " << runtime_error_ex.what() << std::endl;
		exception_strm.close();

		return 4;
	}
	catch ( const std::exception& common_ex )
	{
		exception_strm << "MAIN: common exception handled: " << common_ex.what() << std::endl;
		exception_strm.close();

		return 5;
	}
	catch(...)
	{
		exception_strm << "MAIN: unknown exception handled" << std::endl;
		exception_strm.close();

		return 6;
	}

	exception_strm << "no_exceptions" << std::endl;
	exception_strm.close();
	return ret;
}
