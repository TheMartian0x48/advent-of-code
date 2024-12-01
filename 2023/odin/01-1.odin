package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"


is_digit :: proc(ch: u8) -> bool {
	return '0' <= ch && ch <= '9'
}

read_lines :: proc() -> [dynamic]string {
	data, ok := os.read_entire_file("in.txt", context.allocator)
	defer delete(data, context.allocator)
	it := string(data)
	result: [dynamic]string
	for line in strings.split_lines_iterator(&it) {
		append(&result, strings.clone(line))
	}
	return result
}

main :: proc() {
	lines := read_lines()
	result := 0
	for line, idx in lines {
		left, right: i8 = -1, -1
		for i := 0; i < len(line); i += 1 {
			if is_digit(line[i]) {
				if left == -1 do left = cast(i8)(line[i] - '0')
				right = cast(i8)(line[i] - '0')
			}
		}
		result += cast(int)(left * 10 + right)
	}
	fmt.println(result)
}
