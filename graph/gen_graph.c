#include "../include/utils.h"
#include "/usr/include/graphviz/cgraph.h"
#include "/usr/include/graphviz/gvc.h"
#include "gen_graph.h"
#include <graphviz/gvcext.h>
#include <graphviz/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void gen_graph(void)
{
  Agraph_t *g = agopen("example", Agdirected, NULL);
  Agnode_t *nodes[NUM_STATES];
  for (int i = 0; i < NUM_STATES; i++)
  {
    nodes[i] = agnode(g, state_name[i], 1);
  }

  for (int i = 0; i < NUM_STATES; i++)
  {
    for (int j = 0; j < NUM_EVENTS; j++)
    {
      if (transition_table[i][j] != INVALID_STATE)
      {
        Agnode_t *target = nodes[transition_table[i][j]];
        Agedge_t *e = agedge(g, nodes[i], target, NULL, 1);
        agset(e, "label", event_name[j]);
      }
    }
  }

  GVC_t *gvc;
  gvc = gvContext();

  if (gvLayout(gvc, g, "dot") != 0)
  {
    if (fprintf(stderr, "Error: Graph layout failed\n") < 0)
    {
      perror("fprintf failed");
    }
    gvFreeContext(gvc);
    agclose(g);
    return;
  }

  FILE *outfile = fopen("graph.png", "w");
  if (outfile)
  {
    gvRender(gvc, g, "png", outfile);
    if (fprintf(stderr, "Graph successfully written to graph.png\n") < 0)
    {
      perror("fprintf failed\n");
    }
  }
}

int main(void)
{
  gen_graph();
  return 0;
}
