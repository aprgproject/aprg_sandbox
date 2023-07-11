#pragma once

#include <stack>
#include <string>

namespace alba {

class TowersOfHanoi {
    using Disk = int;
    using Disks = std::stack<Disk>;
    struct StackOfDisks {
        std::string name;
        Disks disks;
    };

public:
    TowersOfHanoi();
    void transferDisksFromStartToFinish(int const numberOfDisks) const;

private:
    void initialStartStack(StackOfDisks& startStack, int const numberOfDisks) const;
    void transferByBulk(
        StackOfDisks& source, StackOfDisks& temporary, StackOfDisks& destination,
        int const numberOfDisksToTransfer) const;
    void transferOneDisk(StackOfDisks& source, StackOfDisks& destination) const;
    void printStacksContents(StackOfDisks& source, StackOfDisks& destination) const;
};

}  // namespace alba

// In the classic problem of the Towers of Hanoi,
// you have 3 towers and N disks of different sizes which can slide onto any tower.
// The puzzle starts with disks sorted in ascending order of size from top to bottom
// (i.e., each disk sits on top of an even larger one).
// You have the following constraints:
// (1) Only one disk can be moved at a time.
// (2) A disk is slid off the top of one tower onto another tower.
// (3) A disk cannot be placed on top of a smaller disk.
// Write a program to move the disks from the first tower to the last using stacks.
