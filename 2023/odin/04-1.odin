package main

import "core:fmt"
import "core:math"
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

Card :: struct {
	id:      int,
	winning: [dynamic]int,
	have:    [dynamic]int,
}

parse_card :: proc(line: string) -> Card {
	card := Card{}
	tokens, _ := strings.split(line, ":")

	id_tokens, _ := strings.split(tokens[0], " ")
	card.id = strconv.atoi(id_tokens[1])

	tokens, _ = strings.split(tokens[1], "|")
	for n in strings.split(tokens[0], " ") do if len(n) > 0 do append(&card.winning, strconv.atoi(n))
	for n in strings.split(tokens[1], " ") do if len(n) > 0 do append(&card.have, strconv.atoi(n))
	return card
}

card_point :: proc(card: Card) -> int {
	win: uint = 0
	for n in card.have {
		is_winner := false
		for x in card.winning do is_winner = is_winner || x == n
		if is_winner do win += 1
	}
	return win > 0 ? 1 << (win - 1) : 0
}

main :: proc() {
	lines := read_lines()
	cards: [dynamic]Card
	for line, idx in lines do append(&cards, parse_card(line))
	result := 0
	for card in cards do result += card_point(card)
	fmt.println(result)
}
