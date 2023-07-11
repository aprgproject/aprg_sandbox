#include "TowersOfHanoi.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>

#include <iostream>
#include <iterator>

using namespace alba::containerHelper;
using namespace std;

namespace alba {

TowersOfHanoi::TowersOfHanoi() {}

void TowersOfHanoi::transferDisksFromStartToFinish(int const numberOfDisks) const {
    StackOfDisks startStack{"startStack", {}};
    StackOfDisks inBetweenStack{"inBetweenStack", {}};
    StackOfDisks endStack{"endStack", {}};

    initialStartStack(startStack, numberOfDisks);
    transferByBulk(startStack, inBetweenStack, endStack, numberOfDisks);
}

void TowersOfHanoi::initialStartStack(StackOfDisks& startStack, int const numberOfDisks) const {
    for (int i = numberOfDisks; i > 0; i--) {
        startStack.disks.push(i);
    }
}

void TowersOfHanoi::transferByBulk(
    StackOfDisks& source, StackOfDisks& temporary, StackOfDisks& destination, int const numberOfDisksToTransfer) const {
    cout << "Started to transfer by bulk (# of disks:[" << numberOfDisksToTransfer << "]),";
    printStacksContents(source, destination);

    if (numberOfDisksToTransfer == 1) {
        transferOneDisk(source, destination);
    } else if (numberOfDisksToTransfer == 2) {
        transferOneDisk(source, temporary);       // small one
        transferOneDisk(source, destination);     // large one
        transferOneDisk(temporary, destination);  // small one
    } else if (numberOfDisksToTransfer >= 3) {
        transferByBulk(source, destination, temporary, numberOfDisksToTransfer - 1);
        transferOneDisk(source, destination);
        transferByBulk(temporary, source, destination, numberOfDisksToTransfer - 1);
    }

    cout << "Transferred to transfer by bulk (# of disks:[" << numberOfDisksToTransfer << "]),";
    printStacksContents(source, destination);
}

void TowersOfHanoi::transferOneDisk(StackOfDisks& source, StackOfDisks& destination) const {
    Disk disk = source.disks.top();
    destination.disks.push(source.disks.top());
    source.disks.pop();
    cout << "Transferred disk:[" << disk << "]";
    printStacksContents(source, destination);
}

void TowersOfHanoi::printStacksContents(StackOfDisks& source, StackOfDisks& destination) const {
    auto const& sourceContainer(getUnderlyingContainer(source.disks));
    auto const& destinationContainer(getUnderlyingContainer(destination.disks));
    std::ostream_iterator<Disk> outputIterator(cout, ", ");
    cout << " from " << source.name << " { ";
    std::copy(sourceContainer.crbegin(), sourceContainer.crend(), outputIterator);
    cout << " } to " << destination.name << " { ";
    std::copy(destinationContainer.crbegin(), destinationContainer.crend(), outputIterator);
    cout << " }\n";
}

}  // namespace alba
