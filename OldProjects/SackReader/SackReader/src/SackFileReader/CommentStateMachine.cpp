#include "CommentStateMachine.hpp"

using namespace std;

namespace alba
{

namespace CommentStateMachineNamespace
{

CommentStateMachine::CommentStateMachine()
    : AlbaBaseStateMachine(State::NotInComment)
{}

bool CommentStateMachine::isInSingleLineComment() const
{
    return m_state==State::DoubleSlash;
}

bool CommentStateMachine::isInMultilineComment() const
{
    return m_state==State::InCommentAsterisk || m_state==State::InCommentNotInAsterisk;
}

bool CommentStateMachine::isInComment() const
{
    return isInSingleLineComment() || isInMultilineComment();
}

void CommentStateMachine::processInput(InputToken const& inputToken)
{
    switch(m_state)
    {
    case State::NotInComment:
        processStateNotInComment(inputToken);
        break;
    case State::Slash:
        processStateSlash(inputToken);
        break;
    case State::DoubleSlash:
        processStateDoubleSlash(inputToken);
        break;
    case State::InCommentNotInAsterisk:
        processStateInCommentNotInAsterisk(inputToken);
        break;
    case State::InCommentAsterisk:
        processStateInCommentAsterisk(inputToken);
        break;
    default:
        assert(false);
        break;
    }
}

void CommentStateMachine::processStateNotInComment(InputToken const& inputToken)
{
    if(inputToken.token=="/")
    {
        saveNextState(State::Slash);
    }
}

void CommentStateMachine::processStateSlash(InputToken const& inputToken)
{
    if(inputToken.token=="/")
    {
        saveNextState(State::DoubleSlash);
    }
    else if(inputToken.token=="*")
    {
        saveNextState(State::InCommentNotInAsterisk);
    }
    else
    {
        saveNextState(State::NotInComment);
    }
}

void CommentStateMachine::processStateDoubleSlash(InputToken const& inputToken)
{
    if(inputToken.isNewLine)
    {
        saveNextState(State::NotInComment);
        processInput(inputToken);
    }
}

void CommentStateMachine::processStateInCommentNotInAsterisk(InputToken const& inputToken)
{
    if(inputToken.token=="*")
    {
        saveNextState(State::InCommentAsterisk);
    }
}

void CommentStateMachine::processStateInCommentAsterisk(InputToken const& inputToken)
{
    if(inputToken.token=="/")
    {
        saveNextState(State::NotInComment);
    }
    else if(inputToken.token!="*")
    {
        saveNextState(State::InCommentNotInAsterisk);
    }
}

}


}//namespace alba
