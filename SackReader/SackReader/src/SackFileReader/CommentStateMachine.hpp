#pragma once

#include <Common/State/AlbaBaseStateMachine.hpp>

namespace alba
{

namespace CommentStateMachineNamespace
{

enum class State
{
    NotInComment,
    Slash,
    DoubleSlash,
    InCommentNotInAsterisk,
    InCommentAsterisk
};

struct InputToken
{
    bool isNewLine;
    std::string token;
};

using BaseCommentStateMachine = AlbaBaseStateMachine<State, InputToken>;
class CommentStateMachine : public BaseCommentStateMachine
{
public:
    CommentStateMachine();
    bool isInSingleLineComment() const;
    bool isInMultilineComment() const;
    bool isInComment() const;
    void processInput(InputToken const& inputToken);
private:
    void processStateNotInComment(InputToken const& inputToken);
    void processStateSlash(InputToken const& inputToken);
    void processStateDoubleSlash(InputToken const& inputToken);
    void processStateInCommentNotInAsterisk(InputToken const& inputToken);
    void processStateInCommentAsterisk(InputToken const& inputToken);
};

}

}//namespace alba
