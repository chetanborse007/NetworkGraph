/******************************************************************************//*!
* @File          MinHeap.cpp
* 
* @Title         Implementation of Min Heap data structure.
* 
* @Author        Chetan Borse
* 
* @Created       04/22/2016
* 
* @Platform      ?
* 
* @Description   This file implements member functions of MinHeap class.
*
*//*******************************************************************************/ 

#include "MinHeap.h"


/******************************************************************************
* @Function		MinHeap::Create
*
* @Description  Create Min Heap data structure.
*
* @Return       void                    Returns nothing
******************************************************************************/
void MinHeap::Create(std::vector<Router*> vpHeap)
{
    int index;

    // Set Heap
    SetHeap(vpHeap);

    // Min heapify starting from the parent of last child to first node
    index = (Size() / 2) - 1;
    while (index >= 0)
    {
        MinHeapify(index);
        index--;
    }
}


/******************************************************************************
* @Function		MinHeap::MinHeapify
*
* @Description	Min Heapify.
*
* @Input		int         index		Index at which Min Heapify is to be done
*
* @Return		void					Returns nothing
******************************************************************************/
void MinHeap::MinHeapify(int index)
{
    int smallest;
    int left  = Left(index);
    int right = Right(index);

    if ((left < Size()) &&
        (m_vpHeap[left]->GetTimeToReach() < m_vpHeap[index]->GetTimeToReach()))
    {
        smallest = left;
    }
    else
    {
        smallest = index;
    }
    
    if ((right < Size()) &&
        (m_vpHeap[right]->GetTimeToReach() < m_vpHeap[smallest]->GetTimeToReach()))
    {
        smallest = right;
    }
    
    if (smallest != index)
    {
        iter_swap(m_vpHeap.begin()+index, m_vpHeap.begin()+smallest);
        MinHeapify(smallest);
    }
}


/******************************************************************************
* @Function     MinHeap::ExtractMin
*
* @Description	Extract Min.
*
* @Return		Router*					Pointer to router 
*                                       having smallest time to reach
******************************************************************************/
Router *MinHeap::ExtractMin()
{
    Router  *pMin;
    
    if (Size() < 1)
    {
        std::cerr << __FUNCTION__
                  << "(): Heap Underflow!"
                  << std::endl;
    }
    
    pMin        = m_vpHeap[0];
    m_vpHeap[0] = m_vpHeap[Size() - 1];
    m_vpHeap.erase(m_vpHeap.end() - 1);
    MinHeapify(0);

    return pMin;
}


/******************************************************************************
* @Function     MinHeap::Insert
*
* @Description	Insert Router into Min Heap data structure.
*
* @Input		Router*     pRouter		Router to be inserted
*
* @Return		void					Returns nothing
******************************************************************************/
void MinHeap::Insert(Router *pRouter)
{
    HeapDecreaseKey(pRouter, Size());
}


/******************************************************************************
* @Function     MinHeap::HeapDecreaseKey
*
* @Description	Decrease key located at given index.
*
* @Input		Router*     pRouter		Router to be replaced with
*
* @Input		int         index		Index at which key is to be decreased
*
* @Return		void					Returns nothing
******************************************************************************/
void MinHeap::HeapDecreaseKey(Router *pRouter, int index)
{
    if ((index < Size()) &&
        (pRouter->GetTimeToReach() > m_vpHeap[index]->GetTimeToReach()))
    {
        std::cerr << __FUNCTION__
                  << "(): New key <"
                  << pRouter->GetTimeToReach()
                  << "> is greater than current key <"
                  << m_vpHeap[index]->GetTimeToReach()
                  << ">!"
                  << std::endl;
        return;
    }
    
    m_vpHeap[index] = pRouter;
    
    while ((index > 0) && (m_vpHeap[Parent(index)] > m_vpHeap[index]))
    {
        iter_swap(m_vpHeap.begin()+index, m_vpHeap.begin()+Parent(index));
        index = Parent(index);
    }
}


/******************************************************************************
* @Function     MinHeap::Display
*
* @Description	Display Min Heap data structure.
*
* @Return		void					Returns nothing
******************************************************************************/
void MinHeap::Display()
{
    std::cout << __FUNCTION__ << "(): Min Heap:" << std::endl;
    for (int i=0; i<Size(); i++)
    {
        std::cout << m_vpHeap[i]->GetRouterName()
                  << " "
                  << m_vpHeap[i]->GetTimeToReach()
                  << std::endl;
    }
}