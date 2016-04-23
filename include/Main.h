/******************************************************************************//*!
* @File          Main.h
* 
* @Title         Header file for main utility/application.
* 
* @Author        Chetan Borse
* 
* @Created       04/22/2016
* 
* @Platform      ?
* 
* @Description   This header file defines the prototypes of classes and functions 
*                for main utility/application.
* 
*//*******************************************************************************/ 

#pragma once

#include <sstream>

#include "Graph.h"


// Tokenizer returns vector of strings by splitting original string on whitespaces
std::vector<std::string> Tokenizer(const std::string& pszQuery,
                                   char chDelimiter=' ');


// Helper method
void ShowUsage();