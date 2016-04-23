/******************************************************************************//*!
* @File          MinHeap.h
* 
* @Title         Header file for Min Heap data structure.
* 
* @Author        Chetan Borse
* 
* @Created       04/22/2016
* 
* @Platform      ?
* 
* @Description   This header file defines the prototypes of classes and functions 
*                for Min Heap data structure.
* 
*//*******************************************************************************/ 

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <limits>
#include <map>
#include <algorithm>

#include "Graph.h"

#define INFINITY std::numeric_limits<float>::infinity()


/* Forward declaration for Router class */
class Router;


/******************************************************************************
* @Class		MinHeap
*
* @Description	Class representing Min Heap data structure.
* 				This class defines attributes and functionalities
*               of Min Heap data structure.
******************************************************************************/
class MinHeap
{
private:
    std::vector<Router*>    m_vpHeap;

    // Methods for retrieving Left Child, Right Child and Parent respectively
    int Left(int index) { return 1 + (2 * index); }
    int Right(int index) { return 2 + (2 * index); }
    int Parent(int index) { return ((index + 1) / 2) - 1; }

public:
    // Constructor
    MinHeap(std::vector<Router*> vpHeap)
    {
        Create(vpHeap);
    }
    
    // Destructor
    ~MinHeap() {}

    // Public setter
    void SetHeap(std::vector<Router*> vpHeap) { m_vpHeap = vpHeap; }
    
    // Public getter
    std::vector<Router*> const GetHeap() { return m_vpHeap; }

    // Returns size of Min Heap data structure
    unsigned int Size() { return m_vpHeap.size(); }

    // Create Min Heap data structure
    void Create(std::vector<Router*> vpHeap);
    
    // Min Heapify
    void MinHeapify(int index);
    
    // Extract Min
    Router *ExtractMin();
    
    // Insert Router into Min Heap data structure
    void Insert(Router *pRouter);
    
    // Decrease key located at given index
    void HeapDecreaseKey(Router *pRouter, int index);
    
    // Display Min Heap data structure
    void Display();
};