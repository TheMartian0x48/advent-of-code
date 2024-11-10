package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

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

Game :: struct {
	id:     int,
	subset: []string,
}

parse_game :: proc(line: string) -> Game {
	tokens, ok := strings.split(line, ":")
	game := Game{}
	ids, id_ok := strings.split(tokens[0], " ")
	game.id = strconv.atoi(ids[1])
	subset, s_ok := strings.split(tokens[1], ";")
	game.subset = subset
	return game
}

game_point :: proc(game: Game, r, g, b: int) -> int {
	for subset in game.subset {
		tokens, ok := strings.split(subset, ",")
		for token in tokens {
			color_tokens, c_ok := strings.split(strings.trim(token, " "), " ")
			id := strconv.atoi(color_tokens[0])
			if color_tokens[1] == "red" && id > r do return 0
			if color_tokens[1] == "blue" && id > b do return 0
			if color_tokens[1] == "green" && id > g do return 0
		}
	}
	return game.id
}

main :: proc() {
	lines := read_lines()
	games: [dynamic]Game
	for line, idx in lines do append(&games, parse_game(line))
	result := 0
	for game in games do result += game_point(game, 12, 13, 14)
	fmt.println(result)
}
