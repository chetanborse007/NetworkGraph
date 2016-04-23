/******************************************************************************//*!
* @File          Main.cpp
* 
* @Title         Implementation of main utility/application.
* 
* @Author        Chetan Borse
* 
* @Created       04/22/2016
* 
* @Platform      ?
* 
* @Description   This file implements functions required by main utility/application.
*
*//*******************************************************************************/ 

#include "Main.h"


/******************************************************************************
* @Function		Tokenizer
*
* @Description	Tokenizer returns vector of strings
*               by splitting original string on whitespaces.
*
* @Input		string&         pszQuery        Query
*
* @Input		char            chDelimiter     Delimiter for splitting original string
*
* @Return		vector<string>                  Returns vector of strings
******************************************************************************/
std::vector<std::string> Tokenizer(const std::string& pszQuery, char chDelimiter)
{
    std::stringstream        stream(pszQuery);
    std::string              pszToken;
    std::vector<std::string> vpszTokens;

    while(getline(stream, pszToken, chDelimiter))
        if (pszToken != "")
            vpszTokens.push_back(pszToken);

    return vpszTokens;
}


/******************************************************************************
* @Function		ShowUsage
*
* @Description	Helper method.
*
* @Return		void                    Returns nothing
******************************************************************************/
void ShowUsage()
{
    std::cerr << "Usage: " << " <Action> <Parameters>" << std::endl;
    std::cerr << "1)  graph <File Path>" << std::endl;
    std::cerr << "2)  addedge <Source Router> <Destination Router> <Transmission Time>" << std::endl;
    std::cerr << "3)  deleteedge <Source Router> <Destination Router>" << std::endl;
    std::cerr << "4)  edgedown <Source Router> <Destination Router>" << std::endl;
    std::cerr << "5)  edgeup <Source Router> <Destination Router>" << std::endl;
    std::cerr << "6)  vertexdown <Router>" << std::endl;
    std::cerr << "7)  vertexup <Router>" << std::endl;
    std::cerr << "8)  path <Source Router> <Destination Router>" << std::endl;
    std::cerr << "9)  print" << std::endl;
    std::cerr << "10) reachable" << std::endl;
    std::cerr << "11) quit" << std::endl;
}


/* Entry point */
int main(int argc, const char *argv[])
{
    std::string     pszQuery;
    std::string     pszAction;
    std::string     pszFilePath;
    std::string     pszSourceRouter;
    std::string     pszDestinationRouter;
    float           fTransmissionTime;
    std::string     pszRouter;
    std::vector<std::string> vpszTokens;
    
    std::cout << __FUNCTION__ << "(): *******************************" << std::endl;
    std::cout << __FUNCTION__ << "(): * Shortest Paths in a Network *" << std::endl;
    std::cout << __FUNCTION__ << "(): *******************************" << std::endl;
    
    while (true)
    {
        std::cout << std::endl;
        std::cout << __FUNCTION__ << "(): Enter Query => " << std::endl;
        getline(std::cin, pszQuery);
        vpszTokens = Tokenizer(pszQuery);
        
        pszAction = vpszTokens[0];
        
        if (pszAction == "graph")
        {
            pszFilePath = vpszTokens[1];
            Network::GetInstance()->Create(pszFilePath);
        }
        else if (pszAction == "addedge")
        {
            pszSourceRouter      = vpszTokens[1];
            pszDestinationRouter = vpszTokens[2];
            fTransmissionTime    = atof(vpszTokens[3].c_str());
            Network::GetInstance()->AddLink(pszSourceRouter,
                                            pszDestinationRouter,
                                            fTransmissionTime);
            std::cout << __FUNCTION__
                      << "(): Link <"
                      << pszSourceRouter
                      << ", "
                      << pszDestinationRouter
                      << ", "
                      << fTransmissionTime
                      << "> is added!"
                      << std::endl;
        }
        else if (pszAction == "deleteedge")
        {
            pszSourceRouter      = vpszTokens[1];
            pszDestinationRouter = vpszTokens[2];
            Network::GetInstance()->DeleteLink(pszSourceRouter, pszDestinationRouter);
            std::cout << __FUNCTION__
                      << "(): Link <"
                      << pszSourceRouter
                      << ", "
                      << pszDestinationRouter
                      << "> is removed!"
                      << std::endl;
        }
        else if (pszAction == "edgedown")
        {
            pszSourceRouter      = vpszTokens[1];
            pszDestinationRouter = vpszTokens[2];
            Network::GetInstance()->DownLink(pszSourceRouter, pszDestinationRouter);
            std::cout << __FUNCTION__
                      << "(): Link <"
                      << pszSourceRouter
                      << ", "
                      << pszDestinationRouter
                      << "> is down!"
                      << std::endl;
        }
        else if (pszAction == "edgeup")
        {
            pszSourceRouter      = vpszTokens[1];
            pszDestinationRouter = vpszTokens[2];
            Network::GetInstance()->UpLink(pszSourceRouter, pszDestinationRouter);
            std::cout << __FUNCTION__
                      << "(): Link <"
                      << pszSourceRouter
                      << ", "
                      << pszDestinationRouter
                      << "> is up!"
                      << std::endl;
        }
        else if (pszAction == "vertexdown")
        {
            pszRouter = vpszTokens[1];
            Network::GetInstance()->DownRouter(pszRouter);
            std::cout << __FUNCTION__
                      << "(): Router <"
                      << pszRouter
                      << "> is down!"
                      << std::endl;
        }
        else if (pszAction == "vertexup")
        {
            pszRouter = vpszTokens[1];
            Network::GetInstance()->UpRouter(pszRouter);
            std::cout << __FUNCTION__
                      << "(): Router <"
                      << pszRouter
                      << "> is up!"
                      << std::endl;
        }
        else if (pszAction == "path")
        {
            pszSourceRouter      = vpszTokens[1];
            pszDestinationRouter = vpszTokens[2];
            Network::GetInstance()->FindShortestPath(pszSourceRouter,
                                                     pszDestinationRouter);
        }
        else if (pszAction == "print")
        {
            Network::GetInstance()->PrintNetwork();
        }
        else if (pszAction == "reachable")
        {
            Network::GetInstance()->FindReachability();
        }
        else if (pszAction == "quit")
        {
            Network::DestroyInstance();
            break;
        }
        else
        {
            ShowUsage();
        }
    }

    return 0;
}