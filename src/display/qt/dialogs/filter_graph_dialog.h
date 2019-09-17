#ifndef FILTER_GRAPH_DIALOG_H_
#define FILTER_GRAPH_DIALOG_H_

#include <QDialog>
#include "filter/filter.h"

class InteractibleNodeGraph;
class FilterGraphNode;
class QMenuBar;

namespace Ui {
class FilterGraphDialog;
}

class FilterGraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterGraphDialog(QWidget *parent = 0);
    ~FilterGraphDialog();

    void recalculate_filter_chains(void);

    void clear_filter_graph(void);

    FilterGraphNode* add_filter_graph_node(const filter_type_enum_e &filterType, const u8 * const initialParameterValues);

    FilterGraphNode* add_filter_node(const filter_type_enum_e type, const u8 *const initialParameterValues = nullptr);

private:
    void reset_graph(void);
    void save_filters(void);
    void load_filters(void);

    Ui::FilterGraphDialog *ui;
    QMenuBar *menubar = nullptr;
    InteractibleNodeGraph *graphicsScene = nullptr;

    // All the nodes that are currently in the graph.
    std::vector<FilterGraphNode*> inputGateNodes;

    unsigned numNodesAdded = 0;
};

#endif