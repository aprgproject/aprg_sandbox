#include "ReversingALinkedList.hpp"

using namespace std;

namespace alba {

namespace ReversingALinkedList {

unique_ptr<Node> reverseALinkedList(unique_ptr<Node> head) {
    unique_ptr<Node> result;
    if (head) {
        unique_ptr<Node> current = move(head->nextPointer);
        result = move(head);
        while (current) {
            unique_ptr<Node> temporary = move(current->nextPointer);
            current->nextPointer = move(result);
            result = move(current);
            current = move(temporary);
        }
    }
    return result;
}

}  // namespace ReversingALinkedList

}  // namespace alba
