#pragma once

#include "../../../src/CPlusPlus/Analyzer/TermAnalyzer.hpp"
#include "../../../src/CPlusPlus/Database/CPlusPlusDatabase.hpp"
#include "../../../src/CPlusPlus/Findings/Findings.hpp"
#include "../../../src/CPlusPlus/Translator/TermTranslator.hpp"
#include "../../MtDirectoryConstants.hpp"
#include "gtest/gtest.h"

struct ModuleTest : public ::testing::Test
{
    ModuleTest();
    void processFile();
    codeReview::CPlusPlusDatabase m_database;
    codeReview::Findings m_findings;
    codeReview::DequeOfTerms m_terms;
    codeReview::TermTranslator m_termTranslator;
    codeReview::TermAnalyzer m_termAnalyzer;
};
