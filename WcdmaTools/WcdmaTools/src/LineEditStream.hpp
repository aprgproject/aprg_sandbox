#pragma once

#include <ostream>
#include <streambuf>
#include <string>

class QTextEdit;

namespace wcdmaToolsGui
{

class LineEditStream : public std::basic_streambuf<char>
{
public:
    LineEditStream(std::ostream &stream, QTextEdit* text_edit);
    ~LineEditStream();

protected:
    //virtual int_type overflow(int_type v);
    //virtual std::streamsize xsputn(const char *p, std::streamsize n);

private:
    std::ostream & m_stream;
    std::streambuf * m_oldStreamBuffer;
    std::string m_string;
    QTextEdit* log_window;
};

}
