# wirelessCommunication_ACN
Wireless Communication between nodes in a network using UDP

CS 6390: Advanced Computer Networks
Fall 2014 Semester Project (Draft Description)
Energy Efficient Communication in Wireless Sensor Networks


1. Overview
In this project you will design and implement an energy efficient communication application for
wireless sensor networks. A wireless sensor network consists of a set of sensor devices that
communicate with each other via wireless links. Building an infrastructure for wireless sensor network
that guarantees energy efficient communication is an important problem. Assume that we want to
deploy a sensor network in an area to take temperature measurements and collect some statistics such
as minimum, average, or maximum temperature in the area. You will be given topology information for
a sensor network deployment (see below for the topology file format). One of the sensor nodes in the
network will be marked as a sink node. The sink node will issue queries into the network to collect a
desired temperature statistic (min/average/max) from the network. One critical requirement in
collecting this statistic is to ensure an energy efficient approach to disseminate the query to other
sensor nodes and to ensure an energy efficient approach to collect the desired statistic from the nodes
in the network. Your main job in this project will be to come up with a design for a spanning tree
construction algorithm for efficient dissemination of query messages and to come up with a design for a
protocol for energy efficient collection of the requested statistics in the network.

2. Building a Spanning Tree
A wireless sensor network consists of a group of sensor nodes communicating through a common broadcast channel using omni-directional antennas with the same transmission range. That is, when a sensor node sends a message, all of its neighbors within the transmission range hear this message. Therefore, while disseminating a query message to the entire sensor network, it may not be necessary for each sensor node to rebroadcast the message to relay the message to other nodes. This then suggests that one can build a spanning tree among a selected number of sensor nodes in the network so as to ensure that all sensor nodes hear the query message and at the same time we perform a minimum number of rebroadcast operations. This then results in energy savings in the network.
In the given topology file, one of the nodes will be marked as a sink node. It is assumed that the sink node knows the topology of the entire network including (x,y) coordinate locations and IDs of each sensor node in the network. Using this information, the sink node will compute a spanning tree rooted at itself. This spanning tree will ensure that a query message is disseminated to all other nodes in the network in an energy efficient way as described above. Once the sink node computes the spanning tree, it will disseminate this information to the nodes on the spanning tree so that each node in the network will know (1) if it is on the spanning tree, (1a) if so, who is its parent on the spanning tree, (1b) who is its children on the spanning tree, and (1c) who is its non-tree neighbors, or (2) if it is not on the spanning tree, then who is its cluster head node which is the neighbor on the spanning tree that this node needs to communicate with when needed (e.g., when reporting its temperature reading).


3. Network Operation
After the spanning tree construction is completed, based on a user request, the sink node will calculate and return statistical information about the area temperature. As an example, if the user requests the average temperature value, then the sink node will collect the necessary information from the network to compute the average temperature value and display it to the user.
  3.1. Query Dissemination
Once the sink node is asked to perform an operation (e.g. return average temperature), it will send out necessary query messages to the network to collect the required information to compute the requested value. The query dissemination will be on the spanning tree to ensure energy efficient query dissemination.  
  3.2. Query Response Collection
Query response collection should be design in a way to ensure energy efficiency in communicating the responses back to the sink node. Assuming that communication consumes more energy than computation, the intermediate nodes in the network can do some processing of the collected data before sending their information to their parents rather than sending all the individual temperature readings coming from each sensor node. One of your tasks will be to come up with an efficient way of collecting and communicating responses back to the sink node. Please note that sending a large message consumes more energy as compared to sending a short message and you should design your protocol to save energy whenever possible without causing any inaccuracies for the calculation of the requested statistic.

4. Implementation
Each node will be a process running on a system by itself. Below is the format of the network topology file. Each sensor node will read this file to learn its location and the location of others so as to identify its neighboring nodes. Broadcast communication will be emulated by using UDP messages where a node will send out individual UDP messages to each of its neighbors so as to emulate a wireless broadcast. Except for identifying their neighboring nodes, the sensor nodes should not be using the network topology file for the locations of any other non-neighbor nodes. One exception to this rule is for the sink node where we assume that the sink node knows the entire topology and therefore can use the network topology file to compute its spanning tree locally.
