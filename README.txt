*******************
*  NETWORK GRAPH  *
*******************


* Introduction
* File List
* Requirements
* Installation
* Usage
* Design Decision
* Maintainer


I. INTRODUCTION
---------------

This is a network graph utility, which represents data communication network consisting Routers as vertices and Links as edges.

This utility represent network that follows the OSPF (Open Shortest Path First) protocol for routing packets using Dijkstra’s shortest path algorithm. The criteria used to compute the weight corresponding to a link includes the time taken for data transmission.
The shortest path algorithm in the utility computes the best path using the criterion of minimizing the total time taken for data to reach the destination. Here, the shortest time path minimizes the sum of the transmission times of the links along the path.This utility also handles network topology that changes dynamically based on the state of the links and the routers.
For example, a link may go down, router may crash, a new link is added or removed.

This utility has below major functionalities:
1. Find shortest path for routing data packets
2. Find reachable routers


II. FILE LIST
-------------

A. Header Files:
    MinHeap.h		Header for Min Heap data structure
    Graph.h		Header for Graph data structure
    Main.h		Header for entry point of utility/application

B. Source Files:
    MinHeap.cpp		Implementation of Min Heap data structure
    Graph.cpp		Implementation of Graph data structure
    Main.cpp		Entry point of utility/application

C. Sample Data Files:
    network.txt		File consisting of information about links in initial network
    queries.txt		File consisting of different queries

D. Makefile generator:
    CMakeList.txt	CMake configuration to generate Makefile 
			for Network Graph project

E. README


III. REQUIREMENTS
-----------------

This application requires the following modules:
1. g++ (Preferably Version 4.8 and above)

2. CMake (https://cmake.org) (Preferably Version 3.1.0 and above)

   Steps to install CMake using ppa:
	> sudo apt-get remove cmake cmake-data
	> sudo -E add-apt-repository -y ppa:george-edison55/cmake-3.x
	> sudo -E apt-get update
	> sudo apt-get install cmake

3. Mac OS or Linux (Not tested on Windows)


IV. INSTALLATION
----------------

A. MAC OS:
    1. Download `NetworkGraph.zip`

    2. Uncompress `NetworkGraph.zip`
        $ unzip NetworkGraph.zip

    3. Create build directory anywhere you want
        $ mkdir build

    4. Change to build directory
        $ cd build

    5. Generate Makefile
        $ cmake <Source Directory>
        e.g. $ cmake ../NetworkGraph/

    6. Build source
        $ make

    7. Find `./NetworkGraph` utility within build directory itself

B. Linux:
    Same as described in (IV)-[A].
    Note: Few commands will be different depending upon your Linux flavour.

C. Windows:
    Not tested.


V. USAGE
--------

A. Mac OS:
    Run `NetworkGraph` utility.
    $ ./NetworkGraph

    Below are the different queries supported:
	1)  graph <File Path>
	2)  addedge <Source Router> <Destination Router> <Transmission Time>
	3)  deleteedge <Source Router> <Destination Router>
	4)  edgedown <Source Router> <Destination Router>
	5)  edgeup <Source Router> <Destination Router>
	6)  vertexdown <Router>
	7)  vertexup <Router>
	8)  path <Source Router> <Destination Router>
	9)  print
	10) reachable
	11) quit

B. Linux:
    Same as described in (V)-[A].

C. Windows:
    Not tested.


VI. DESIGN DECISION
-------------------

A. Data Structures:
    * Min Heap
    * Router
    * Link
    * Network (Singleton class)

    1. Min Heap ->
	Attributes:
		m_vpHeap		Vector of pointers to Router data structures.

	Methods:
		Size()			Returns size of Min Heap data structure
		Create()		Create Min Heap data structure
		MinHeapify()		Min Heapify
		ExtractMin()		Extract Min
		Insert()		Insert Router into Min Heap data structure
		HeapDecreaseKey()	Decrease key located at given index
		Display()		Display Min Heap data structure

    2. Router ->
	Attributes:
		m_pszRouterName		Router Name.
		m_fTimeToReach		Time To Reach at Router.
		m_pPreviousRouter	Previous Router.
		m_vpAdjacentRouters	Vector of Adjacent Routers.
		m_bActive		Flag to check whether the Router is active or down.
		m_spAncestors		Vector of Ancestors.

	Methods:
		IsActive()		Check whether the Router is active or down
		AddAdjacentRouter()	Add Adjacent Router
		DeleteAdjacentRouter()	Delete Adjacent Router
		AddAncestors()		Add Ancestors
		DeleteAncestors()	Delete Ancestors
		Reset()			Reset attributes of the Router

    3. Link ->
	Attributes:
		m_pszLinkName		Link Name.
		m_pSourceRouter		Source Router.
		m_pDestinationRouter	Destination Router.
		m_fTransmissionTime	Transmission Time.
		m_bActive		Flag to check whether the Link is active or down.

	Methods:
		IsActive()		Check whether the Link is active or down
		Reverse()		Reverse the Link

    4. Network ->
	Attributes:
		m_Routers		Map of routers.
		m_Links			Map of links.

	Methods:
		Create()		Create Network Graph
		AddRouter()		Add Router to a Network
		AddLink()		Add Link to a Network
		DeleteLink()		Delete Link from a Network
		UpRouter()		Up Router in a Network
		DownRouter()		Down Router in a Network
		UpLink()		Up Link in a Network
		DownLink()		Down Link in a Network
		FindShortestPath()	Find Shortest Path
		Dijkstra()		Dijkstra's Algorithm
		PrintNetwork()		Print Network Graph
		FindReachability()	Find Reachable Routers
		Transpose()		Transpose Network Graph

B. Algorithms:
    1. Find shortest path for routing data packets:
	> Reset all routers.
	> Set SourceRouter's TimeToReach to 0.
	> Initialise Min Heap data structure with all the available routers.
	> If Min Heap is not empty,
		a. Extract Router from Min Heap, which has minimal time to reach.
		b. If extracted router is down,
		   Then,
			Do not consider the extracted router.
		c. For every outgoing link,
			- If outgoing link is down,
		   	  Then,
				Do not consider the outgoing link.
			- If the shortest distance is found,
			  Then,
				Update relevant adjacent router.
	> If Min Heap is empty,
	  Then,
		Stop algorithm.

    2. Find Reachable Routers:
	Note:
		Time Complexity = O(V + E*A),
		Where,
			V: Total routers in a network
			E: Total links in a network
			A: Total ancestors for every router in a network
		If A~V, Time Complexity = O(V + E*V).

	> Reset all routers.
	> Transpose Network Graph.
	> For every router,
		a. If router is down,
		   Then,
			Do not consider it.
		c. For every outgoing link,
			- If outgoing link is down,
		   	  Then,
				Do not consider the outgoing link.
			- Find and update all possible ancestors.
	> For every router,
		a. Print Reachable Routers.


VII. MAINTAINER
---------------

Name        Chetan Borse
EMail ID    chetanborse2106@gmail.com
LinkedIn    https://www.linkedin.com/in/chetanrborse
