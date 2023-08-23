#define CHECK_TERM(it, termType, content, lineNumber) \
    EXPECT_EQ(it->getTermType(), termType);           \
    EXPECT_EQ(it->getLineNumber(), lineNumber);       \
    EXPECT_EQ(it++->getString(), content);

#define CHECK_TERM_WITH_VALUE_TYPE(it, termType, content, valueType, lineNumber) \
    EXPECT_EQ(it->getTermType(), termType);                                      \
    EXPECT_EQ(it->getValueType().getTypeName(), valueType);                      \
    EXPECT_EQ(it->getLineNumber(), lineNumber);                                  \
    EXPECT_EQ(it++->getString(), content);

#define CHECK_TERM_THEN_WHITE_SPACE(it, termType, content, lineNumber) \
    EXPECT_EQ(it->getTermType(), termType);                            \
    EXPECT_EQ(it->getLineNumber(), lineNumber);                        \
    EXPECT_EQ(it++->getString(), content);                             \
    EXPECT_EQ(it->getTermType(), TermType::WhiteSpace);                \
    EXPECT_EQ(it->getLineNumber(), lineNumber);                        \
    EXPECT_EQ(it++->getString(), " ");

#define CHECK_TERM_WITH_VALUE_TYPE_THEN_WHITE_SPACE(it, termType, content, valueType, lineNumber) \
    EXPECT_EQ(it->getTermType(), termType);                                                       \
    EXPECT_EQ(it->getLineNumber(), lineNumber);                                                   \
    EXPECT_EQ(it->getValueType().getTypeName(), valueType);                                       \
    EXPECT_EQ(it++->getString(), content);                                                        \
    EXPECT_EQ(it->getTermType(), TermType::WhiteSpace);                                           \
    EXPECT_EQ(it->getLineNumber(), lineNumber);                                                   \
    EXPECT_EQ(it++->getString(), " ");

#define CHECK_TERM_IF_NEWLINE(it, lineNumber)        \
    EXPECT_EQ(it->getTermType(), TermType::NewLine); \
    EXPECT_EQ(it->getLineNumber(), lineNumber);      \
    EXPECT_EQ(it++->getString(), "\n");

#define CHECK_TYPE_IN_DATABASE(database, typeName, cPlusPlusType) \
    ASSERT_TRUE(database.isType(typeName));                       \
    EXPECT_EQ(database.getTypeReferenceWithAlias(typeName), cPlusPlusType);
