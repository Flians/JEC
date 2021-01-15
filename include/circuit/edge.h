#ifndef _EDGE_H_
#define _EDGE_H_

#include "util/libhead.h"
#include "circuit/port.h"
#include "util/_properties.h"
#include "util/_map_property.h"

class Port;

class Edge : virtual public MapProperty
{
public:
    Port *src;
    Port *tar;
    vector<Point<>> bend_points;

public:
    Edge() : src(nullptr), tar(nullptr){};
    Edge(Port *_src, Port *_tar) : src(_src), tar(_tar){};
    ~Edge();

    /**
     * Reverses the edge, including its bend points. Add the CYCLE property for the netlist.
     * 
     * @param layeredGraph
     *            the layered graph
     */
    /*
    void reverse(final LGraph layeredGrap)
    {
        LPort oldSource = getSource();
        LPort oldTarget = getTarget();

        setSource(null);
        setTarget(null);
        if (adaptPorts && oldTarget.getProperty(InternalProperties.INPUT_COLLECT))
        {
            setSource(
                LGraphUtil.provideCollectorPort(layeredGraph, oldTarget.getNode(), PortType.OUTPUT, PortSide.EAST));
        }
        else
        {
            setSource(oldTarget);
        }
        if (adaptPorts && oldSource.getProperty(InternalProperties.OUTPUT_COLLECT))
        {
            setTarget(
                LGraphUtil.provideCollectorPort(layeredGraph, oldSource.getNode(), PortType.INPUT, PortSide.WEST));
        }
        else
        {
            setTarget(oldSource);
        }

        // Switch end labels
        for (LLabel label : labels)
        {
            EdgeLabelPlacement labelPlacement = label.getProperty(LayeredOptions.EDGE_LABELS_PLACEMENT);

            if (labelPlacement == EdgeLabelPlacement.TAIL)
            {
                label.setProperty(LayeredOptions.EDGE_LABELS_PLACEMENT, EdgeLabelPlacement.HEAD);
            }
            else if (labelPlacement == EdgeLabelPlacement.HEAD)
            {
                label.setProperty(LayeredOptions.EDGE_LABELS_PLACEMENT, EdgeLabelPlacement.TAIL);
            }
        }

        boolean reversed = getProperty(InternalProperties.REVERSED);
        setProperty(InternalProperties.REVERSED, !reversed);

        bendPoints = KVectorChain.reverse(bendPoints);
    }
    */

    friend ostream &operator<<(ostream &output, const Edge &p);
};

#endif