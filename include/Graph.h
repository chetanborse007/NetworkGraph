/******************************************************************************//*!
* @File          Graph.h
* 
* @Title         Header file for Graph data structure.
* 
* @Author        Chetan Borse
* 
* @Created       04/22/2016
* 
* @Platform      ?
* 
* @Description   This header file defines the prototypes of classes and functions 
*                for Graph data structure.
* 
*//*******************************************************************************/ 

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <limits>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

#include "MinHeap.h"

#define INFINITY std::numeric_limits<float>::infinity()


/* Forward declaration for MinHeap class */
class MinHeap;


/******************************************************************************
* @Class		Router
*
* @Description	Class representing Router.
* 				This class defines attributes and functionalities
*               of Router.
******************************************************************************/
class Router
{
private:
    // Comparator for comparing elements of set
    struct SetComparator
    {
        bool operator() (Router* lhs, Router* rhs) const
        {
            return lhs->GetRouterName() < rhs->GetRouterName();
        }
    };

    std::string          m_pszRouterName;
    float                m_fTimeToReach;
    Router               *m_pPreviousRouter;
    std::vector<Router*> m_vpAdjacentRouters;
    bool                 m_bActive;
    std::set<Router*, SetComparator>    m_spAncestors;

public:
    // Constructor
    Router(std::string pszRouterName="", bool bActive=true)
    {
        m_pszRouterName = pszRouterName;
        m_bActive       = bActive;
        Reset();
    }

    // Destructor
    ~Router() {}

    // Public setter
    void SetRouterName(std::string pszRouterName="")
    {
        m_pszRouterName = pszRouterName;
    }
    void SetTimeToReach(float fTimeToReach=INFINITY)
    {
        m_fTimeToReach = fTimeToReach;
    }
    void SetPreviousRouter(Router *pPreviousRouter)
    {
        m_pPreviousRouter = pPreviousRouter;
    }
    void SetActive(bool bActive) { m_bActive = bActive; }
    
    // Public getter
    std::string GetRouterName() { return m_pszRouterName; }
    float const GetTimeToReach() { return m_fTimeToReach; }
    Router *GetPreviousRouter() { return m_pPreviousRouter; }
    std::vector<Router*> const GetAdjacentRouters() { return m_vpAdjacentRouters; }
    std::set<Router*, SetComparator> GetAncestors() { return m_spAncestors; }

    // Check whether the Router is active or down
    bool IsActive() { return m_bActive; }

    // Add Adjacent Router
    void AddAdjacentRouter(Router* pAdjacentRouter)
    {
        m_vpAdjacentRouters.push_back(pAdjacentRouter);
        sort(m_vpAdjacentRouters.begin(), m_vpAdjacentRouters.end(), Compare);
    }

    // Delete Adjacent Router
    void DeleteAdjacentRouter(Router* pAdjacentRouter)
    {
        m_vpAdjacentRouters.erase(
                                  std::remove(
                                              m_vpAdjacentRouters.begin(),
                                              m_vpAdjacentRouters.end(),
                                              pAdjacentRouter
                                             ),
                                  m_vpAdjacentRouters.end()
                                 );
    }

    // Delete all Adjacent Routers
    void DeleteAdjacentRouters() { m_vpAdjacentRouters.clear(); }

    // Add Ancestors
    void AddAncestors(std::set<Router*> spAncestors)
    {
        m_spAncestors.insert(spAncestors.begin(), spAncestors.end());
    }

    // Delete all Ancestors
    void DeleteAncestors() { m_spAncestors.clear(); }

    // Comparator for comparing elements of vector
    static bool Compare(Router *v1, Router *v2)
    {
        return v1->GetRouterName() < v2->GetRouterName();
    }

    // Reset attributes of the Router
    void Reset()
    {
        m_fTimeToReach    = INFINITY;
        m_pPreviousRouter = NULL;
        DeleteAncestors();
    }
};


/******************************************************************************
* @Class       Link
*
* @Description	Class representing Link.
* 				This class defines attributes and functionalities
*              of Link.
******************************************************************************/
class Link
{
private:
    std::string m_pszLinkName;
    Router      *m_pSourceRouter;
    Router      *m_pDestinationRouter;
    float       m_fTransmissionTime;
    bool        m_bActive;

public:
    // Constructor
    Link(Router *pSourceRouter=NULL,
         Router *pDestinationRouter=NULL,
         float fTransmissionTime=INFINITY,
         bool bActive=true)
    {
        m_pSourceRouter      = pSourceRouter;
        m_pDestinationRouter = pDestinationRouter;
        m_fTransmissionTime  = fTransmissionTime;
        m_bActive            = bActive;
    }
    
    // Destructor
    ~Link() {}
    
    // Public setter
    void SetSourceRouter(Router *pSourceRouter) { m_pSourceRouter = pSourceRouter; }
    void SetDestinationRouter(Router *pDestinationRouter)
    {
        m_pDestinationRouter = pDestinationRouter;
    }
    void SetTransmissionTime(float fTransmissionTime)
    {
        m_fTransmissionTime = fTransmissionTime;
    }
    void SetActive(bool bActive) { m_bActive = bActive; }

    // Public getter
    Router *GetSourceRouter() { return m_pSourceRouter; }
    Router *GetDestinationRouter() { return m_pDestinationRouter; }
    float const GetTransmissionTime() { return m_fTransmissionTime; }
    
    // Check whether the Link is active or down
    bool IsActive() { return m_bActive; }
    
    // Reverse the Link
    void Reverse()
    {
        std::swap(m_pSourceRouter, m_pDestinationRouter);
        m_pSourceRouter->AddAdjacentRouter(m_pDestinationRouter);
    }
};


/******************************************************************************
* @Class		Network
*
* @Description	Singleton class representing Network data structure.
* 				This class defines attributes and functionalities
*               of Network data structure.
******************************************************************************/
class Network
{
private:
    std::map<std::string, Router*> m_Routers;
    std::map<std::string, Link*>   m_Links;

    static Network *s_pNetwork;

    // Constructor
    Network() {}
    
    // Destructor
    ~Network() {}

    // Reset all routers
    void ResetRouters()
    {
        for (auto &router : m_Routers)
            router.second->Reset();
    }
    
    // Initialise Min Heap data structure
    MinHeap *InitialiseMinHeap(std::map<std::string, Router*> Routers);
    
    // Dijkstra's Algorithm
    void Dijkstra(Router *pSourceRouter);
    
    // Print Shortest Path
    void PrintShortestPath(Router *pDestinationRouter);

    // Transpose Network Graph
    void Transpose();

public:
    // Public setter
    std::map<std::string, Router*> const GetRouters() { return m_Routers; }
    std::map<std::string, Link*> const GetLinks() { return m_Links; }

    // Public getter
    Router *GetRouter(std::string pszRouterName)
    {
        return m_Routers[pszRouterName];
    }
    
    Link *GetLink(std::string pszSourceRouter, std::string pszDestinationRouter)
    {
        return m_Links[pszSourceRouter + "->" + pszDestinationRouter];
    }

    // Get an instance of singleton Network class
    static Network *GetInstance();
    
    // Destroy an instance of singleton Network class
    static void DestroyInstance();

    // Create Network Graph
    void Create(std::string pszFilePath);
    
    // Add Router to a Network
    Router *AddRouter(std::string pszRouterName);

    // Add Link to a Network
    Link *AddLink(std::string pszSourceRouter,
                  std::string pszDestinationRouter,
                  float fTransmissionTime);

    // Delete Link from a Network
    void DeleteLink(std::string pszSourceRouter, std::string pszDestinationRouter);

    // Up Router in a Network
    void UpRouter(std::string pszRouter);

    // Down Router in a Network
    void DownRouter(std::string pszRouter);

    // Up Link in a Network
    void UpLink(std::string pszSourceRouter, std::string pszDestinationRouter);

    // Down Link in a Network
    void DownLink(std::string pszSourceRouter, std::string pszDestinationRouter);
    
    // Find Shortest Path
    void FindShortestPath(std::string pszSourceRouter,
                          std::string pszDestinationRouter);

    // Print Network Graph
    void PrintNetwork();

    // Find Reachable Routers
    void FindReachability();
};