#pragma once

#include "../Include/Winheaders.h"
#include <string>

namespace blackbone
{

class Utils
{
public:
    /// <summary>
    /// Convert UTF-8 string to wide char one
    /// </summary>
    /// <param name="str">UTF-8 string</param>
    /// <returns>wide char string</returns>
    BLACKBONE_API static std::wstring UTF8ToWstring( const std::string& str );

    /// <summary>
    /// Convert wide string to UTF-8
    /// </summary>
    /// <param name="str">UTF-8 string</param>
    /// <returns>wide char string</returns>
    BLACKBONE_API static std::string WstringToUTF8( const std::wstring& str );

    /// <summary>
    /// Convert ANSI string to wide char one
    /// </summary>
    /// <param name="input">ANSI string.</param>
    /// <param name="locale">String locale</param>
    /// <returns>wide char string</returns>
    BLACKBONE_API static std::wstring AnsiToWstring( const std::string& input, DWORD locale = CP_ACP );

    /// <summary>
    /// Convert wide char string to ANSI one
    /// </summary>
    /// <param name="input">wide char string.</param>
    /// <param name="locale">String locale</param>
    /// <returns>ANSI string</returns>
    BLACKBONE_API static std::string WstringToAnsi( const std::wstring& input, DWORD locale = CP_ACP );

    /// <summary>
    /// Get filename from full-qualified path
    /// </summary>
    /// <param name="path">File path</param>
    /// <returns>Filename</returns>
    BLACKBONE_API static std::wstring StripPath( const std::wstring& path );

    /// <summary>
    /// Get parent directory
    /// </summary>
    /// <param name="path">File path</param>
    /// <returns>Parent directory</returns>
    BLACKBONE_API static std::wstring GetParent( const std::wstring& path );

    /// <summary>
    /// Get current process exe file directory
    /// </summary>
    /// <returns>Exe directory</returns>
    BLACKBONE_API static std::wstring GetExeDirectory();

    /// <summary>
    /// Cast string characters to lower case
    /// </summary>
    /// <param name="str">Source string.</param>
    /// <returns>Result string</returns>
    BLACKBONE_API static std::wstring ToLower( const std::wstring& str );

    /// <summary>
    /// Generate random alpha-numeric string
    /// </summary>
    /// <param name="length">Desired length. 0 - random length from 5 to 15</param>
    /// <returns>Generated string</returns>
    BLACKBONE_API static std::wstring RandomANString( int length = 0 );

    /// <summary>
    /// Get system error description
    /// </summary>
    /// <param name="code">The code.</param>
    /// <returns>Error message</returns>
    BLACKBONE_API static std::wstring GetErrorDescription( NTSTATUS code );

    /// <summary>
    /// Check if file exists
    /// </summary>
    /// <param name="path">Full-qualified file path</param>
    /// <returns>true if exists</returns>
    BLACKBONE_API static bool FileExists( const std::wstring& path );
};


/// <summary>
/// std::mutex alternative
/// </summary>
class CriticalSection
{
public:
    BLACKBONE_API CriticalSection()
    {
        InitializeCriticalSection( &_native );
    }

    BLACKBONE_API  ~CriticalSection()
    {
        DeleteCriticalSection( &_native );
    }

    BLACKBONE_API void lock()
    {
        EnterCriticalSection( &_native );
    }

    BLACKBONE_API void unlock()
    {
        LeaveCriticalSection( &_native );
    }

private:
    CRITICAL_SECTION _native;
};


/// <summary>
/// std::lock_guard alternative
/// </summary>
class CSLock
{
public:
    BLACKBONE_API CSLock( CriticalSection& cs )
        : _cs( cs ) 
    {
        cs.lock();
    }

    BLACKBONE_API ~CSLock()
    {
        _cs.unlock();
    }

private:
    CSLock( const CSLock& ) = delete;
    CSLock& operator = ( const CSLock& ) = delete;

private:
    CriticalSection& _cs;
};

}