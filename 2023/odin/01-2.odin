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
	words := [9]string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}
	result := 0
	for line, idx in lines {
		left, right := -1, -1
		for id := 0; id < len(line); id += 1 {
            // check for digit char
			if is_digit(line[id]) {
				if left == -1 do left = cast(int)line[id] - '0'
				right = cast(int)line[id] - '0'
				continue
			}
            // check for digit word
			n := 0
			for n < 9 {
				found := true
				for i := 0; i < len(words[n]); i += 1 {
					if i + id >= len(line) || words[n][i] != line[id + i] {
						found = false
						break
					}
				}
				if found {
					if left == -1 do left = n + 1
					right = n + 1
					break
				}
				n += 1
			}
		}
		result += cast(int)(left * 10 + right)
	}
	fmt.println(result)
}
