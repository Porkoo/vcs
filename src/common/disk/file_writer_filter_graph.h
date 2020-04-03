/*
 * 2020 Tarpeeksi Hyvae Soft
 *
 * Software: VCS
 *
 */

#ifndef FILE_WRITER_FILTER_GRAPH_H
#define FILE_WRITER_FILTER_GRAPH_H

#include "display/qt/subclasses/InteractibleNodeGraphNode_filter_graph_nodes.h"
#include "display/display.h"

namespace file_writer
{
namespace filter_graph
{
    namespace version_b
    {
        bool write(const std::string &filename,
                   const std::vector<FilterGraphNode*> &nodes,
                   const std::vector<filter_graph_option_s> &graphOptions);
    }
}
}


#endif
