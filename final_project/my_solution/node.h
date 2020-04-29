//
// Created by professor on 4/29/20.
//
#pragma once

#include "date.h"
#include "comparisons.h"
#include <string>
#include <memory>
#include <map>
#include <functional>

using namespace std;


class Node {
public:
	Node() = default;
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
private:

};

struct EmptyNode : public Node {
	EmptyNode() = default;
	bool Evaluate(const Date &date, const string &event) const override { return true; }
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);
	bool Evaluate(const Date &date, const string &event) const override;
private:
	const Comparison _cmp;
	const Date _predicate;
	function<bool(const Date&, const Date&)> func;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& value);
	bool Evaluate(const Date &date, const string &event) const override;
private:
	const Comparison _cmp;
	const string _predicate;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& logic,
			shared_ptr<const Node> lhs,
			shared_ptr<const Node> rhs);
	bool Evaluate(const Date &date, const string &event) const override;
private:
	const LogicalOperation op;
	shared_ptr<const Node> _lhs, _rhs;
};