/*
 * 2019 Tarpeeksi Hyvae Soft
 * 
 * Software: VCS
 * 
 */

#ifndef FILTER_GRAPH_INPUT_GATE_NODE_H
#define FILTER_GRAPH_INPUT_GATE_NODE_H

#include "filter/filter.h"
#include "display/qt/dialogs/filter_graph/filter_graph_node.h"

class InputGateNode : public FilterGraphNode
{
public:
    InputGateNode(const QString title,
                  const unsigned width = 200,
                  const unsigned height = 130) : FilterGraphNode(filter_node_type_e::gate, title, width, height)
    {
        this->edges =
        {
            node_edge_s(node_edge_s::direction_e::out, QRect(this->width-11, 9, 22, 22), this),
        };

        return;
    }

    node_edge_s* output_edge(void) override;

private:
};

#endif
