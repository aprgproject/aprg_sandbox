#include <LineEditStream.hpp>

#include <qtextedit.h>

namespace tcomToolsGui
{

LineEditStream::LineEditStream(std::ostream & stream, QTextEdit * text_edit)
    : m_stream(stream)
{
    log_window = text_edit;
    //m_oldStreamBuffer = stream.rdbuf();
    //stream.rdbuf(this);
}

LineEditStream::~LineEditStream()
{
    //if (!m_string.empty()){log_window->append(m_string.c_str());}
    //m_stream.rdbuf(m_oldStreamBuffer);
}
/*
std::basic_streambuf<char>::int_type LineEditStream::overflow(int_type v)
{
    if (v == '\n')
    {
        log_window->append(m_string.c_str());
        m_string.erase(m_string.begin(), m_string.end());
    }
    else
    {
        m_string += v;
    }
    return v;
}

std::streamsize LineEditStream::xsputn(const char *p, std::streamsize n)
{
    m_string.append(p, p + n);
    unsigned int pos = 0;
    while (pos != std::string::npos)
    {
        pos = m_string.find('\n');
        if (pos != std::string::npos)
        {
            std::string temp(m_string.begin(), m_string.begin() + pos);
            log_window->append(temp.c_str());
            m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
        }
    }
    return n;
}
*/
}


