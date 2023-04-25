#include "ModuleTest.hpp"

ModuleTest::ModuleTest()
    : m_database(),
      m_findings(),
      m_terms(),
      m_termTranslator(MT_FILE_READER_TEST_FILE, m_findings, m_terms),
      m_termAnalyzer(m_terms, m_database, m_findings) {}

void ModuleTest::processFile() {
    m_termTranslator.readFile();
    m_termAnalyzer.analyze();
    printTerms(m_terms);
    m_findings.printFindings(std::cout);
    // m_database.print(cout);
}
