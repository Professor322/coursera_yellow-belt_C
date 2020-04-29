//
// Created by professor on 4/29/20.
//

#pragma once

#include "includes.h"
#include "date.h"

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};


template <typename T>
bool Less(const T& elem, const T& to_compare) {return elem < to_compare; }

template <typename T>
bool LessOrEqual(const T& elem, const T& to_compare) {return elem <= to_compare; }

template <typename T>
bool Greater(const T& elem, const T& to_compare) {return elem > to_compare; }

template <typename T>
bool GreaterOrEqual(const T& elem, const T& to_compare) {return elem >= to_compare; }

template <typename T>
bool Equal(const T& elem, const T& to_compare) {return elem == to_compare; }

template <typename T>
bool NotEqual(const T& elem, const T& to_compare) {return elem != to_compare; }


