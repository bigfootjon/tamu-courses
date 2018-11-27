#ifndef _H_LIVENESS
#define _H_LIVENESS

#include <set>
#include "mips.h"
#include "df_base.h"

typedef std::set<const Location*> LiveSet;

class Liveness : public DataFlow<LiveSet, ControlFlowGraph::ReverseFlow> {
public:
  Liveness(ControlFlowGraph &cfg) : DataFlow(cfg) {
    analyze();
  }

protected:
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
    LiveSet out(in);
    LiveSet instr_locs = ((Instruction*)instr)->GetLocations();
    for (LiveSet::iterator it = instr_locs.begin(); it != instr_locs.end(); ++it) {
      if (*it != NULL) {
        out.insert(*it);
      }
    }
    return out;
  }

  // Calculate the meet of two values
  LiveSet meet(const LiveSet& a, const LiveSet& b) {
    LiveSet result = LiveSet(a);
    result.insert(b.begin(), b.end());
    return result;
  }
};

#endif
