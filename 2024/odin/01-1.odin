package main

import "core:fmt"
import "core:os"
import "core:slice"
import "core:sort"
import "core:strconv"
import "core:strings"

main :: proc() {
	data, ok := os.read_entire_file("in.txt", context.allocator)
	defer delete(data, context.allocator)
	input := string(data)

	left: [dynamic]int
	right: [dynamic]int

	for line in strings.split_lines_iterator(&input) {
		parts := strings.split(line, "   ")
		l := strconv.atoi(parts[0])
		r := strconv.atoi(parts[1])
		append(&left, l)
		append(&right, r)
	}

	slice.sort(left[:])
	slice.sort(right[:])

	result := 0
	for i in 0 ..< len(left) do result = result + abs(left[i] - right[i])
	fmt.println(result)
}