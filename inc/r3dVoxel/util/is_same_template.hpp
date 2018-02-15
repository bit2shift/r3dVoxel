#pragma once

namespace r3dVoxel::util
{
	/*
	 * Checks if two given templates are the same, ignoring their parameters.
	 */
	template<typename, typename>
	constexpr bool is_same_template{false};

	template<template<typename...> class T, typename... A, typename... B>
	constexpr bool is_same_template<T<A...>, T<B...>>{true};
}
