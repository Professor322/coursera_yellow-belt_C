#pragma once

#include "includes.h"
#include "node.h"


using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
