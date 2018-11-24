#include <set>
#include "mips.h"
#include "df_base.h"

typedef std::set<const Location*> LiveSet;

class Liveness : public DataFlow<LiveSet, ControlFlowGraph::ReverseFlow> {
  // Value for beginning of function (or end in ReverseFlow)
  LiveSet init() {
    return LiveSet();
  }

  // "Empty" value used to accumulate effects
  LiveSet top() {
    return LiveSet();
  }

  // Calculate effect a particular instruction has on value
  LiveSet effect(const Instruction* instr, const LiveSet& in) {
    ((Instruction*)instr)->Print();
    return in;
  }

  // Calculate the meet of two values
  LiveSet meet(const LiveSet& a, const LiveSet& b) {
    LiveSet result = LiveSet(a);
    result.insert(b.begin(), b.end());
    return result;
  }
};
