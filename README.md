# Routing_Protocols_Algorithm


1. linkstate:

Uses the Link State routing algorithm.
Manages routing tables based on the Link State algorithm.
Takes three input file names as arguments: topologyfile, messagesfile, and changesfile.
Reads the topology file to build the network.
Implements the Link State algorithm to construct and update routing tables for each node.
Simulates message delivery based on the constructed routing tables.
Applies changes from the changesfile to the network, updating routing tables accordingly.
Outputs the final converged routing tables and the results of message delivery to an output file (output_ls.txt).
Follows tie-breaking rules specified for the Link State algorithm.


2. distvec:

Uses the Distance Vector routing algorithm.
Manages routing tables based on the Distance Vector algorithm.
Takes three input file names as arguments: topologyfile, messagesfile, and changesfile.
Reads the topology file to build the network.
Implements the Distance Vector algorithm to construct and update routing tables for each node.
Simulates message delivery based on the constructed routing tables.
Applies changes from the changesfile to the network, updating routing tables accordingly.
Outputs the final converged routing tables and the results of message delivery to an output file (output_dv.txt).
Follows tie-breaking rules specified for the Distance Vector algorithm.

**************************************************************************************************************************************************


(1) In this assignment, socket programming is not used for directly transmitting messages over the network. Instead, it assumes the existence of virtual routers and the circuits connecting them. The task involves calculating and updating the routing tables of each router.

(2) The programs linkstate and distvec are executed as follows, each taking three file names as input arguments:
```
./linkstate topologyfile messagesfile changesfile
./distvec topologyfile messagesfile changesfile
```
Example execution:
```
./linkstate topology.txt messages.txt changes.txt
```

(3) If the number of input arguments is incorrect, the program should output the following message and exit:
```
(linkstate)
usage: linkstate topologyfile messagesfile changesfile
(distvec)
usage: distvec topologyfile messagesfile changesfile
```

(4) If an error occurs when opening the input file, the program should output the following message:
```
Error: open input file.
```

(5) Upon successful execution, the program should output the following message:
```
(linkstate)
Complete. Output file written to output_ls.txt.
(distvec)
Complete. Output file written to output_dv.txt.
```

(6) The format of the topology file is as follows: The first line indicates the total number of nodes in the network. Subsequent lines contain information about links (circuits) in the network.

Example:
```
5
0 1 8
1 2 3
1 4 4
3 0 1
3 4 1
```

(7) The messages file contains one message per line, with the format:
```
source destination message
```
Example:
```
1 0 here is a message from 1 to 0
2 4 this one gets sent from 2 to 4!
```

(8) The changes file describes changes in the network. Each line represents a change, including the format:
```
source destination cost
```
If the cost is set to -999, it indicates that there is no link between the source and destination.

Example:
```
1 3 1
1 3 -999
```

(9) The program's tasks include reading the topology file to build the network, using link-state or distance-vector algorithms to construct routing tables for each node, and simulating the delivery of messages based on these routing tables.

(10) The output files for distvec and linkstate are named output_dv.txt and output_ls.txt, respectively. The format includes the converged routing tables before applying changes, and the message delivery simulation.

(11) Example files and their contents, as well as the corresponding output files for distvec and linkstate, are provided.

(12) Tie-breaking rules are specified for distance vector and link-state algorithms to ensure consistent results.

(13) The messages file and changes file can be empty, indicating no messages or network changes.

(14) Routing tables and message delivery should be outputted before applying each line of the changes file.

(15) Constraints: The number of nodes is at most 100, the maximum link cost is 100, and the maximum length of a message string is 1000 bytes. Messages and changes files do not exceed 100 lines.

(16) All input nodes are assumed to form a single network.
