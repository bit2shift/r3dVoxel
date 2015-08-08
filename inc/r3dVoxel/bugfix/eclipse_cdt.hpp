#pragma once

/* Alternative to alignas(x) on Eclipse CDT */
#define ALIGN(x) [[gnu::aligned(x)]]
