/******************************************************************************//*!
* @File          Graph.cpp
* 
* @Title         Implementation of Graph data structure.
* 
* @Author        Chetan Borse
* 
* @Created       04/22/2016
* 
* @Platform      ?
* 
* @Description   This file implements member functions of Network class.
*
*//*******************************************************************************/ 

#include "Graph.h"


/* Initializing Network's static data member. */
Network *Network::s_pNetwork = NULL;


/******************************************************************************
* @Function		Network::GetInstance
*
* @Description  Get an instance of singleton Network class.
*
* @Return       Network*                Returns pointer to Network class
******************************************************************************/
Network* Network::GetInstance()
{
    if (!s_pNetwork)
        s_pNetwork = new Network;
        
    return s_pNetwork;
}


/******************************************************************************
* @Function		Network::DestroyInstance
*
* @Description	Destroy an instance of singleton Network class.
*
* @Return		void					Returns nothing
******************************************************************************/
void Network::DestroyInstance()
{
    if (s_pNetwork)
        delete s_pNetwork;
        
    s_pNetwork = NULL;
}


/******************************************************************************
* @Function     Network::Create
*
* @Description	Create Network Graph.
*
* @Input		string		pszFilePath     File Path from which links to be read
*
* @Return		void                        Returns nothing
******************************************************************************/
void Network::Create(std::string pszFilePath)
{
    std::string   pszSourceRouter;
    std::string   pszDestinationRouter;
    std::string   pszTransmissionTime;
    std::ifstream hFile(pszFilePath);

    if (!hFile.good())
    {
        std::cerr << __FUNCTION__
                  << "(): File <"
                  << pszFilePath
                  << "> does not exist!"
                  << std::endl;
        return;
    }
    
    while (hFile >> pszSourceRouter >> pszDestinationRouter >> pszTransmissionTime)
    {
        AddLink(pszSourceRouter,
                pszDestinationRouter,
                atof(pszTransmissionTime.c_str()));
        AddLink(pszDestinationRouter,
                pszSourceRouter,
                atof(pszTransmissionTime.c_str()));
    }
}


/******************************************************************************
* @Function     Network::AddRouter
*
* @Description	Add Router to a Network.
*
* @Input		string		pszRouterName   Name of Router to be added
*
* @Return		Router*                     Returns pointer to Router
******************************************************************************/
Router *Network::AddRouter(std::string pszRouterName)
{
    Router *pRouter = GetRouter(pszRouterName);
    
    if (pRouter == NULL)
    {
        pRouter                  = new Router(pszRouterName);
        m_Routers[pszRouterName] = pRouter;
    }
    
    return pRouter;
}


/******************************************************************************
* @Function     Network::AddLink
*
* @Description	Add Link to a Network.
*
* @Input		string		pszSourceRouter         Source Router
*
* @Input		string		pszDestinationRouter    Destination Router
*
* @Input		float		fTransmissionTime       Transmission Time
*
* @Return		Link*                               Returns pointer to Link
******************************************************************************/
Link *Network::AddLink(std::string pszSourceRouter,
                       std::string pszDestinationRouter,
                       float fTransmissionTime)
{
    Router  *pSourceRouter;
    Router  *pDestinationRouter;
    Link    *pLink = GetLink(pszSourceRouter, pszDestinationRouter);
    
    if (pLink != NULL)
        pLink->SetTransmissionTime(fTransmissionTime);
    
    if (pLink == NULL)
    {
        pSourceRouter      = AddRouter(pszSourceRouter);
        pDestinationRouter = AddRouter(pszDestinationRouter);
        pLink              = new Link(pSourceRouter,
                                      pDestinationRouter,
                                      fTransmissionTime);
        m_Links[pszSourceRouter + "->" + pszDestinationRouter] = pLink;
        GetRouter(pszSourceRouter)->AddAdjacentRouter(GetRouter(pszDestinationRouter));
    }
    
    return pLink;
}


/******************************************************************************
* @Function     Network::DeleteLink
*
* @Description	Delete Link from a Network.
*
* @Input		string		pszSourceRouter         Source Router
*
* @Input		string		pszDestinationRouter    Destination Router
*
* @Return		void                                Returns nothing
******************************************************************************/
void Network::DeleteLink(std::string pszSourceRouter,
                         std::string pszDestinationRouter)
{
    Router  *pSourceRouter      = GetRouter(pszSourceRouter);
    Router  *pDestinationRouter = GetRouter(pszDestinationRouter);
    Link    *pLink              = GetLink(pszSourceRouter, pszDestinationRouter);
    
    if (pLink != NULL)
    {
        pSourceRouter->DeleteAdjacentRouter(pDestinationRouter);
        m_Links.erase(pszSourceRouter + "->" + pszDestinationRouter);
        delete pLink;
    }
}


/******************************************************************************
* @Function     Network::UpRouter
*
* @Description	Up Router in a Network.
*
* @Input		string		pszRouter       Name of Router to be upped
*
* @Return		void                        Returns nothing
******************************************************************************/
void Network::UpRouter(std::string pszRouter)
{
    Router  *pRouter = GetRouter(pszRouter);
    
    if (pRouter != NULL)
        pRouter->SetActive(true);
}


/******************************************************************************
* @Function     Network::DownRouter
*
* @Description	Down Router in a Network.
*
* @Input		string		pszRouter       Name of Router to be downed
*
* @Return		void                        Returns nothing
******************************************************************************/
void Network::DownRouter(std::string pszRouter)
{
    Router  *pRouter = GetRouter(pszRouter);
    
    if (pRouter != NULL)
        pRouter->SetActive(false);
}


/******************************************************************************
* @Function     Network::UpLink
*
* @Description	Up Link in a Network.
*
* @Input		string		pszSourceRouter         Source Router
*
* @Input		string		pszDestinationRouter    Destination Router
*
* @Return		void                        Returns nothing
******************************************************************************/
void Network::UpLink(std::string pszSourceRouter, std::string pszDestinationRouter)
{
    Router  *pSourceRouter      = GetRouter(pszSourceRouter);
    Router  *pDestinationRouter = GetRouter(pszDestinationRouter);
    Link    *pLink              = GetLink(pszSourceRouter, pszDestinationRouter);
    
    if (pLink != NULL)
        pLink->SetActive(true);
}


/******************************************************************************
* @Function     Network::DownLink
*
* @Description	Down Link in a Network.
*
* @Input		string		pszSourceRouter         Source Router
*
* @Input		string		pszDestinationRouter    Destination Router
*
* @Return		void                                Returns nothing
******************************************************************************/
void Network::DownLink(std::string pszSourceRouter,
                       std::string pszDestinationRouter)
{
    Router  *pSourceRouter      = GetRouter(pszSourceRouter);
    Router  *pDestinationRouter = GetRouter(pszDestinationRouter);
    Link    *pLink              = GetLink(pszSourceRouter, pszDestinationRouter);
    
    if (pLink != NULL)
        pLink->SetActive(false);
}


/******************************************************************************
* @Function     Network::FindShortestPath
*
* @Description	Find Shortest Path.
*
* @Input		string		pszSourceRouter         Source Router
*
* @Input		string		pszDestinationRouter    Destination Router
*
* @Return		void                                Returns nothing
******************************************************************************/
void Network::FindShortestPath(std::string pszSourceRouter,
                               std::string pszDestinationRouter)
{
    Router  *pSourceRouter      = GetRouter(pszSourceRouter);
    Router  *pDestinationRouter = GetRouter(pszDestinationRouter);
    
    if (pSourceRouter == NULL)
    {
        std::cerr << __FUNCTION__
                  << "(): Source Router <"
                  << pszSourceRouter
                  << "> does not exist!"
                  << std::endl;
        return;
    }

    if (pDestinationRouter == NULL)
    {
        std::cerr << __FUNCTION__
                  << "(): Destination Router <"
                  << pszDestinationRouter
                  << "> does not exist!"
                  << std::endl;
        return;
    }

    // Run Dijkstra's Algorithm in order to find the shortest path
    Dijkstra(pSourceRouter);
    
    if (pDestinationRouter->GetTimeToReach() == INFINITY)
    {
        std::cerr << __FUNCTION__
                  << "(): Destination Router <"
                  << pszDestinationRouter
                  << "> is not reachable!"
                  << std::endl;
        return;
    }

    // Print Shortest Path
    std::cout << __FUNCTION__ << "(): Shortest Path: " << std::endl;
    PrintShortestPath(pDestinationRouter);
    std::cout << "  " << pDestinationRouter->GetTimeToReach() << std::endl;
}


/******************************************************************************
* @Function     Network::Dijkstra
*
* @Description	Dijkstra's Algorithm.
*
* @Input		Router*		pszSourceRouter         Source Router
*
* @Return		void                                Returns nothing
******************************************************************************/
void Network::Dijkstra(Router *pSourceRouter)
{
    Router  *u;
    Router  *v;
    Link    *uv;
    MinHeap *pMinHeap;
    
    // Reset all routers
    ResetRouters();
    
    // Set SourceRouter's TimeToReach to 0
    pSourceRouter->SetTimeToReach(0);
    
    // Initialise Min Heap data structure with all the available routers
    pMinHeap = InitialiseMinHeap(m_Routers);

    // Iterate, untill Min Heap is empty
    while (pMinHeap->Size() > 0)
    {
        // Extract Min from Min Heap
        u = pMinHeap->ExtractMin();
        
        // Do not consider the router, if it is down
        if (!u->IsActive())
            continue;
        
        // Check every outgoing link
        for (Router *v : u->GetAdjacentRouters())
        {
            uv = m_Links[u->GetRouterName() + "->" + v->GetRouterName()];
            
            // Do not consider the outgoing link, if it is down
            if (!uv->IsActive())
                continue;

            // Update, if the shortest path is found
            if (v->GetTimeToReach() >
                (u->GetTimeToReach() + uv->GetTransmissionTime()))
            {
                v->SetTimeToReach(u->GetTimeToReach() + uv->GetTransmissionTime());
                v->SetPreviousRouter(u);
            }
        }
    }
    
    // Delete Min Heap data structure
    delete pMinHeap;
}


/******************************************************************************
* @Function     Network::InitialiseMinHeap
*
* @Description	Initialise Min Heap data structure.
*
* @Input		map<string, Router*>    Routers     Map of routers
*
* @Return		MinHeap*                            Returns pointer to Min Heap
*                                                   data structure
******************************************************************************/
MinHeap *Network::InitialiseMinHeap(std::map<std::string, Router*> Routers)
{
    std::vector<Router*>    vpRouters;
    
    for (auto &router : Routers)
        vpRouters.push_back(router.second);
    
    return new MinHeap(vpRouters);
}


/******************************************************************************
* @Function     Network::PrintShortestPath
*
* @Description	Print Shortest Path.
*
* @Input		Router*		pDestinationRouter      Destination Router
*
* @Return		void                                Returns nothing
******************************************************************************/
void Network::PrintShortestPath(Router *pDestinationRouter)
{
    if (pDestinationRouter->GetPreviousRouter() != NULL)
    {
        PrintShortestPath(pDestinationRouter->GetPreviousRouter());
        std::cout << " -> ";
    }
    
    std::cout << pDestinationRouter->GetRouterName();
}


/******************************************************************************
* @Function     Network::PrintNetwork
*
* @Description	Print Network Graph.
*
* @Return		void                        Returns nothing
******************************************************************************/
void Network::PrintNetwork()
{
    Link    *uv;
    
    std::cout << __FUNCTION__ << "(): Network graph: " << std::endl;
    for (auto &u : m_Routers)
    {
        std::cout << u.first;
        if (!u.second->IsActive())
            std::cout << " <DOWN>";
        std::cout << std::endl;
        
        for (Router *v : u.second->GetAdjacentRouters())
        {
            uv = GetLink(u.first, v->GetRouterName());
            std::cout << "  "
                      << v->GetRouterName()
                      << " "
                      << uv->GetTransmissionTime();
            if (!uv->IsActive())
                std::cout << " <DOWN>";
            std::cout << std::endl;
        }
    }
}


/******************************************************************************
* @Function     Network::FindReachability
*
* @Description	Find Reachable Routers.
*
* @Return		void                        Returns nothing
* 
* @Algorithm    a. Transpose Network Graph.
*               b. For every router,
*                       For every outgoing link,
*                           Find and update all possible ancestors.
*
* @TimeComplexity   O(V + E*A),
*                   Where,
*                       V: Total routers in a network
*                       E: Total links in a network
*                       A: Total ancestors for every router in a network
*                   If A~V, Time Complexity = O(V + E*V).
*
******************************************************************************/
void Network::FindReachability()
{
    Router  *u;
    Router  *v;
    Link    *uv;
    std::set<Router*> spAncestors;
    
    // Reset all routers
    ResetRouters();
    
    // Transpose Network Graph
    Transpose();
    
    // Iterate for every router
    for (auto &router : m_Routers)
    {
        u = router.second;
        
        // Do not consider the router, if it is down
        if (!u->IsActive())
            continue;
        
        // For every outgoing link, find and update all possible ancestors
        for (Router *v : u->GetAdjacentRouters())
        {
            uv = m_Links[u->GetRouterName() + "->" + v->GetRouterName()];
            
            // Do not consider the outgoing link, if it is down
            if (!uv->IsActive())
                continue;

            spAncestors.clear();
            for (Router *pAncestor : u->GetAncestors())
                if (pAncestor != v)
                    spAncestors.insert(pAncestor);
            spAncestors.insert(u);
            
            v->AddAncestors(spAncestors);
        }
    }
    
    // Print Reachable Routers
    std::cout << __FUNCTION__ << "(): Reachable Routers: " << std::endl;
    for (auto &u : m_Routers)
    {
        // Do not print the router, if it is down
        if (!u.second->IsActive())
            continue;
        
        std::cout << u.first << std::endl;
        
        for (Router *v : u.second->GetAncestors())
            std::cout << "  " << v->GetRouterName() << std::endl;
    }
    
    // Reset Network Graph to original one by transposing it again
    Transpose();
}


/******************************************************************************
* @Function     Network::Transpose
*
* @Description	Transpose Network Graph.
*
* @Return		void                        Returns nothing
******************************************************************************/
void Network::Transpose()
{
    std::string     pszSourceRouter;
    std::string     pszDestinationRouter;
    std::map<std::string, Link*> mTransposedLinks;
    
    // Reset all Adjacent Routers
    for (auto &router : m_Routers)
        router.second->DeleteAdjacentRouters();
    
    // Reverse all links and update map of links
    for (auto &link : m_Links)
    {
        link.second->Reverse();
        pszSourceRouter      = link.second->GetSourceRouter()->GetRouterName();
        pszDestinationRouter = link.second->GetDestinationRouter()->GetRouterName();
        mTransposedLinks[pszSourceRouter + "->" + pszDestinationRouter] = link.second;
    }
    
    m_Links = mTransposedLinks;
}