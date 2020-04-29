//
// Created by professor on 4/29/20.
//

#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date) :
				_cmp(cmp),
				_predicate(date) {
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
	switch(_cmp) {
		case Comparison::Less:
			return Less(date, _predicate);
		case Comparison::LessOrEqual:
			return LessOrEqual(date, _predicate);
		case Comparison::Greater:
			return Greater(date, _predicate);
		case Comparison::GreaterOrEqual:
			return GreaterOrEqual(date, _predicate);
		case Comparison::Equal:
			return Equal(date, _predicate);
		case Comparison::NotEqual:
			return NotEqual(date, _predicate);
		default: return false;
	}
}

EventComparisonNode::EventComparisonNode(const Comparison &cmp, const string& value) :
			_cmp(cmp),
			_predicate(value) {}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {

	switch(_cmp) {
		case Comparison::Less:
			return Less(event, _predicate);
		case Comparison::LessOrEqual:
			return LessOrEqual(event, _predicate);
		case Comparison::Greater:
			return Greater(event, _predicate);
		case Comparison::GreaterOrEqual:
			return GreaterOrEqual(event, _predicate);
		case Comparison::Equal:
			return Equal(event, _predicate);
		case Comparison::NotEqual:
			return NotEqual(event, _predicate);
		default: return false;
	}
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logic,
		shared_ptr<const Node> lhs,
		shared_ptr<const Node> rhs) :
		op(logic),
		_lhs(lhs),
		_rhs(rhs)
		{}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
	if (op == LogicalOperation::And) {
		return _lhs->Evaluate(date, event) && _rhs->Evaluate(date, event);
	} else if (op == LogicalOperation::Or) {
		return _lhs->Evaluate(date, event) || _rhs->Evaluate(date, event);
	}
	return false;
}