#include "cfg.h"
#include "tac.h"

/*----------------------------------------------------------
 * Create and initialize new CFG
 */
ControlFlowGraph::ControlFlowGraph(iterator first, iterator last)
   : first( first ), last( last )
{
  map_labels();
  map_edges();
}

/*----------------------------------------------------------
 * Build map from labels -> instructions
 */
void ControlFlowGraph::map_labels()
{
  for (iterator p= first; p != last; ++p)
  {
    Label* label= dynamic_cast<Label*>(*p);
    if (label)
      instr_for_label[label->text()]= *p;
  }
}

/*----------------------------------------------------------
 * Build map from instruction -> input edges
 * Build map from instruction -> output edges
 */
void ControlFlowGraph::map_edges()
{
  for (iterator cur= first; cur != last; ++cur)
  {
    iterator next= cur;
    ++next;

    if (dynamic_cast<Goto*>(*cur)) {
      add_edge(*cur, instr_for_label[dynamic_cast<Goto*>(*cur)->branch_label()]);
    } else if (dynamic_cast<IfZ*>(*cur)) {
      add_edge(*cur, *next);
      add_edge(*cur, instr_for_label[dynamic_cast<IfZ*>(*cur)->branch_label()]);
    } else {
      add_edge(*cur, *next);
    }
  }
}

/*----------------------------------------------------------
 * Add edge going between two instructions
 */
void ControlFlowGraph::add_edge(Instruction* from, Instruction* to)
{
  in_edges[to].push_back(from);
  out_edges[from].push_back(to);
}
