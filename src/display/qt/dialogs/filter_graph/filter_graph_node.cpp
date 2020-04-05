/*
 * 2019 Tarpeeksi Hyvae Soft
 * 
 * Software: VCS
 * 
 */

#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QStyle>
#include "filter/filter.h"
#include "common/globals.h"
#include "display/qt/dialogs/filter_graph/filter_graph_node.h"
#include "display/qt/subclasses/QGraphicsScene_interactible_node_graph.h"

FilterGraphNode::FilterGraphNode(const filter_node_type_e type,
                                 const QString title,
                                 const unsigned width,
                                 const unsigned height) :
    InteractibleNodeGraphNode(title, width, height),
    filterType(type)
{
    this->generate_right_click_menu();

    return;
}

FilterGraphNode::~FilterGraphNode()
{
    kf_delete_filter_instance(this->associatedFilter);

    this->rightClickMenu->close();
    this->rightClickMenu->deleteLater();

    return;
}

void FilterGraphNode::set_background_color(const QString colorName)
{
    // If we recognize this color name.
    if (this->backgroundColorList.indexOf(colorName) >= 0)
    {
        this->backgroundColor = colorName;
        this->update();
    }

    return;
}

const QList<QString>& FilterGraphNode::background_color_list(void)
{
    return this->backgroundColorList;
}

const QString& FilterGraphNode::current_background_color_name(void)
{
    return this->backgroundColor;
}

bool FilterGraphNode::is_enabled(void) const
{
    return this->isEnabled;
}

void FilterGraphNode::set_enabled(const bool enabled)
{
    this->isEnabled = enabled;

    if (enabled)
    {
        emit this->enabled();
    }
    else
    {
        emit this->disabled();
    }

    dynamic_cast<InteractibleNodeGraph*>(this->scene())->update();

    return;
}

void FilterGraphNode::generate_right_click_menu(void)
{
    if (this->rightClickMenu)
    {
        this->rightClickMenu->deleteLater();
    }

    this->rightClickMenu = new QMenu();

    this->rightClickMenu->addAction(this->title);
    this->rightClickMenu->actions().at(0)->setEnabled(false);

    // Add an option to enable/disable this node. Nodes that are disabled will act
    // as passthroughs, and their corresponding filter won't be applied.
    if (this->filterType != filter_node_type_e::gate)
    {
        this->rightClickMenu->addSeparator();

        QAction *enabled = new QAction("Enabled", this->rightClickMenu);

        enabled->setCheckable(true);
        enabled->setChecked(this->isEnabled);

        connect(this, &FilterGraphNode::enabled, this, [=]
        {
            enabled->setChecked(true);
        });

        connect(this, &FilterGraphNode::disabled, this, [=]
        {
            enabled->setChecked(false);
        });

        connect(enabled, &QAction::triggered, this, [=]
        {
            this->set_enabled(!this->isEnabled);
            kd_recalculate_filter_graph_chains();
        });

        this->rightClickMenu->addAction(enabled);
    }

    // Add options to change the node's color.
    if ((this->filterType != filter_node_type_e::gate) &&
        !this->background_color_list().empty())
    {
        this->rightClickMenu->addSeparator();

        QMenu *colorMenu = new QMenu("Background color", this->rightClickMenu);

        QActionGroup *colorGroup = new QActionGroup(colorMenu);
        colorGroup->setExclusive(true);

        for (const auto &color : this->backgroundColorList)
        {
            QAction *colorAction = new QAction(color, colorMenu);
            colorAction->setCheckable(true);
            colorAction->setChecked(color == this->backgroundColor);
            colorAction->setActionGroup(colorGroup);
            colorMenu->addAction(colorAction);

            connect(colorAction, &QAction::triggered, this, [=]
            {
                this->set_background_color(color);
            });
        }

        this->rightClickMenu->addMenu(colorMenu);
    }

    // Add the option to delete this node.
    {
        this->rightClickMenu->addSeparator();

        connect(this->rightClickMenu->addAction("Remove this node"), &QAction::triggered, this, [=]
        {
            dynamic_cast<InteractibleNodeGraph*>(this->scene())->remove_node(this);
        });
    }

    return;
}
